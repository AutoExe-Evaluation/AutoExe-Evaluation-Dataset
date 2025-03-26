void browser_init(const char *path, DIR *dir)
{
    // PRE: true
    const struct dirent *nextdir;
    size_t i = 0, path_len = strlen(path);
    int col = 0;
	/* The maximum number of columns that the filenames will take
	 * up. */
    int line = 0;
	/* The maximum number of lines that the filenames will take
	 * up. */
    int filesperline = 0;
	/* The number of files that we can display per line. */

    assert(path != NULL && path[strlen(path) - 1] == '/' && dir != NULL);

    longest = 0;

    /* Find the length of the longest filename in the current folder. */
    while ((nextdir = readdir(dir)) != NULL) {
	size_t name_len = strlenpt(nextdir->d_name);

	if (name_len > longest)
	    longest = name_len;

	i++;
    }

    /* Put 10 characters' worth of blank space between columns of filenames
     * in the list whenever possible, as Pico does. */
    longest += 10;

    /* Make sure longest is between 15 and COLS. */
    if (longest < 15)
	longest = 15;
    if (longest > COLS)
	longest = COLS;

    rewinddir(dir);

    free_chararray(filelist, filelist_len);

    filelist_len = i;

    filelist = (char **)nmalloc(filelist_len * sizeof(char *));

    i = 0;

    while ((nextdir = readdir(dir)) != NULL && i < filelist_len) {
	/* Don't show the "." entry. */
	if (strcmp(nextdir->d_name, ".") == 0)
	    continue;

	filelist[i] = charalloc(path_len + strlen(nextdir->d_name) + 1);
	sprintf(filelist[i], "%s%s", path, nextdir->d_name);

	i++;
    }

    assert(i == filelist_len); // POST
}
