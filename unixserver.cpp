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

using namespace std;
static int i=0;
int ret[10]={0};

void threadf(int new_soc,int j)
{

char buffer[1024];
(recv(new_soc, buffer, 50, 0));
printf("\nRequesting for file: %s\n", buffer);
ret[j]=-1;
}

int main()
{
int welcome, new_soc, n;
//vector<thread> v;

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
for(int k=0;k<10;k++)
{
if(ret[k]==-1){ret[k]=-2;t[k].join();}
}
/*while(j<10)
{
if(ret[j]==-1)t[j].join();
}*/
}

//while(!v.empty())v.pop_back().join();
/*fd = open(fname, O_RDONLY);
if (fd < 0)
send(new_soc, "\nFile not found\n", 15, 0);
else
while ((n = read(fd, buffer, sizeof(buffer))) > 0)
send(new_soc, buffer, n, 0);
printf("\nRequest sent\n");
close(fd);*/



return 0;

}





