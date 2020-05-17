//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "superblock.h"

void dump_superblock(FILE* f) {
    struct superblock *new_super = malloc((sizeof(struct superblock)));
    new_super->version = 0;
    new_super->block_size = 2048;
    new_super->inode_size = 2048;
    new_super->free_blocks = block_num;
    new_super->free_inodes = inode_num;
    new_super->total_blocks = block_num;
    new_super->total_inodes = inode_num;
    new_super->padding = 0;
    fwrite(new_super, sizeof(*new_super), 1, f);
    free(new_super);
}