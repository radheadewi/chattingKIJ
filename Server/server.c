
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
            printf("pntrnama: %s\n %d\n", pntr->username, pntr->sock_id);
            
            return pntr;
        }
    }
    pntr->sock_id = -1;
    return pntr;
}

char ListAll(){
    struct node *pntr;
    char *listnya="LISTUSER-";
    pntr=head;
    while(pntr->next!=tail){
        pntr=pntr->next;
        strcat(listnya,pntr->username);
        strcat(listnya,":");
    }
    return *listnya;
}

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

/*string ListArray(){

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

    if(strcmp(client_message,"raga")==0 || strcmp(client_message,"randy")==0 || strcmp(client_message,"fandy")==0 || strcmp(client_message,"radhea")==0 ){
  //          //login array

     /*     strcat(login,":");
          strcat(login,client_message);
          write(new_sd, login, strlen(login));
    */

    //Masukkan ke List------------>>>>>>>>>>>>>>>>>>>>>>>>>>>

        add(sock, client_message);

    }
    //-----------
    //char data_user[3000] = "";
    char *data_user = "Username : ";
    strcat(data_user, client_message);
    write(sock , data_user , strlen(client_message));
    
    //clear the message buffer
    memset(client_message, 0, 2000);
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        char *tmp1, *tmp2, *tmp3;
        tmp1 = strtok(client_message, ":");
        
        if(strcmp(client_message,"REFRESH") == 0)
        {
            char *list_user;
            // Disini string untuk list--->>>>>>>>>>>>>>>>
            char *tmp = ListAll();
            strcpy(list_user,tmp);
            //input variabel list_user;

            write(sock, list_user, strlen(list_user));
            memset(list_user,0,3000);
        }
        // Untuk char harus TalkTo , talkto, TALKTO.
        else if(strcmp(tmp1, "TALKTO") == 0)
        {
            // tmp1 = TALKTO
            // tmp2 = Username
            // tmp3 = Pesan
            //-----------------------//
            struct node *asal , *tujuan;
            char *data_kembalian = "FROM:";
            tmp2 = strtok(NULL, ":");
            tmp3 = strtok(NULL,"\r\n");
            //Cek nilai tmp1 - 3.
            printf("%s , %s , %s\n",tmp1,tmp2,tmp3);
            //------------------------//
            asal = cek_id(sock);
            tujuan = cek_nama(tmp2);

            strcat(data_kembalian,asal->username);
            strcat(data_kembalian,":");
            strcat(data_kembalian,tmp3);
            write(sock , data_kembalian , strlen(data_kembalian));
        }
        else if(strcmp(client_message,"BYE") == 0)
        {
            char *bye = "Client terputus";
            printf("%s : %s\n",bye,data_user);
            puts("Client disconnected");
            write(sock , bye , strlen(bye));
            fflush(stdout);
            break;
        }

    }
    if(read_size <= 0)
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
    host.sin_port  = htons(6666);

    int yes = 1;
  //  status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd, (struct sockaddr *)&host, sizeof(host));
    if (status == -1)  printf("bind error\n");
    
   
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





