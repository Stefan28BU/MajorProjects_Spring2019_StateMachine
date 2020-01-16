#ifndef SMPROJ_GLOBALS_H
#define SMPROJ_GLOBALS_H

#include "SMClass.h"
extern char IdText[];
int yylex();
int yyparse();
void yyerror(const char*);
extern StateMachine *current;
extern StateMachine *smList;
extern char idListInput[];
extern char* idListState[];
extern int idCountInput;
extern int idCountState;
extern char* fromState;
extern char* gotoState;
extern char inputSymbol;
extern char inputTrans[];
extern char *stateTrans[];
extern int inputTransCount;
extern int stateTransCount;
extern int addTransCount;
extern char* finalStates[];
extern int finalStatesCount;

#endif //SMPROJ_GLOBALS_H
