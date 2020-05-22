

%{

#include<iostream>
#include<cstdio>
#include<stdlib.h>
#include<string.h>
using namespace std;
extern int yylex();
void yyerror(char *msg);
int a[3];
string name;

%}


%union{
char* str;
int * details;
int i;
}

%type <str> OPEN STR
%type <details> DEP WITH
%type <i> CLOSE ACC BALAN BAL ERR MINI  
%token STR DEP WITH MINI ACC BAL ERR

%%



START :  OPEN  	 { a[0]=1;name=string($1);cout<<"account opened successfully by "<<name<<endl;return 0;}
      |  CLOSE   { a[0]=2;a[1]=$1;cout<<"acc closed ";return 0;}	
      |  BALAN   { a[0]=3;a[1]=$1;cout<<"account balance is "<<endl;return 0;}	
      |  DEP	 { a[0]=4;a[1]=*($1+0);a[2]=*($1+1);return 0;}
      |  WITH	 { a[0]=5;a[1]=*($1+0);a[2]=*($1+1);return 0;}  
      |  MINI    { a[0]=6;a[1]=$1;return 0;}    
      |  ERR     { a[0]=10;return 0;}      
      ;
OPEN  : STR  	 { $$=$1;printf("from the yacc %s\n",$1);}
      ;
CLOSE : ACC   	 { $$=$1;}
      ; 
BALAN : BAL 	 { $$=$1;}
      ;
      
%%


void yyerror(char *msg)
{

fprintf(stderr,"%s\n",msg);
exit(1);

}

int main()
{
while(1)
{
	yyparse();
	switch(a[0])
	{
		case 1 : cout<<"from the main "<<name<<endl;
			 break;
		case 2 : cout<<"from the main "<<endl;
			 break;
		case 3 : cout<<"from the main"<<a[1]<<endl;
			 break;
		case 4 : cout<<"from the main deposit "<<a[0]<<a[1]<<a[2]<<endl;
			 break;	 
		case 5 : cout<<"from the main WITHDRAW "<<a[0]<<a[1]<<a[2]<<endl;
			 break;	
		case 6 : cout<<"from the main mini statement "<<a[0]<<a[1]<<endl;
			 break;				  			 
		case 10: cout<<"invalid synatx "<<endl;
			 break;
			 
			 
		default : break;
			 
	}	 
}	 
return 0;

}




