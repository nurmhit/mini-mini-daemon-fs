//
// Created by Мхитарян Нарек on 17/05/2020.
//


#pragma once

#include "globals.h"
#include "inode.h"
#include <stdio.h>
#include <stdlib.h>

struct defblock{
    char data[128];
};

int offset_blocks;

struct defblock* create_block();

void dump_blocks(FILE* f);

void dump_block(int i, struct defblock* block);

void read_block(int i, struct defblock* block);

int32_t acquire_block();

void ret_block_text(int num, char* place);

void out_block(int num);

void fill_block_origin(char* name, char* type, int num, struct defblock* block);

void delete_block(int block_number);

