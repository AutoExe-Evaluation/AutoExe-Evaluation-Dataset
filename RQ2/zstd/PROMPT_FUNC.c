/** FIO_openDstFile() :
 *  condition : `dstFileName` must be non-NULL.
 * @result : FILE* to `dstFileName`, or NULL if it fails */
static FILE*
FIO_openDstFile(FIO_ctx_t* fCtx, FIO_prefs_t* const prefs,
                const char* srcFileName, const char* dstFileName,
                const int mode)
{
    if (prefs->testMode) return NULL;  /* do not open file in test mode */

    assert(dstFileName != NULL);
    if (!strcmp (dstFileName, stdoutmark)) {
        DISPLAYLEVEL(4,"Using stdout for output \n");
        SET_BINARY_MODE(stdout);
        if (prefs->sparseFileSupport == 1) {
            prefs->sparseFileSupport = 0;
            DISPLAYLEVEL(4, "Sparse File Support is automatically disabled on stdout ; try --sparse \n");
        }
        return stdout;
    }

    /* ensure dst is not the same as src */
    if (srcFileName != NULL && UTIL_isSameFile(srcFileName, dstFileName)) {
        DISPLAYLEVEL(1, "zstd: Refusing to open an output file which will overwrite the input file \n");
        return NULL;
    }

    if (prefs->sparseFileSupport == 1) {
        prefs->sparseFileSupport = ZSTD_SPARSE_DEFAULT;
    }

    if (UTIL_isRegularFile(dstFileName)) {
        /* Check if destination file already exists */
#if !defined(_WIN32)
        /* this test does not work on Windows :
         * `NUL` and `nul` are detected as regular files */
        if (!strcmp(dstFileName, nulmark)) {
            EXM_THROW(40, "%s is unexpectedly categorized as a regular file",
                        dstFileName);
        }
#endif
        if (!prefs->overwrite) {
            if (g_display_prefs.displayLevel <= 1) {
                /* No interaction possible */
                DISPLAYLEVEL(1, "zstd: %s already exists; not overwritten  \n",
                        dstFileName);
                return NULL;
            }
            DISPLAY("zstd: %s already exists; ", dstFileName);
            if (UTIL_requireUserConfirmation("overwrite (y/n) ? ", "Not overwritten  \n", "yY", fCtx->hasStdinInput))
                return NULL;
        }
        /* need to unlink */
        FIO_removeFile(dstFileName);
    }

    {
#if defined(_WIN32)
        /* Windows requires opening the file as a "binary" file to avoid
         * mangling. This macro doesn't exist on unix. */
        const int openflags = O_WRONLY|O_CREAT|O_TRUNC|O_BINARY;
        const int fd = _open(dstFileName, openflags, mode);
        FILE* f = NULL;
        if (fd != -1) {
            f = _fdopen(fd, "wb");
        }
#else
        const int openflags = O_WRONLY|O_CREAT|O_TRUNC;
        const int fd = open(dstFileName, openflags, mode);
        FILE* f = NULL;
        if (fd != -1) {
            f = fdopen(fd, "wb");
        }
#endif
        if (f == NULL) {
            DISPLAYLEVEL(1, "zstd: %s: %s\n", dstFileName, strerror(errno));
        }
        /* An increased buffer size can provide a significant performance boost on some platforms.
         * Note that providing a NULL buf with a size that's not 0 is not defined in ANSI C, but is defined
         * in an extension. There are three possibilities here -
         * 1. Libc supports the extended version and everything is good.
         * 2. Libc ignores the size when buf is NULL, in which case everything will continue as if we didn't
         *    call `setvbuf`.
         * 3. We fail the call and execution continues but a warning message might be shown.
         * In all cases due execution continues. For now, I believe that this is a more cost-effective
         * solution than managing the buffers allocations ourselves (will require an API change). */
        if(setvbuf(f, NULL, _IOFBF, 1 MB))
            DISPLAYLEVEL(2, "Warning: setvbuf failed for %s\n", dstFileName);
        return f;
    }
}
