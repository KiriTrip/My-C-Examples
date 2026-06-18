#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(-1);
    }

    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct addrinfo hint, *res;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, "8080", &hint, &res) != 0)
    {
        perror("Getaddrinfo error");
        exit(-1);
    }

    int bind_result = bind(sockfd, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);

    // Listen for incoming connections!
    int listen_result = listen(sockfd, 20);
    if (listen_result < 0)
    {
        perror("Listen error");
        exit(-1);
    }

    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    int new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size);
    if (new_fd < 0)
    {
        perror("Accept error");
        exit(-1);
    }
    
    int max_len = 1000;
    char received_request[max_len];
    memset(received_request, 0, max_len);
    int num_bytes = recv(new_fd, received_request, max_len, 0);
    if (strncmp(received_request, "GET", 3) == 0)
    {
        printf("Received HTTP GET request!\n");

        // We respond to the HHTP GET request
        char *status_line = "HTTP/1.1 200 OK\r\n";
        send(new_fd, status_line, strlen(status_line), 0);
        
        char *headers = "Content-Type: text/html\r\n\r\n";
        send(new_fd, headers, strlen(headers), 0);
        
        FILE* index_file = fopen("index.html", "r");
        char c;
        while ( (c = getc(index_file)) != EOF )
        {
            send(new_fd, &c, 1, 0);
        }
    }
    else
    {
        printf("Received NON-GET request. Ignoring...\n");
        exit(-1);
    }

    close(new_fd);
    close(sockfd);
    return 0;
}