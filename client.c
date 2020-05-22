#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <errno.h>

#include <arpa/inet.h> 

int make_new_sockW(char* sendBuff)
{
    int sockWfd = 0;
    
    struct sockaddr_in serv_addr_out; 
    char porti[24];

    memset(sendBuff, '0',sizeof(sendBuff));
    if((sockWfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);

    memset(&serv_addr_out, '0', sizeof(serv_addr_out)); 

    serv_addr_out.sin_family = AF_INET;
    serv_addr_out.sin_port = htons(5003); 

    strcpy(porti, "127.0.0.1");



                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);

    if(inet_pton(AF_INET,porti, &serv_addr_out.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);

    if( connect(sockWfd, (struct sockaddr *)&serv_addr_out, sizeof(serv_addr_out)) < 0)
    {
       printf("\n Error : Connect Failed 2 \n");
       return 1;
    } 

                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);
    return sockWfd;
}

int make_new_sockR(char* recvBuff)
{
    int sockRfd = 0, n = 0;
    struct sockaddr_in serv_addr_in; 


                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);
    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockRfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 


                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);
    memset(&serv_addr_in, '0', sizeof(serv_addr_in)); 

    serv_addr_in.sin_family = AF_INET;
    serv_addr_in.sin_port = htons(5002); 

    char porti[24];
        strcpy(porti, "127.0.0.1");


                printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);

    if(inet_pton(AF_INET,porti, &serv_addr_in.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

             printf("%s\n", "I HAVE BEEN HERE");
    fflush(stdout);

    if(connect(sockRfd, (struct sockaddr *)&serv_addr_in, sizeof(serv_addr_in)) < 0)
    {
       printf("\n Error : Connect Failed 1 \n");
       return 1;
    } 

                printf("%s\n", "I HAVE BEEN HERE");
    return sockRfd;
}

int main(int argc, char *argv[])
{
    
    char recvBuff[1024];
    char sendBuff[1024];
    
    fflush(stdout);


    
    int tik = 0;

    while(1)
    {
        char s[128];
        scanf("%s", s);
        sleep(1);
        int sockWfd = make_new_sockW(sendBuff);
        printf("%d\n", sockWfd);
        strcpy(sendBuff, s);
        printf("%s\n", "EASYPEASY");
        write(sockWfd, sendBuff, strlen(sendBuff));
        close(sockWfd);
        tik++;
        if(strcmp(s, "exit") == 0)
        {
            break;
        }
        /*int sockRfd = make_new_sockR(recvBuff);
        sleep(1);
        int n = 0;
        while ( (n = read(sockRfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {

            recvBuff[n] = 0;
            printf("%s\n", recvBuff);
        }
        close(sockRfd);*/
    }
    
    printf("%s\n", "EASYPEASY2");
    return 0;
}