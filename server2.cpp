#include <bits/stdc++.h> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <string.h> // contains string functions
#include <errno.h> //It defines macros for reporting and retrieving error conditions through error codes
#include <time.h> //contains various functions for manipulating date and time
#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <signal.h>
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses
#include <thread>
#include <pthread.h> 
#include <fstream>
#include "y.tab.h"
#include <pthread.h>
using namespace std;
extern int a[3];
extern FILE* yyin;
extern string name;
static int i=0;
int ret[10]={0};
pthread_mutex_t l; 
void print(int new_soc)
{
	//string response;
	switch(a[0])
	{
		case 1 : {
		
			 send(new_soc, "Successfully opened the account\n", sizeof("Successfully opened the account\n"), 0);
			 break;
			 
			 }
		case 2 : {
			 //cout<<"Successfully closed the account\n"<<endl;
			 send(new_soc, "Successfully closed the account\n", sizeof("Successfully closed the account\n"), 0);
			 break;
			 }
		case 3 : {
			 //cout<<"Your account balance is: \n"<<a[1]<<endl;
			 send(new_soc, "Your account balance is: \n", sizeof("Your account balance is: \n"), 0);
			 break;
			 }
		case 4 : {
			 //cout<<"Amount deposited successfully \n"<<a[0]<<a[1]<<a[2]<<endl;
			 send(new_soc, "Amount deposited successfully \n", sizeof("Amount deposited successfully \n"), 0);
			 break;	 
			 }
		case 5 : {
			 //cout<<"Amount withdrawn successfully from your account\n"<<a[0]<<a[1]<<a[2]<<endl;
			 send(new_soc, "Amount withdrawn successfully from your account\n", sizeof("Amount withdrawn successfully from your account\n"), 0);
			 break;	
			 }
		case 6 : {
			 //cout<<"Your mini statement is\n"<<a[0]<<a[1]<<endl;
			 send(new_soc, "Your mini statement is\n", sizeof("Your mini statement is\n"), 0);
			 break;
			 }				  			 
		case 10: {
			 //cout<<"invalid synatx\n"<<endl;
			 send(new_soc, "invalid synatx!! Command not found\n", sizeof("invalid synatx!! Command not found\n"), 0);
			
			 break;
			} 
			 
		default : break;
			
			 
	}

	

}

void signal_callback_handler(int signum) {
   cout << "Caught signal " << signum << endl;
   //Terminate program
   exit(signum);
}


void threadf(int new_soc,int j)
{

char buffer[30];
char msg[] = "Hey!! you are connected to the server\n";
send(new_soc, msg, sizeof(msg), 0);
//cout<<"This is from the thread "<<this_thread::get_id()<<endl;
while(1)
{
	if(recv(new_soc, buffer, 50, 0)>0)signal(SIGINT, signal_callback_handler);
	if(strcmp(buffer,"exit")==0)break;
	pthread_mutex_lock(&l);
	char c[]="\n";
	strcat(buffer,c);
	yyin=fopen("temp.txt","w");
	if(yyin==NULL)cout<<"failed to open"<<endl;	
	fputs(buffer,yyin);	
	fclose(yyin);
	yyin=fopen("temp.txt","r");
	if(yyparse())print(new_soc);
	fclose(yyin);
	pthread_mutex_unlock(&l);
}
ret[j]=-1;
}

int main()
{

signal(SIGINT, signal_callback_handler);
int welcome, new_soc, n;

struct sockaddr_in addr;
welcome = socket(PF_INET, SOCK_STREAM, 0);
addr.sin_family = AF_INET;
addr.sin_port = htons(7891);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
bind(welcome, (struct sockaddr *) &addr, sizeof(addr));
printf("\nServer is Online");
listen(welcome, 5);
thread t[10];


while(1)
{

new_soc = accept(welcome, NULL, NULL);
t[i]=thread(threadf,new_soc,i);
i++;
if(i==10)break;

}

for(int j=0;i<10;j++)
{

cout<<"the thread is jointed "<< i<<endl;
t[j].join();
}
return 0;

}


/* 
for(int k=0;k<10;k++)
{
if(ret[k]==-1){ret[k]=-2;t[k].join();}
}


*/

/*while(j<10)
{
if(ret[j]==-1)t[j].join();
}*/

//while(!v.empty())v.pop_back().join();
/*fd = open(fname, O_RDONLY);
if (fd < 0)
send(new_soc, "\nFile not found\n", 15, 0);
else
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
send(new_soc, buffer, n, 0);
printf("\nRequest sent\n");
close(fd);*/









