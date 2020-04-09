#include <bits/stdc++.h> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include<thread>
#include <pthread.h> 
//#include<mutex>
using namespace std;

pthread_mutex_t l; 
int welcomeSocket;

void f(int i)
{

 char buffer[1024],a[100];
 string msg;
 int  newSocket;
 struct sockaddr_storage serverStorage;
 socklen_t addr_size;
  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  /*---- Send message to the socket of the incoming connection ----*/
 
 strcpy(buffer,"Hello World ");
 cout<<"this is from thread id "<<this_thread::get_id()<<endl;
 
 cout<<"recieved messages are"<<endl;
 while(1)
 {
   if(recv(newSocket,a,100,0)==0)
   {
   cout<<"client disconnected"<<endl;
   close(newSocket);
   }	
   if(strcmp(a,"exit")==0)break;
   pthread_mutex_lock(&l);
   send(newSocket,buffer,13,0);
   pthread_mutex_unlock(&l);
  }
  close(newSocket);
  }



int main(){

  struct sockaddr_in serverAddr;

 

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
	cout<<"listening"<<endl;
  else
	cout<<"error"<<endl;




 thread t[5];
 for(int i=0;i<5;i++)
 {
 t[i]=thread(f,i);
 cout<<"this is from thread id "<<t[i].get_id()<<endl;
 }	

 for(int i=0;i<5;i++)
 t[i].join();
 

  return 0;
}

 






