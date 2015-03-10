
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h> //strlen
#include <arpa/inet.h> //inet_addr
#include <unistd.h> //write
#include <pthread.h> //for threading , link with lpthread
#include <fcntl.h>

pthread_mutex_t lock;


struct node{
    int sock_id;
    char username[100];
    struct node *next;

};

struct node *head, *tail;
int contuser=0;

void init()
{
    head=(struct node *)malloc(sizeof(*head));
    tail=(struct node *)malloc (sizeof(*tail));
    head->next=tail;
    tail->next=tail;
}

struct node* add(int sock, char nama[])
{
    struct node *pntr;
    struct node *t;
    pntr=head;
    while (pntr->next!=tail ) pntr=pntr->next;

    t=(struct node *)malloc(sizeof(*t));
    t->sock=nilai;

    strcpy(t->nama,nama);
    t->next=tail;
    pntr->next=t;
    countuser=countuser+1;
    return pntr;
    /* data */
};


void delete(struct node *pntr)
{
    struct node *baru;
    baru=pntr->next;
    pntr->next=pntr->next->next;
    contuser=contuser-1;
    free(baru);
}

struct node * getnode(char nama[])
{
    struct node *pntr;
    pntr=head;

    while(pntr->next!=tail)
    {
        pntr=pntr->next;
        if (strcmp(pntr->nama,nama)==0)
        {
            printf("pntrnama: %s\n %d\n", pntr->nama, pntr->sock_id);
            
            return pntr;
        }
    }
    return 0;
}


void List()
{
    struct node *pntr;
    printf("username:  ");
    pntr=head;
    while (pntr != tail) {
        printf("%s\n",pntr->nama);
        pntr = pntr->next;
    }
}


int main()
{

   
    char *konek = "200OK\r\n",
        *login = "300OK\r\n",
        *temp;

    char buf[1024];

    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    host_info.ai_flags = AI_PASSIVE;
   
    printf("Creating a socket...\n");
    int socketfd ; // The socket descripter
    socketfd = socket(AF_INET, SOCK_STREAM, host_info_list->ai_protocol);
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

    write(new_sd, konek, strlen(konek));    
    
    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    

    while(new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size)) 
    {
        if (new_sd == -1)
        {
            printf("Listen()ing error\n");
            break;
        }
        else
        {
            printf("Connection accepted. Using new socketfd : %d\n", new_sd );
        }

        // Login

        read(new_sd,buf,strlen(buf),0);
        temp = strtok(buf,":");
        temp = strtok(NULL,":");

        if(strcmp(temp,"raga")==0 || strcmp(temp,"randy")==0 || strcmp(temp,"fandy")==0 || strcmp(temp,"radhea")==0 ){

            //login array

            strcat(login,":");
            strcat(login,temp);
            write(new_sd, login, strlen(login));
        }

    }

return 0 ;


}





