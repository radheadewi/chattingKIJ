
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
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
    t->sock_id=sock;

    strcpy(t->username,nama);
    t->next=tail;
    pntr->next=t;
    contuser=contuser+1;
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

struct node *cek_nama(char *nama)
{
    struct node *pntr;
    pntr=head;

    while(pntr->next!=tail)
    {
        pntr=pntr->next;
        if (strcmp(pntr->username,nama)==0)
        {
            printf("pntrnama:%s,%d\n", pntr->username, pntr->sock_id);
            
            return pntr;
        }
    }
    pntr->sock_id = -1;
    return pntr;
}

void ListAll(int socket){
    struct node *pntr;
    int sock = socket;
    char kirim[1024];
    bzero(&kirim, sizeof(kirim));
    sprintf(kirim,"LISTUSER-");
    char listnya[1024];
    bzero(&listnya, sizeof(listnya));
    pntr=head;
    if(contuser==1){
        sprintf(kirim,"%s%s:\n",kirim,pntr->next->username);
        printf("%s\n", kirim);
        write(sock, kirim, sizeof(kirim));
        //printf("list cuma satu\n" );
    }
    else{
        while(pntr->next!=tail){     
            pntr=pntr->next;
            sprintf(listnya, "%s%s:", listnya, pntr->username);
            printf("%d,%s\n",pntr->sock_id ,pntr->username);
        }
        sprintf(kirim, "%s%s\n",kirim, listnya);
        printf("%s\n",kirim );
        write(sock, kirim, strlen(kirim));
        //printf("list > 1\n" );
    }



}


/*
struct node *cek_id(int id_socket)
{
    struct node *pntr;
    pntr=head;

    while(pntr->next!=tail)
    {
        pntr=pntr->next;
        if (pntr->sock_id==id_socket)
        {
            printf("pntrnama: %s\n %d\n", pntr->username, pntr->sock_id);
            
            return pntr;
        }
    }
    pntr->sock_id = -1;
    return pntr;
}

*/

void List()
{
    struct node *pntr;
    printf("username:  ");
    pntr=head;
    while (pntr != tail) {
        printf("%s\n",pntr->username);
        pntr = pntr->next;
    }
}

void *connection_handler(void *socket_desc)
{
   
    int sock = *(int*)socket_desc;
    //printf("1\n");
    int read_size;
    char messag[2000] , client_message[2000];
    //printf("1.2\n");
   
    read_size = recv(sock, client_message, 2000, 0);
    //printf("2\n");
    client_message[read_size] = '\0';
    
    printf("%s\n",client_message );
    char *nama_baru;
    //printf("3\n");
    nama_baru = strtok(client_message,":");
    nama_baru = strtok(NULL,":");

    printf("%s\n",nama_baru );
    add(sock, nama_baru);
//    char *data_user = "Username : ";
//    write(sock , data_user , strlen(client_message));
//    memset(client_message, 0, 2000);
     
    
        //Receive a message from client
    while( (read_size = recv(sock , messag , 2000 , 0)) > 0 )
    {
        printf("%s\n",messag );
        char *tmp1, *tmp2, *tmp3;
        tmp1 = strtok(messag, ":");
        printf("%s\n", tmp1);
        if(strcmp(tmp1,"REFRESH") == 0)
        {
            ListAll(sock);
            printf("1. %s\n", messag);
        }

        else if(strcmp(tmp1, "TALKTO") == 0)
        {          
            struct node *asal , *tujuan;
            char data_kembalian[1024];
            //bzero(&data_kembalian, strlen(data_kembalian));
            sprintf(data_kembalian, "FROM:");
            tmp2 = strtok(NULL, ":");
            tmp3 = strtok(NULL,"\r\n");
            // printf("%s , %s , %s\n",tmp1,tmp2,tmp3);
            tujuan = cek_nama(tmp2);
            sprintf(data_kembalian, "%s%s:%s\n", data_kembalian, nama_baru , tmp3);
            printf("%s\n", data_kembalian);
            printf("Socket id : %d\n",tujuan->sock_id );
            int cek = write(tujuan->sock_id, data_kembalian, strlen(data_kembalian));
            //printf("%d\n",cek );
            printf("2. %s\n", messag);
        }
                
        else if(strcmp(tmp1,"BYE") == 0)
        {
            char *bye = "Client terputus";
            // printf("%s : %s\n",bye,data_user);
            puts("Client disconnected");
            write(sock , bye , sizeof(bye));
            fflush(stdout);
            break;
            // bye masih belum berfungsi
        }
        else if( tmp1 == NULL)
        {
            char *bye = "NOTE : Data yang dikirim kosong";
            write(sock , bye , sizeof(bye));
        }
        bzero(&messag, sizeof(messag));
    }
     
    if(read_size == -1)
        {
            perror("recv failed");
        }   
    
    return 0;
} 



int main()
{

    int status;
   

    char *konek = "200OK\r\n",
        *login = "300OK\r\n",
        *temp;

    char buf[1024];

    struct sockaddr_in host , client;   
   
    printf("Creating a socket...\n");
    int socketfd ; 
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
  

    if (socketfd == -1) printf("socket error\n");
    printf("Binding socket...\n");

    host.sin_family = AF_INET;
    host.sin_addr.s_addr = INADDR_ANY;
    host.sin_port  = htons(9999);

    int yes = 1;
  //  status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, (struct sockaddr *)&host, sizeof(host));
    if (status == -1)  printf("bind error\n");
    
    printf("Listen()ing for connections...\n");
    
    status =  listen(socketfd, 5);
    if (status == -1)  printf("Listen()ing error888888\n");

    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    
    pthread_t thread_id;
    init();

    while(new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size)) 
    {
        if (new_sd == -1)
        {
            printf("Listen()ing error\n");
            //break;
        }
     /*else
        {
            printf("Connection accepted. Using new socketfd : %d\n", new_sd );
        }
*/      else {
            printf("Connection accepted. Using new socketfd : %d\n", new_sd );
            int cek = pthread_create( &thread_id , NULL , connection_handler , (void*) &new_sd); 
            if(cek < 0) {
                printf("Gagal membuat thread");
                return 1;
            }
        }
    /*    if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_sd) < 0)
        {
            perror("could not create thread");
            return 1;
        }
*/   
    }
    return 0 ;
}

