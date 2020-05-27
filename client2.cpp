#include<bits/stdc++.h>
#include "stdio.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

using namespace std;

int main()
{
int soc, n;
char buffer[1024], fname[50];
struct sockaddr_in addr;
soc = socket(PF_INET, SOCK_STREAM, 0);
addr.sin_family = AF_INET;
addr.sin_port = htons(7891);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");
while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ;
//printf("\nClient is connected to Server");
recv(soc, buffer, sizeof(buffer), 0);
printf("%s\n", buffer);


while(1)
{
cout<<"/****************************************************************/"<<endl;
printf("\nEnter your operation : ");
scanf("%[^\n]%*c", fname); 
char s[]="exit";
if(strcmp(fname,s)==0)break;
send(soc, fname, sizeof(fname), 0);
printf("\nRecieved response : ");
recv(soc, buffer, sizeof(buffer), 0);
printf("%s", buffer);
}


return 0;
}
