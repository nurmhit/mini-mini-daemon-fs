//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "defblock.h"

struct defblock* create_block()
{
    struct defblock* block = malloc(sizeof(struct defblock));
    for(int i = 0; i < inode_block_num; ++i)
    {
        block->data[i] = '0';
    }
    return block;
}

void dump_blocks(FILE* f)
{
    for(int i = 0; i < block_num; ++i)
    {
        struct defblock* block = create_block();
        fwrite(block, sizeof(struct defblock), 1, f);
        free(block);
    }

}

void dump_block(int i, struct defblock* block)
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_blocks + i * sizeof(struct defblock), SEEK_SET);
    fwrite(block, sizeof(struct defblock), 1, f);
    fclose(f);
}

void read_block(int i, struct defblock* block)
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_blocks + i * sizeof(struct defblock), SEEK_SET);
    fread(block, sizeof(struct defblock), 1, f);
    fclose(f);
}

int32_t acquire_block()
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_blocks, SEEK_SET);
    int block_num = -1;
    for(int i = offset_blocksbitmap*8; i < offset_inodes*8; ++i)
    {
        if(can_get_bit(i))
        {
            acquire_bit(i);
            free_blocks--;
            block_num = i;
            break;
        }
    }
    if(block_num == -1)
    {
        printf("FILE SYSTEM IS FULL\nNEED MORE BLOCKS\n");
        return -1;
    }
    fclose(f);
    return block_num;
}

void out_block(int num)
{
    struct defblock* cur_block = create_block();
    read_block(num, cur_block);
    printf("%s", cur_block->data);
    free(cur_block);
}

void fill_block_origin(char* name, char* type, int num, struct defblock* block)
{
    sprintf(block->data, "%s %s %d", name, type, num);
}

void delete_block(int block_number)
{
    if(block_number == -1)
        return;
    struct defblock* cur_block = create_block();
    dump_block(block_number, create_block());
    release_bit(get_block_bit_place(block_number));
    free(cur_block);
    free_blocks++;
}