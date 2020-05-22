#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "globals.h"
#include "defblock.h"
#include "defblock.c"
#include "inode.h"
#include "inode.c"
#include "superblock.h"
#include "superblock.c"
#include "defblock.h"
#include "bitoperations.h"
#include "bitoperations.c"
#include "fileInteractions.h"
#include "fileInteractions.c"
#include "userEndInteractions.h"
#include "userEndInteractions.c"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <arpa/inet.h> 

void some_test()
{
  char* pathik = "/lol/haha/kek";
  char place[LOCAL_PATH_MAX];
  int start_point = 1;
  while(start_point < strlen(pathik))
  {
    start_point = get_next_dir_name(start_point, pathik, place);
    if(start_point < strlen(pathik))
      printf("%s ", place);
  }
}

void init()
{
    inode_num = 128;
    block_num = 128;
    block_size = 128;
    inode_block_num = 16;
    free_inodes = inode_num - 1;
    free_blocks = block_num;
    cur_id = 1;
    cur_directory = 0;
    //cwd = malloc(PATH_MAX*sizeof(char ));
    //to_dir_path = malloc(PATH_MAX*sizeof(char ));;
    path;
    LOCAL_PATH_MAX = PATH_MAX;
    MAX_FILE = inode_block_num*block_size;
    offset_blocks = offset_inodes + sizeof(struct inode);
    offset_blocksbitmap = offset_inodebitmap + inode_num;
    offset_inodes = offset_blocksbitmap + block_num;
}

FILE* okie;

void WriteLog(char* data)
{

    fprintf(okie, "%s", data);
    fflush(okie);
    
}

void SetPidFile(char* Filename)
{
    char okay[128];
    sprintf(okay, "[PID] Pid num of Monitor is %u\n", getpid());
    WriteLog(okay);
}

void read_from_client(char* s, int listenRfd)
{
  char recvBuff[200];
  int connRfd = accept(listenRfd, (struct sockaddr*)NULL, NULL);
                int n = 0;
                strcpy(s, "");
                while ( (n = read(connRfd, recvBuff, sizeof(recvBuff)-1)) > 0)
                {
                    char okay[120];
                    sprintf(okay, "%d\n", n);
                    WriteLog(okay);
                    recvBuff[n] = '\0';
                    strcat(s, recvBuff);
                    WriteLog(s);
                    WriteLog("\n");
                }
                s[strlen(s)] = '\0';
                WriteLog(s);
                WriteLog("\n");
                close(connRfd);
}


