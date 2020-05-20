%{

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "y.tab.h"

int cnt=1;
%}



%%


open|OPEN {cnt=1;printf("open is matchd \n");}
account|ACCOUNT {if(cnt==1){cnt++;printf("acc is matched\n");}}
[0-9]+ {if(cnt==2){yylval.i=atoi(yytext);cnt=1;printf("The value of num is %d\n",(yylval.i));return NUM;}}
[ \t] {;}
.|\n {yywrap();}



%%

int yywrap()
{

return -1;

}
