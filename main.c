#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

//Use sprintf and only go through directory once at the cost of memory or
//go through directory twice?
int main(int argc, char *argv[]) {
  char dirName[40];
  if (argc > 1) { //use command line arguments
    strncpy(dirName, argv[1], 40);
  } else {
    printf("Please input the name of a directory: ");
    fgets(dirName, 40, stdin);
  }

  strtok(dirName, "\n"); //remove the ending newline
  int total = 0;
  DIR * dir = opendir(dirName);
  if (dir == NULL) {
    printf(" >> %s \n", strerror(errno));
    return 0;
  }

  struct dirent * info = readdir(dir);
  struct stat metadata;
  printf("Statistics for directory: %s \n", dirName);
  printf("Directories: \n");

  //Find stuff related to directories first
  while (info != NULL) {
    char path[300];
    sprintf(path, "%s/%s", dirName, info -> d_name);
    stat(path, &metadata);
    if (S_ISDIR(metadata.st_mode)) {
      printf(" > %s \n", info -> d_name);
    }

    info = readdir(dir);
  }

  rewinddir(dir); //go back to start
  printf("Regular files: \n");

  //Then find regular files
  info = readdir(dir);
  while (info != NULL) {
    char path[300];
    sprintf(path, "%s/%s", dirName, info -> d_name);
    stat(path, &metadata);
    if (S_ISREG(metadata.st_mode)) {
      printf(" > %s \n", info -> d_name);
      total += metadata.st_size;
    }

    info = readdir(dir);
  }

  closedir(dir);
  printf("Total directory size: %d bytes \n", total);

  return 0;
}
