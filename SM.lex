%{
/* author: Yufan Xu */

#include "globals.h"
#include "y.tab.h"
#include <string.h>
%}
%%
DFA { return DFA; }
Name { return NAME; }
Inputs { return INPUTS; }
States { return STATES; }
Start { return START; }
Final { return FINAL; }
"End." { return END; }
"," { return COMMA; }
";" { return SEMI; }
":" { return COLON; }
"(" { return LEFTPARENT; }
")" { return RIGHTPARENT; }

[ \t\r\n]*
[0-9a-zA-Z]+ { strcpy(IdText, yytext); return ID; }
. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
