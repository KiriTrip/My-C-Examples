#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(-1);
    }
    struct sockaddr addr;
    int bind_result = bind(sockfd, &addr, sizeof(struct sockaddr));

    printf("Bind result is: %d\n", bind_result);

    while (1)
    {
        // Some kind of request must be received here
        printf("Waiting for request ...\n");
        sleep(1);
    }
}