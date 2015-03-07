
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{

    int status;
    struct addrinfo host_info;
    struct addrinfo *host_info_list;
    memset(&host_info, 0, sizeof host_info);

    printf("Setting up the structs...\n");

    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    host_info.ai_flags = AI_PASSIVE;
    status = getaddrinfo(NULL, "6666", &host_info, &host_info_list);

    if (status != 0)  printf("getaddrinfo error\n");

    printf("Creating a socket...\n");
    int socketfd ; // The socket descripter
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
    if (socketfd == -1) printf("socket error\n");

    printf("Binding socket...\n");


    int yes = 1;
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)  printf("bind error\n");

    printf("bind error\n");
    printf("Listen()ing for connections...\n");
    status =  listen(socketfd, 5);
    if (status == -1)  printf("Listen()ing error\n");


    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_sd == -1)
    {
        printf("Listen()ing error\n");
    }
    else
    {
        printf("Connection accepted. Using new socketfd : %d\n", new_sd );
    }


       
    char *msg = "thank you.";
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(new_sd, msg, len, 0);

    std::cout << "Stopping server..." << std::endl;
    freeaddrinfo(host_info_list);
    close(new_sd);
    close(socketfd);

return 0 ;


}



