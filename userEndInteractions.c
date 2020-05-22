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
    fflush(stdout);
    free(cur_dir);
}

void ret_text(char* filename, char* place)
{
  strcpy(place, "");
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
            char cur_place[block_size];
            ret_block_text(cur_node->blocks[i], cur_place);
            strcat(place, cur_place);
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
    int non_zero = 0;
    for(int i = 0; i < inode_block_num; ++i)
    {
        if(cur_dir->blocks[i] != -1)
        {
            int block_number = cur_dir->blocks[i];
            struct defblock* cur_block = create_block();
            read_block(block_number, cur_block);
            sscanf(cur_block->data, "%s", name);
            if(strcmp(name, ".") != 0 && strcmp(name, "..") != 0)
            {
              non_zero = 1;
              printf("%s ", name);
            }
            free(cur_block);
        }
    }
    if(non_zero != 0)
      printf("\n");
    fflush(stdout);
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
    int changed = 0;
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
                changed = 1;
                break;
            }
            //TODO add support of errors about non-file types tried to use cat on
            free(cur_block);
        }
    }
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
    printf("PRINT pwd TO GET YOUR CURRENT PLACE IN FS\n");
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
        if(strcmp(s, "pwd") == 0)
        {
          cur_path();
        }
        if(strcmp(s, "cp") == 0)
        {
          char path1[LOCAL_PATH_MAX], path2[LOCAL_PATH_MAX];
          scanf("%s %s", path1, path2);
          cp(path1, path2);
        }
        if(strcmp(s, "mv") == 0)
        {
          char path1[LOCAL_PATH_MAX], path2[LOCAL_PATH_MAX];
          scanf("%s %s", path1, path2);
          move(path1, path2);
        }
        if(strcmp(s, "load") == 0)
        {
          char path1[LOCAL_PATH_MAX];
          scanf("%s", path1);
          load(path1);
        }
        if(strcmp(s, "store") == 0)
        {
          char path1[LOCAL_PATH_MAX];
          scanf("%s", path1);
          store(path1);
        }
        printf("mini-mini-fs: user$ ");
    }
}

void cur_path()
{
  int full_path[100];
  int cur_place = 0;
  char absolute_path[256];
  while(true)
  {
    if(cur_directory == 0)
    {
      full_path[cur_place] = cur_directory;
      break;
    }
    else
    {
      full_path[cur_place] = cur_directory;
      cd("..");
      cur_place++;
    }
  }

  int prev_place = 0;
  while(cur_place >= 0)
  {
    if(full_path[cur_place] != 0)
    {
      char name[128];
      int result_code = get_name_by_id(prev_place, full_path[cur_place], name);
      if(result_code == 1)
        return;
      cd(name);
      strcat(absolute_path, name);
    }
    strcat(absolute_path, "/");
    prev_place = full_path[cur_place];
    cur_place--;
  }
  printf("%s\n", absolute_path);
}

void cur_path_manual(char* place)
{
  int full_path[100];
  int cur_place = 0;
  char absolute_path[256];
  while(true)
  {
    if(cur_directory == 0)
    {
      full_path[cur_place] = cur_directory;
      break;
    }
    else
    {
      full_path[cur_place] = cur_directory;
      cd("..");
      cur_place++;
    }
  }

  int prev_place = 0;
  while(cur_place >= 0)
  {
    if(full_path[cur_place] != 0)
    {
      char name[128];
      int result_code = get_name_by_id(prev_place, full_path[cur_place], name);
      if(result_code == 1)
        return;
      cd(name);
      strcat(absolute_path, name);
    }
    strcat(absolute_path, "/");
    prev_place = full_path[cur_place];
    cur_place--;
  }
  strcpy(place, absolute_path);
}

int get_next_dir_name(int start, char* long_path, char* place)
{
  char some;
  int i = start;
  int j = 0;
  while(i < strlen(long_path))
  {
    place[j] = long_path[i];
    if(long_path[i] == '/')
    {
      //long_path[i] = '\0';
      i++;
      break;
    }
    i++;
    j++;
  }
  place[j] = '\0';
  return i;
}

void cp(char* filename, char* destination)
{
  char file_content[inode_block_num*block_size];
  char full_file_path[LOCAL_PATH_MAX];
  char full_destination_path[LOCAL_PATH_MAX];
  //cur_path_manual(full_file_path);
  //cur_path_manual(full_destination_path);
  strcat(full_file_path, filename);
  strcat(full_destination_path, destination);
  char cur_pathik[LOCAL_PATH_MAX];
  cur_path_manual(cur_pathik);
  //cd("/");

  char cur_cur_dir[LOCAL_PATH_MAX];

  int start_point = 1;
  while(start_point < strlen(full_file_path))
  {
    start_point = get_next_dir_name(start_point, full_file_path, cur_cur_dir);
    if(start_point < strlen(full_file_path)) {
      cd(cur_cur_dir);
    }
    else
    {
      ret_text(cur_cur_dir, file_content);
    }
  }


  cd("/");

  char destin_dirs[LOCAL_PATH_MAX];

  start_point = 1;
  while(start_point < strlen(full_destination_path) && strcmp(full_destination_path, "/") != 0)
  {
    start_point = get_next_dir_name(start_point, full_destination_path, destin_dirs);
    if(start_point < strlen(full_destination_path)) {
      cd(destin_dirs);
    }
    else
    {
      cd(destin_dirs);
    }
  }

  add_file(cur_cur_dir, file_content);

  cd("/");

  start_point = 1;
  while(start_point < strlen(cur_pathik))
  {
    start_point = get_next_dir_name(start_point, cur_pathik, cur_cur_dir);
      cd(cur_cur_dir);
  }

}

void move(char* filename, char* destination)
{
  cp(filename, destination);
  int i = 0;
  if(filename[0] == '/')
    i++;
  rmrf(filename + i);
}

void load(char *filename)
{

  char path_to_f[LOCAL_PATH_MAX];
  strcpy(path_to_f, "/home/parallels/Desktop/");
  strcat(path_to_f, filename);
  fflush(stdout);
  int fd = open(path_to_f, O_RDONLY);
  char buf[MAX_FILE];
  int res = read(fd, buf, MAX_FILE);
  add_file(filename, buf);
  close(fd);
}

void store(char *filename)
{
  char path_to_f[LOCAL_PATH_MAX];
  strcpy(path_to_f, "/home/parallels/Desktop/");
  strcat(path_to_f, filename);



  char buf[MAX_FILE];
  ret_text(filename, buf);

  //SECOND WAY TO DO THIS, JUST IN CASE
  FILE *f = fopen(path_to_f, "wb+");
  printf("%s\n", path_to_f);
  fwrite(buf, sizeof(char), strlen(buf), f);
  fclose(f);

  /*int fd = open(filename, O_WRONLY);
  if(fd == -1)
  {
    int fd2 = open(filename, O_CREAT);
    close(fd2);
    fd = open(filename, O_WRONLY);
  }

  write(fd, buf, strlen(buf));
  close(fd);*/
}