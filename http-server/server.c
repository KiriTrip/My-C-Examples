#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(-1);
    }
    struct addrinfo hint, *res;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "8080", &hint, &res);
    int bind_result = bind(sockfd, res->ai_addr, res->ai_addrlen);

    printf("Bind result is: %d\n", bind_result);

    while (1)
    {
        // Some kind of request must be received here
        printf("Waiting for request ...\n");
        sleep(1);
    }
}