//
// Created by Мхитарян Нарек on 17/05/2020.
//


#pragma once

#include <limits.h>

static const int block_num = 128;
static const int inode_num = 128;
static const int block_size = 128;
static const int inode_block_num = 32;
static int free_inodes = inode_num - 1;
static int free_blocks = block_num;
static int cur_id = 1;
static int cur_directory = 0;
static char cwd[PATH_MAX];
static char to_dir_path[PATH_MAX];
static char* path;
static int LOCAL_PATH_MAX = PATH_MAX;
static int MAX_FILE = inode_block_num*block_size;



