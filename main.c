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


int main() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcat(cwd,  "/file.txt");
    }
    else
    {
        printf("SOMETHING WENT WRONG");
        return 1;
    }
    path = malloc(strlen(cwd) + strlen("/file.txt"));
    strcpy(path, cwd);
    greetings();
    interactions_with_user();
    free(path);
    return 0;
}
