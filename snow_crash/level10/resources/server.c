#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int sockfd, new;
    struct sockaddr_in servaddr;
    int ncli = 0;
    char buff[4096];
    char *msg = NULL;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return (1);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433);
    servaddr.sin_port = htons(6969);
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
        return (1);
    write(1, "socket bound\n", 14);
    if (listen(sockfd, 10) != 0)
        return (1);
    write(1, "listening...\n", 14);
    new = accept(sockfd, NULL, NULL);
    if (new < 0)
        return (1);
    write(1, "connection accepted\n", 21);
    bzero(&buff, 4096);
    wait(5);
    int received = recv(new, buff, 4095, 0);
    write(1, buff, received);
    write(1, "\n", 1);
    bzero(&buff, 4096);
    received = recv(new, buff, 4095, 0);
    write(1, buff, received);
	close(sockfd);
    close(new);
    return (0);
}