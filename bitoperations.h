//
// Created by Мхитарян Нарек on 17/05/2020.
//

#pragma once

#include <stdint.h>
#include "globals.h"
#include "superblock.h"
#include <stdlib.h>
#include <stdbool.h>

struct bitmap_inodes{
    uint8_t is_used[inode_num];
};

struct bitmap_blocks{
    uint8_t is_used[block_num];
};

static const int offset_inodebitmap = sizeof(struct superblock);
static const int offset_blocksbitmap = offset_inodebitmap + inode_num;

uint8_t get_mask_add(int n);

uint8_t get_mask_release(int n);

void dump_bitmap_inodes(FILE* f);

void dump_bitmap_blocks(FILE* f);

void acquire_bit(int n);

void release_bit(int n);

bool can_get_bit(int n);

void full_zero();

int get_inode_bit_place(int inode_number);

int get_block_bit_place(int block_number);

