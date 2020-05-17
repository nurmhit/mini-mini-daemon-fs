//
// Created by Мхитарян Нарек on 17/05/2020.
//

#pragma once

#include "globals.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct superblock{
    uint32_t total_blocks, total_inodes;
    uint32_t free_blocks, free_inodes;
    uint32_t block_size;
    uint32_t inode_size;
    uint32_t version, padding;
};

void dump_superblock(FILE* f);

static const int offset_superblock = 0;

