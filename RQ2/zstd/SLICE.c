/* FILE: benchzstd.c */
/*...*/
#define MB *(1 <<20)


/* FILE: zstdcli.c */
/*...*/
#define MB *(1 <<20)


/* FILE: fileio.c */
/*...*/
static FILE*
FIO_openDstFile(FIO_ctx_t* fCtx, FIO_prefs_t* const prefs,
                const char* srcFileName, const char* dstFileName,
                const int mode)
{
    /*...*/
    {
/*...*/
        FILE* f = NULL;
        /*...*/
        if (f == NULL) {
            /*...*/

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
        if(setvbuf(f, NULL, _IOFBF, 1 MB))                      /* CRASH LOCATION */
            /*...*/;
        /*...*/

    }
}
