#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "globals.h"
#include "defblock.h"
#include "defblock.c"
#include "inode.h"
#include "inode.c"
#include "superblock.h"
#include "superblock.c"
#include "defblock.h"
#include "bitoperations.h"
#include "bitoperations.c"
#include "fileInteractions.h"
#include "fileInteractions.c"
#include "userEndInteractions.h"
#include "userEndInteractions.c"

void some_test()
{
  char* pathik = "/lol/haha/kek";
  char place[LOCAL_PATH_MAX];
  int start_point = 1;
  while(start_point < strlen(pathik))
  {
    start_point = get_next_dir_name(start_point, pathik, place);
    if(start_point < strlen(pathik))
      printf("%s ", place);
  }
}


int main() {
  //some_test();
  //return 0;
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        path = malloc(strlen(cwd) + strlen("/file.txt"));
        strcpy(path, cwd);
        strcat(path,  "/");
        strcpy(to_dir_path, path);
        strcat(path,  "file.txt");
    }
    else
    {
        printf("SOMETHING WENT WRONG");
        return 1;
    }


    greetings();
    interactions_with_user();
    free(path);
    return 0;
}
