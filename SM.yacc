%{
/* author: Yufan Xu */

#include <iostream>
#include "globals.h"
#include <string.h>
#include <ctype.h>

using namespace std;

%}

%token DFA NAME INPUTS STATES START FINAL END COMMA SEMI COLON LEFTPARENT RIGHTPARENT ID

%start smlist
%%
smlist: smlist sm {
                       cout << "Found a smlist" << endl;
                       smList->AddSM(current);
                       current = new StateMachine;
                  }
      | sm {
                cout << "Found a single SM" << endl;
                smList->AddSM(current);
                current = new StateMachine;
           }
      ;
sm: dfaspec body endspec { cout << "Found dfaspec/body/endspec\n"; }
  ;
dfaspec: DFA SEMI { cout << "Found dfaspec" << endl; }
       ;
endspec: END {
                 cout << "Found endspec" << endl;
                 idCountState = 0;
                 idCountInput = 0;
                 addTransCount = 0;


                 cout << current->isSane() << endl;
             }
       ;
body: speclist { cout << "Found body" << endl; }
    ;
speclist: speclist spec { cout << "Found speclist/spec" << endl; }
        | spec { cout << "Found a single spec" << endl; }
        ;
spec: inputspec { cout << "Found an inputspec" << endl; }
    | statespec { cout << "Found an statespec" << endl; }
    | namespec { cout << "Found an namespec" << endl; }
    | startspec { cout << "Found an startspec" << endl; }
    | finalspec { cout << "Found an finalspec" << endl; }
    | transspec { cout << "Found an transspec" << endl; }
    ;
namespec: NAME COLON ID SEMI {
                                  cout << "Found namespec: NAME : ID ;" << endl;
                                  current->SetName(IdText);
                             }
        ;
idlist: idlist COMMA ID {
                             cout << "Found idlist: comma followed by ID" << endl;

                             if (strlen(IdText) == 1) {
                                 idListInput[idCountInput] = IdText[0];
                                 idCountInput ++;
                             }
                             if (!isdigit(IdText[0])) {
                                 idListState[idCountState] = strdup(IdText);
                                 idCountState ++;
                                 finalStates[finalStatesCount] = strdup(IdText);
                                 finalStatesCount++;
                             }
                        }
      | ID {
                cout << "Found a single ID" << endl;

                if (strlen(IdText) == 1) {
                    idListInput[idCountInput] = IdText[0];
                    idCountInput ++;
                }
                if (!isdigit(IdText[0])) {
                    idListState[idCountState] = strdup(IdText);
                    idCountState ++;
                    finalStates[finalStatesCount] = strdup(IdText);
                    finalStatesCount++;
                }
           }
      ;
id: ID {
           cout << "Found ID" << endl;
           if (strlen(IdText) == 1 && !current->isInputAState(IdText[0])) {
               inputSymbol = IdText[0];
           }
           if (!isdigit(IdText[0])) {
               gotoState = strdup(IdText);
               fromState = strdup(IdText);
           }
       }
  ;
inputspec: INPUTS COLON idlist SEMI {
                                         cout << "Found inputspec: INPUTS : idlist ;\n";
                                         for (int i = 0; i < idCountInput; i ++) {
                                             current->AddInput(idListInput[i]);
                                             idListInput[i] = '\0';
                                         }
                                    }
         ;
statespec: STATES COLON idlist SEMI {
                                        cout << "Found statespec: STATES : idlist ;" << endl;

                                        for(int i=0; i < idCountState; i ++) {
                                            if (!current->isStateAnInput(idListState[i])) {
                                                current->AddState(idListState[i]);
                                                idListState[i] = NULL;
                                            }
                                        }
                                        finalStatesCount = 0;
                                    }
         ;
startspec: START COLON id SEMI {
                                    cout << "Found startspec: START : id ;\n";
                                    current->SetStart(IdText);
                               }
         ;
finalspec: FINAL COLON idlist SEMI {
                                       cout << "Found finalspec: FINAL : idlist ;\n";

                                       for(int i =0; i < finalStatesCount; i ++ ) {
                                           current->SetFinal(finalStates[i]);
                                           finalStates[i] = NULL;
                                       }
                                       finalStatesCount = 0;
                                   }
         ;

transspec: id COLON translist SEMI {
                                       cout << "Found transspec: id : translist ;\n";

                                       for (int i = 0; i < stateTransCount; i ++ ) {
                                           cout << "1" << endl;
                                           char *stateN = strdup(current->GetStateName(addTransCount));
                                           cout << "2" << endl;

                                           current->AddTransition(stateN, inputTrans[i], stateTrans[i]);
                                                                                      cout << "3" << endl;

                                       }
                                       addTransCount++;
                                       inputTransCount = 0;
                                       stateTransCount = 0;
                                   }
         ;
translist: translist COMMA trans {
                                     cout << "Found translist: comma(,) followed by trans\n";
                                 }
         | trans { cout << "Found a trans" << endl; }
         ;
trans: LEFTPARENT id COMMA id RIGHTPARENT {
                                              inputTrans[inputTransCount] = inputSymbol;
                                              inputTransCount++;

                                              stateTrans[stateTransCount] = strdup(gotoState);
                                              stateTransCount++;
                                          }
     ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n",s);
}
int yywrap() {
    return(1);
}

