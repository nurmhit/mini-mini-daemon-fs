//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "fileInteractions.h"

int add_small_file(char* content)
{
    int ans = -1;
    if(free_inodes > 0 && free_blocks >= inode_block_num)
    {
        FILE *f = fopen(path, "rb+");
        int my_node_num = acquire_inode();
        struct inode* my_node = create_node();
        read_inode(my_node_num, my_node);
        for(int i = 0; i < inode_block_num; ++i)
        {
            my_node->blocks[i] = acquire_block();
        }
        dump_inode(my_node_num, my_node);
        struct defblock* block = create_block();
        int cur_pos_in_text = 0, length = strlen(content), cur_space = 0, cur_num = 0;
        while(cur_pos_in_text < length)
        {
            if(cur_space == 0)
            {
                if(cur_num != 0)
                {
                    dump_block(my_node->blocks[cur_num], block);
                }
                cur_num++;
                read_block(my_node->blocks[cur_num], block);
                cur_space = block_size;

            }
            block->data[block_size - cur_space] = content[cur_pos_in_text];
            cur_space--;
            cur_pos_in_text++;
        }
        if(cur_space != 0)
        {
            block->data[block_size - cur_space] = '\0';
        }
        dump_block(my_node->blocks[cur_num], block);
        ans = my_node_num;
        free(my_node);
        free(block);
        fclose(f);
    }
    else
    {
        printf("COULDN'T CREATE FILE, SORRY\n");
    }
    return ans;
}







int add_file(char* name, char* content)
{
    if(strlen(name) >  block_size)
    {
        printf("YOUR FILE NAME IS TOO BIG, SHORTEN IT TO SAVE IN FILE SYSTEM\n");
        return -1;
    }
    if(strlen(content) <= 15*block_size - 8)
    {
        int num = add_small_file(content);
        if(num != -1)
        {
            //TODO more compact placement inside blocks
            struct inode* cur_dir = create_node();
            read_inode(cur_directory, cur_dir);
            for(int i = 0; i < inode_block_num; ++i)
            {
                if(cur_dir->blocks[i] == -1)
                {
                    struct defblock* block = create_block();
                    int block_number = acquire_block();
                    cur_dir->blocks[i] = block_number;
                    read_block(block_number, block);
                    char* type = "file";
                    fill_block_origin(name, type, num, block);
                    dump_block(block_number, block);
                    free(block);
                    break;
                }

            }
            dump_inode(cur_directory, cur_dir);
            free(cur_dir);
        }
        else
        {
            printf("SOME PROBLEM OCCURED WITH FILE\n");
        }
    }
    else
    {
        //TODO add bigger file files support
    }
    return 0;
}


void add_dir(char* name)
{
    struct inode* cur_dir = create_node();
    read_inode(cur_directory, cur_dir);
    int dir_num = acquire_inode();
    struct inode* dir_inode = create_node();
    dir_inode->is_dir = 1;
    dump_inode(dir_num, dir_inode);
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] == -1)
        {
            //TODO add more compact placement of dirs inside block
            struct defblock* block = create_block();
            int block_number = acquire_block();
            cur_dir->blocks[i] = block_number;
            read_block(block_number, block);
            char* type = "dir";
            fill_block_origin(name, type, dir_num, block);
            dump_block(block_number, block);
            free(block);
            break;
        }

    }
    dump_inode(cur_directory, cur_dir);
    free(dir_inode);
    free(cur_dir);
}