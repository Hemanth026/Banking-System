%{
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#include "y.tab.h"

using namespace std;
int ocnt=1/*open count*/,ccnt=1/*close coount*/,flag,bal=1/*balance*/,eflag=1,dep=1,with=1;
 char t[]="exit";
 char t1[]="EXIT";
const char* s=t;
const char* s1=t1;
int det[2];
%}


%%	


open|OPEN 	{if(ocnt==1){flag=1;ocnt++;}}
close|CLOSE	{if(ccnt==1){flag=2;ccnt++;}}
account|ACCOUNT {if(ccnt==2&&flag==2)ccnt++;else if (flag==1&&ocnt==2)ocnt++;}
show|SHOW	{if(bal==1)bal++;}
balance|BALANCE {if(bal==2)bal++;}
deposit|DEPOSIT {if(dep==1)dep++;}
withdraw|WITHDRAW {if(with==1)with++;}
MINISTATEMENT   {yylval.i=6;return MINI;}
[a-zA-Z]+ 	{

		if(*s==*yytext||*s1==*yytext)exit(1);
		else if(ocnt==3){ocnt=1;yylval.str=yytext;return STR;}
		else if(eflag){eflag=0; yylval.i=4;return ERR; }
		else {yylval.i=4;yywrap(); }
		
		}
[0-9]+ 		{
		if(ccnt==3){yylval.i=atoi(yytext);ccnt=1;return ACC;}
		else if(bal==3){yylval.i=atoi(yytext);bal=1;return BAL;}
		else if(ocnt==3){yylval.i=4;return ERR;}
		else if(dep==2){det[0]=atoi(yytext);dep++;}
		else if(dep==3){det[1]=atoi(yytext);dep=1;yylval.details=det;return DEP;}
		else if(with==2){det[0]=atoi(yytext);with++;}
		else if(with==3){det[1]=atoi(yytext);dep=1;yylval.details=det;return WITH;}
		}
[ \t]	 	{;}
. 		{
		if(eflag){ocnt=ccnt=bal=1;yylval.i=4;return ERR;}
		else ;
		}
\n		{ocnt=ccnt=bal=eflag=with=1;yywrap();}


%%

int yywrap()
{

return -1;

}














