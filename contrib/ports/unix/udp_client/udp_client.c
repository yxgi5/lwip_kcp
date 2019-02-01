#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAXLINE 80

#define SERV_PORT 7
int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int sockfd, n;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    socklen_t servaddr_len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.0.2", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        n  = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&servaddr,sizeof(servaddr));
        if (n == -1)
        {
            perror("sendto error");
        }
        n = recvfrom(sockfd, buf, MAXLINE, 0, NULL, 0);
        if (n == -1)
        {
            perror("recvfrom error");
        }
        write(1,buf,n);
    }
    close(sockfd);
    return 0;
}