int WorkProc()
{
  freopen("/home/parallels/Desktop/f", "w", stdout);
    int             status;
    WriteLog("[DAEMON] Started\n");
    status = 0;
    if (!status)
    {
        

        char okay[128];
        sprintf(okay, "[PID] Pid num of Worker is %u\n", getpid());
        WriteLog(okay);

        int MyTik = 0;
        time_t ticks;

        int listenWfd = 0, connfd = 0;
        struct sockaddr_in serv_addr_out; 

        char sendBuff[1025];

        listenWfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serv_addr_out, '0', sizeof(serv_addr_out));
        memset(sendBuff, '0', sizeof(sendBuff)); 

        serv_addr_out.sin_family = AF_INET;
        serv_addr_out.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr_out.sin_port = htons(5002); 

        WriteLog("NOT BINDED YET");

        bind(listenWfd, (struct sockaddr*)&serv_addr_out, sizeof(serv_addr_out)); 

        WriteLog("OK");

        int listenRfd = 0;
        struct sockaddr_in serv_addr_in; 

        char recvBuff[1025];
         

        listenRfd = socket(AF_INET, SOCK_STREAM, 0);
        memset(&serv_addr_in, '0', sizeof(serv_addr_in));
        memset(recvBuff, '0', sizeof(recvBuff)); 

        serv_addr_in.sin_family = AF_INET;
        serv_addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr_in.sin_port = htons(5003); 

        bind(listenRfd, (struct sockaddr*)&serv_addr_in, sizeof(serv_addr_in)); 

        WriteLog("OK2");

        listen(listenRfd, 10); 
        listen(listenWfd, 10); 

        WriteLog("OK3\n");

        char porti[24];
        strcpy(porti, "127.0.0.1");

        while (MyTik<5)  
        {
            char s[128];
            printf("mini-mini-fs: user$ ");

            
            
             

            int n = 0;

            //sleep(3);


            while(true)
            {
                int connRfd = accept(listenRfd, (struct sockaddr*)NULL, NULL);
                n = 0;
                strcpy(s, "");
                while ( (n = read(connRfd, recvBuff, sizeof(recvBuff)-1)) > 0)
                {
                    sprintf(okay, "%d\n", n);
                    WriteLog(okay);
                    recvBuff[n] = '\0';
                    strcat(s, recvBuff);
                    WriteLog(s);
                    WriteLog("\n");
                }
                s[strlen(s)] = '\0';
                WriteLog(s);
                WriteLog("\n");
                close(connRfd);

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
                    read_from_client(name, listenRfd);
                    mkdir(name);
                }
                if(strcmp(s, "create") == 0)
                {
                    char name[128], content[1024];
                    read_from_client(name, listenRfd);
                    read_from_client(content, listenRfd);
                    //scanf("%s %s", name, content);
                    add_file(name, content);
                }
                if(strcmp(s, "rmrf") == 0)
                {
                    char name[128];
                    read_from_client(name, listenRfd);
                    //scanf("%s", name);
                    rmrf(name);
                }
                if(strcmp(s, "cat") == 0)
                {
                    char name[128];
                    read_from_client(name, listenRfd);
                    //scanf("%s", name);
                    cat(name);
                }
                if(strcmp(s, "cd") == 0)
                {
                    char name[128];
                    read_from_client(name, listenRfd);
                    //scanf("%s", name);
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
                  read_from_client(path1, listenRfd);
                  read_from_client(path2, listenRfd);
                  //scanf("%s %s", path1, path2);
                  cp(path1, path2);
                }
                if(strcmp(s, "mv") == 0)
                {
                  char path1[LOCAL_PATH_MAX], path2[LOCAL_PATH_MAX];
                  read_from_client(path1, listenRfd);
                  read_from_client(path2, listenRfd);
                  //scanf("%s %s", path1, path2);
                  move(path1, path2);
                }
                if(strcmp(s, "load") == 0)
                {
                  char path1[LOCAL_PATH_MAX];
                  read_from_client(path1, listenRfd);
                  //scanf("%s", path1);
                  load(path1);
                }
                if(strcmp(s, "store") == 0)
                {
                  char path1[LOCAL_PATH_MAX];
                  read_from_client(path1, listenRfd);
                  //scanf("%s", path1);
                  store(path1);
                }
                printf("mini-mini-fs: user$ ");
                fflush(stdout);
            }
            if(strcmp(recvBuff, "ho") == 0)
            {
                WriteLog("WOW\n");
                //close(connRfd);
                WriteLog("WOW\n");
                int connWfd = accept(listenWfd, (struct sockaddr*)NULL, NULL); 
                WriteLog("WOW\n");
                ticks = time(NULL);
                snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
                WriteLog("WOW\n");
                //read(connfd, sendBuff, 2);
                write(connWfd, sendBuff, strlen(sendBuff)); 
                WriteLog("WOW\n");
                close(connWfd);
                WriteLog("WOW\n");
            }
            else if(strcmp(recvBuff, "exit") == 0)
            {
                MyTik = 5;
            }
            else
            {
                //close(connRfd);
                //close(connRfd);
            }

            //WriteLog(sendBuff);

            
            sleep(1);
            sprintf(okay, "[DAEMON] Number of iters left %d\n", 1 - MyTik);
            WriteLog(okay);
            MyTik++;
       }

       close(listenRfd);
       close(listenWfd);

    }
    else
    {
        WriteLog("[DAEMON] Create work thread failed\n");
    }

    WriteLog("[DAEMON] Stopped\n");
    
    return 0;
}

int MonitorProc()
{
    int      pid;
    int      status;
    int      need_start = 1;

    SetPidFile("/home/parallels/Desktop/file.txt");
    for (;;)
    {
        if (need_start)
        {
            pid = fork();
        }
        
        need_start = 1;
        
        if (pid == -1)
        {
            WriteLog("[MONITOR] Fork failed ()\n");
        }
        else if (!pid)
        {
            status = WorkProc();
            exit(status);
        }
        else
        {
           
                
                status = WEXITSTATUS(status);
                if (status == 0)
                {     
                    WriteLog("[MONITOR] Child stopped\n");
                    
                    break;
                }
                else if (status != 0) 
                {
                    char okay[128];
                    sprintf(okay, "[MONITOR] Child restart with status%d\n", status);
                    WriteLog(okay);
                    WriteLog("KJDCJADB");
                }
           
        }
    }
    WriteLog("[MONITOR] Stop\n");
    return status;
}


int main() {
    init();
  //some_test();
  //return 0;
    printf("%s\n", "???");
    fflush(stdout);
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        fflush(stdout);
        path = malloc(strlen(cwd) + strlen("/file.txt"));
        strcpy(path, cwd);
        strcat(path,  "/");
        printf("%s\n", path);
        fflush(stdout);
        strcpy(to_dir_path, path);
        strcat(path,  "file.txt");
    }
    else
    {
        printf("SOMETHING WENT WRONG");
        return 1;
    }


    //greetings();
    fflush(stdout);
    //interactions_with_user();
    okie = fopen("/home/parallels/Desktop/file.txt", "w+");

    int      pid;
    int      status;
    int      need_start = 1;
    pid = fork();

    if (pid == -1)
    {
        printf("Error: Start Daemon failed ()\n");
        return -1;
    }
    else if (!pid)
    {
        
        setsid();
        chdir("/");
        /*close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);*/
        status = MonitorProc();
        fclose(okie);     
        return status;
    }
    else
    {
        return 0;
    }

    free(path);
    return 0;
}
