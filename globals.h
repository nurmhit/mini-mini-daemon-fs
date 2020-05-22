//
// Created by Мхитарян Нарек on 17/05/2020.
//


#pragma once

#include <limits.h>

int block_num;
int inode_num;
int block_size;
int inode_block_num;
int free_inodes;
int free_blocks;
int cur_id = 1;
int cur_directory = 0;
char cwd[PATH_MAX];
char to_dir_path[PATH_MAX];
char* path;
int LOCAL_PATH_MAX = PATH_MAX;
int MAX_FILE;



