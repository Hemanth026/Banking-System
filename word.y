

%{

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern int yylex();
void yyerror(char *msg);
int a[2];
%}


%union{
//char* str;
int i;
}

//%type <str> E T 
%type <i> R NUM
%token 	 NUM


%%

S :  R  	 {a[0]=1;a[1]=$1;printf("syntax is acccepted\n");return 0;}
  ;
R : NUM		 {$$=$1;printf("this is from yac  %d",$1);}		 
  ;
%%


void yyerror(char *msg)
{

fprintf(stderr,"%s\n",msg);
exit(1);

}

int main()
{

yyparse();
printf("from the main %d %d ",a[0],a[1]);
return 0;

}




