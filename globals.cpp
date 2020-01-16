#include "globals.h"

#include <iostream>
char IdText[5000];
StateMachine *current = NULL;
StateMachine *smList = NULL;
char idListInput[5000];
char *idListState[5000];
int idCountInput = 0;
int idCountState = 0;
char* fromState;
char* gotoState;
char inputSymbol;
char inputTrans[5000];
char *stateTrans[5000];
int inputTransCount = 0;
int stateTransCount = 0;
int addTransCount = 0;
char* finalStates[5000];
int finalStatesCount = 0;

