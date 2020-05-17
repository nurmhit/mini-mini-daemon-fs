//
// Created by Мхитарян Нарек on 17/05/2020.
//

#pragma once

#include <stdint.h>
#include "globals.h"
#include "bitoperations.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "defblock.h"


struct inode{
    uint32_t file_len;
    uint32_t creation_timestamp, last_access_timestamp, last_change_timestamp;
    uint32_t id_creation, id_group;
    uint32_t is_dir, num_in_row;
    uint32_t hard_link_counter;
    int32_t blocks[inode_block_num];
};

static const int offset_inodes = offset_blocksbitmap + block_num;

struct inode* create_node();

void dump_root_inode(FILE* f);

void dump_inodes(FILE* f);

void dump_inode(int i, struct inode* node);

void read_inode(int i, struct inode* node);

int32_t acquire_inode();

void delete_inode(int inode_number);
