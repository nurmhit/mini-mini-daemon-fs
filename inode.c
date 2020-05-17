//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "inode.h"


struct inode* create_node()
{
    struct inode *node = malloc(sizeof(struct inode));
    node->num_in_row = 0;
    time_t cur_time = time(NULL);
    node->creation_timestamp = cur_time;
    node->last_access_timestamp = cur_time;
    node->last_change_timestamp = cur_time;
    node->hard_link_counter = 0;
    node->file_len = 0;
    node->id_creation = 0;
    node->id_group = 0;
    node->is_dir = 0;
    for(int i = 0; i < inode_block_num; ++i)
    {
        node->blocks[i] = -1;
    }
    return node;
}

void dump_root_inode(FILE* f)
{
    struct inode *root_node = create_node();
    root_node->is_dir = 1;
    acquire_bit(offset_inodebitmap*8);
    fwrite(root_node, sizeof(struct inode), 1, f);
    free(root_node);

}

void dump_inodes(FILE* f)
{
    for(int i = 0; i < inode_num - 1; ++i) {
        struct inode *node = create_node();
        fwrite(node, sizeof(struct inode), 1, f);
        free(node);
    }
}

void dump_inode(int i, struct inode* node)
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_inodes + i * sizeof(struct inode), SEEK_SET);
    fwrite(node, sizeof(struct inode), 1, f);
    fclose(f);
}

void read_inode(int i, struct inode* node)
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_inodes + i * sizeof(struct inode), SEEK_SET);
    fread(node, sizeof(struct inode), 1, f);
    fclose(f);
}

int32_t acquire_inode()
{
    FILE *f = fopen(path, "rb+");
    fseek(f, offset_inodes, SEEK_SET);
    int inode_number = -1;
    for(int i = offset_inodebitmap*8; i < offset_blocksbitmap*8; ++i)
    {
        if(can_get_bit(i))
        {
            acquire_bit(i);
            free_inodes--;
            inode_number = i - offset_inodebitmap*8;
            break;
        }
    }
    if(inode_number == -1)
    {
        printf("FILE SYSTEM IS FULL\n NEED MORE INODES\n");
        return -1;
    }
    fclose(f);
    return inode_number;
}

void delete_inode(int inode_number)
{
    struct inode* cur_node = create_node();
    read_inode(inode_number, cur_node);
    if(cur_node->is_dir != 1)
    {
        for (int i = 0; i < inode_block_num; ++i)
        {
            delete_block(cur_node->blocks[i]);
        }
    }
    else
    {
        for (int i = 0; i < inode_block_num; ++i)
        {
            if(cur_node->blocks[i] != -1)
            {
                struct defblock *cur_block = create_block();
                read_block(cur_node->blocks[i], cur_block);
                char name[128], type[10];
                int number;
                sscanf(cur_block->data, "%s %s %d", name, type, &number);
                if(strcmp(type,"file") == 0)
                {
                    delete_block(number);
                }
                else
                {
                    delete_inode(number);
                }
            }
        }
    }
    free(cur_node);
    cur_node = create_node();
    dump_inode(inode_number, cur_node);
    release_bit(get_inode_bit_place(inode_number));
    free_inodes++;
    free(cur_node);
}
