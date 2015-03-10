
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

struct node *cek(char *nama)
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
    pntr->sock_id = -1;
    return pntr;
}

struct node *cek_id(int id_socket)
{
    struct node *pntr;
    pntr=head;

    while(pntr->next!=tail)
    {
        pntr=pntr->next;
        if (strcmp(pntr->sock_id,id_socket)==0)
        {
            printf("pntrnama: %s\n %d\n", pntr->nama, pntr->sock_id);
            
            return pntr;
        }
    }
    pntr->sock_id = -1;
    return pntr;
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


void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Koneksi Telah Terbuat. Masukkan Username : ";
    write(sock , message , strlen(message));

    read_size = recv(sock, client_message, 2000, 0);
    // end of string
    client_message[read_size] = '\0';
     //Cek Login ------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



    //Masukkan ke List------------>>>>>>>>>>>>>>>>>>>>>>>>>>>




    //-----------
    char data_user[3000] = "";
    data_user = "Username : ";
    strcat(data_user, client_message);
    write(sock , data_user , strlen(client_message));
    
    //clear the message buffer
    memset(client_message, 0, 2000);
     
     int socket_id_user;
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) >= 0 )
    {
        char *tmp;
        tmp = strtok(client_message, ":");
        if(strcmp(client_message,"refresh" ) == 0 || strcmp(client_message,"Refresh") == 0 || strcmp(client_message,"REFRESH") == 0)
        {
            char list_user[3000];
            // Disini string untuk list--->>>>>>>>>>>>>>>>

            //input variabel list_user;


            //-----------------------//

            write(sock, list_user, strlen(list_user));
            memset(list_user,0,3000);
        }
        // Untuk char harus TalkTo , talkto, TALKTO.
        else if(strcmp(tmp,"TalkTo") == 0 || strcmp(tmp,"talkto") == 0 || strcmp(tmp, "TALKTO") == 0)
        {
            char *data_kembalian;
            tmp = strtok(NULL, ".");
            if(tmp == NULL)
            {
                
                data_kembalian= "Harus diakhiri tanda titik.";
                //end of string marker
                write(sock , data_kembalian , strlen(data_kembalian));
            }
            else
            {
                //------------Cek username di list <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


                //-----------------
                socket_id_user = cek(tmp);
                write(sock , data_kembalian , strlen(data_kembalian));
            }
        }
        else if(strcmp(tmp,"BYE") == 0 || strcmp(tmp,"bye") == 0)
        {
            char *bye = "Client terputus";
            printf("%s : %s\n",bye,data_user);
            puts("Client disconnected");
            write(sock , bye , strlen(bye));
            fflush(stdout);
            break;
        }
        else if( tmp == NULL)
        {
            char *bye = "Data yang dikirim kosong";
            write(sock , bye , strlen(bye));
        }
        else
        {
            struct node *pengirim;
            pengirim = cek(sock);
            strcat(pengirim->nama, ":");
            strcat(pengirim->nama, client_message);
            write(socket_id_user, pengirim->nama, strlen(pengirim->nama));
            memset(client_message,0,2000);
        }
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
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
    
    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    
    pthread_t thread_id;


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


        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &new_sd) < 0)
        {
            perror("could not create thread");
            return 1;
        }

        
    }

return 0 ;


}





