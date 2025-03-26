static size_t filelist_len = 0;
void browser_init(const char *path, DIR *dir)
{
	// PRE: true
    const struct dirent *nextdir;
    size_t i = 0, path_len = strlen(path);
    while ((nextdir = readdir(dir)) != NULL) {
	i++;
    }
    rewinddir(dir);
	filelist_len = i;
    i = 0;
    while ((nextdir = readdir(dir)) != NULL && i < filelist_len) {
	i++;
    }
    assert(i == filelist_len); // POST
}

