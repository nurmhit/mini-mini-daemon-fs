//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "bitoperations.h"

uint8_t get_mask_add(int n)
{
    return (1 << n);
}

uint8_t get_mask_release(int n)
{
    return ~(1 << n);
}

void full_zero()
{
    FILE *f = fopen(path, "rb+");

    uint8_t  x = 0;
    for(int i = 0;  i < 10; ++i)
    {
        fwrite(&x, sizeof(uint8_t), 1, f);
    }

    fclose(f);
}

void dump_bitmap_inodes(FILE* f)
{
    struct bitmap_inodes *bit_i = malloc(sizeof(struct bitmap_inodes));
    for(int i = 0; i < inode_num; ++i)
    {
        bit_i->is_used[i] = 0;
    }
    fseek(f, 0, SEEK_END);
    fwrite(bit_i, sizeof(struct bitmap_inodes), 1, f);

}

void dump_bitmap_blocks(FILE* f)
{
    struct bitmap_blocks *bit_b = malloc(sizeof(struct bitmap_blocks));
    for(int i = 0; i < block_num; ++i)
    {
        bit_b->is_used[i] = 0;
    }
    fseek(f, 0, SEEK_END);
    fwrite(bit_b, sizeof(struct bitmap_blocks), 1, f);

}


void acquire_bit(int n)
{
    int fst = n/8;
    int sec = n%8;
    FILE *f = fopen(path, "rb+");
    uint8_t x  = get_mask_add(sec);
    fseek(f, fst, SEEK_SET);
    uint8_t z;
    fread(&z, sizeof(uint8_t), 1, f);
    fseek(f, fst, SEEK_SET);
    x |= z;
    fwrite(&x, sizeof(x), 1, f);
    fclose(f);
}

void release_bit(int n)
{
    int fst = n/8;
    int sec = n%8;
    FILE *f = fopen(path, "rb+");
    uint8_t x  = get_mask_release(sec);
    fseek(f, fst, SEEK_SET);
    uint8_t z;
    fread(&z, sizeof(uint8_t), 1, f);
    fseek(f, fst, SEEK_SET);
    x &= z;
    fwrite(&x, sizeof(x), 1, f);
    fclose(f);
}

bool can_get_bit(int n)
{
    int fst = n/8;
    int sec = n%8;
    FILE *f = fopen(path, "rb+");
    uint8_t x  = get_mask_add(sec);
    fseek(f, fst, SEEK_SET);
    uint8_t z;
    fread(&z, sizeof(uint8_t), 1, f);
    x &= z;
    fclose(f);
    return (x == 0);
}

int get_inode_bit_place(int inode_number)
{
    return offset_inodebitmap*8 + inode_number;
}

int get_block_bit_place(int block_number)
{
    return offset_blocksbitmap*8 + block_number;
}