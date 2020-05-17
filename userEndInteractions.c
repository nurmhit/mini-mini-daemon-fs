//
// Created by Мхитарян Нарек on 17/05/2020.
//

#include "userEndInteractions.h"

void rmrf(char* filename)
{
    struct inode* cur_dir = create_node();
    read_inode(cur_directory, cur_dir);
    char name[128], type[10];
    int inode_number;
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] != -1)
        {
            int block_number = cur_dir->blocks[i];
            struct defblock* cur_block = create_block();
            read_block(block_number, cur_block);
            sscanf(cur_block->data, "%s %s %d", name, type, &inode_number);
            if(strcmp(name, filename) == 0)
            {
                delete_inode(inode_number);
                delete_block(cur_dir->blocks[i]);
                cur_dir->blocks[i] = -1;
                free(cur_block);
                break;
            }
            //TODO add support of errors about non-file types tried to use cat on
            free(cur_block);
        }
    }
    dump_inode(cur_directory, cur_dir);
    free(cur_dir);
}


void cat(char* filename)
{
    struct inode* cur_dir = create_node();
    read_inode(cur_directory, cur_dir);
    char name[128], type[10];
    int inode_number;
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] != -1)
        {
            int block_number = cur_dir->blocks[i];
            struct defblock* cur_block = create_block();
            read_block(block_number, cur_block);
            sscanf(cur_block->data, "%s %s %d", name, type, &inode_number);
            if(strcmp(type, "file") == 0 && strcmp(name, filename) == 0)
            {
                struct inode* cur_node = create_node();
                read_inode(inode_number, cur_node);
                for(int i = 0; i < inode_block_num; ++i)
                {
                    if(cur_node->blocks[i] != -1)
                    {
                        out_block(cur_node->blocks[i]);
                    }
                }
                free(cur_node);
                free(cur_block);
                break;
            }
            //TODO add support of errors about non-file types tried to use cat on
            free(cur_block);
        }
    }
    printf("\n");
    free(cur_dir);
}

void mkdir(char *name)
{
    add_dir(name);
}

void ls()
{
    struct inode* cur_dir = create_node();
    read_inode(cur_directory, cur_dir);
    char name[128], type[10];
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] != -1)
        {
            int block_number = cur_dir->blocks[i];
            struct defblock* cur_block = create_block();
            read_block(block_number, cur_block);
            sscanf(cur_block->data, "%s", name);
            printf("%s ", name);
            free(cur_block);
        }
    }
    printf("\n");
    free(cur_dir);
}

void cd(char* dirname)
{
    if(strcmp(dirname, "/") == 0)
    {
        cur_directory = 0;
        return;
    }
    struct inode* cur_dir = create_node();
    read_inode(cur_directory, cur_dir);
    char name[128], type[10];
    int inode_number;
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] != -1)
        {
            int block_number = cur_dir->blocks[i];
            struct defblock* cur_block = create_block();
            read_block(block_number, cur_block);
            sscanf(cur_block->data, "%s %s %d", name, type, &inode_number);
            if(strcmp(type, "dir") == 0 && strcmp(name, dirname) == 0)
            {
                cur_directory = inode_number;
                free(cur_block);
                break;
            }
            //TODO add support of errors about non-file types tried to use cat on
            free(cur_block);
        }
    }
    printf("\n");
    free(cur_dir);
}


void create_file_system()
{
    FILE *f = fopen(path, "wb+");
    dump_superblock(f);
    dump_bitmap_inodes(f);
    dump_bitmap_blocks(f);
    dump_root_inode(f);
    dump_inodes(f);
    dump_blocks(f);
    fclose(f);

}

void ls_test()
{
    create_file_system();
    char* x = "lol";
    add_file("haha", x);
    add_file("kokoko", x);
    mkdir("thisisdirrr");
    ls();
    cat("haha");
    cat("kokoko");
    cd("thisisdirrr");
    add_file("jojo", "O.o");
    cat("jojo");
    ls();

}

void greetings()
{
    printf("HELLO THERE, USER OF THIS SMALL FS!\n");
    printf("HERE ARE THINGS YOU CAN DO WITH FS:");
    printf("PRINT clear TO CREATE BRAND NEW FS\n");
    printf("PRINT ls TO SHOW ALL FILES IN CURRENT DIRECTORY\n");
    printf("PRINT exit TO CLOSE FS\n");
    printf("PRINT mkdir AND *name* AFTERWARDS TO CREATE DIRECTORY\n");
    printf("PRINT cd AND *name* AFTERWARDS TO CHANGE DIRECTORY (TYPE ONE SLASH AS A NAME, TO GET BACK TO ROOT DIR)\n");
    printf("PRINT create AND *name* AND *content* AFTERWARDS TO CREATE FILE\n");
    printf("PRINT rmrf AND *name* AFTERWARDS TO DELETE DIRECTORY/FILE\n");
    printf("PRINT cat AND *name* AFTERWARDS TO DISPLAY FILE\n");
    printf("PRINT help TO SEE THIS MESSAGE\n");
}

void interactions_with_user()
{
    char s[128];
    printf("mini-mini-fs: user$ ");
    while(scanf("%s", s))
    {
        if(strcmp(s, "exit") == 0)
        {
            break;
        }
        if(strcmp(s, "ls") == 0)
        {
            ls();
        }
        if(strcmp(s, "mkdir") == 0)
        {
            char name[128];
            scanf("%s", name);
            mkdir(name);
        }
        if(strcmp(s, "create") == 0)
        {
            char name[128], content[1024];
            scanf("%s %s", name, content);
            add_file(name, content);
        }
        if(strcmp(s, "rmrf") == 0)
        {
            char name[128];
            scanf("%s", name);
            rmrf(name);
        }
        if(strcmp(s, "cat") == 0)
        {
            char name[128];
            scanf("%s", name);
            cat(name);
        }
        if(strcmp(s, "cd") == 0)
        {
            char name[128];
            scanf("%s", name);
            cd(name);
        }
        if(strcmp(s, "clear") == 0)
        {
            create_file_system();
        }
        if(strcmp(s, "help") == 0)
        {
            greetings();
        }
        printf("mini-mini-fs: user$ ");
    }
}