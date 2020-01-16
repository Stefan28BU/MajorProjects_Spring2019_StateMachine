/*
 * Author: Yufan Xu
 * File: Main.cpp
 * Assignment: CSI4330 Final Project
 */

#include <iostream>
#include "globals.h"

int main() {

    smList = new StateMachine;
    current = new StateMachine;

    if (yyparse() != 0) {
        cout << "Syntax Error Occured; Code Generation Aborted." << endl;
        exit(1);
    }

    const char* M = smList->getSM(0)->GetName();
    const char* extension = strdup(".cpp");
    char* fileName = (char*) malloc(1 + strlen(M) + strlen(extension));

    strcpy(fileName, M);
    strcat(fileName, extension);

    ofstream outFile;

    outFile.open(fileName);

    outFile << "/* " << endl;
    outFile<<  " * Author: Yufan Xu" << endl;
    outFile << " * Filename: " << fileName << endl;
    outFile << " */\n" << endl;

    for (int i = 0; i < smList->getSMListSize(); i ++) {

        cout << "Machine Name: " << smList->getSM(i)->GetName() << endl << endl;
        smList->getSM(i)->printInput();
        smList->getSM(i)->printStates();
        smList->getSM(i)->printStart();
        smList->getSM(i)->printFinalStates();
        cout << endl;

        smList->getSM(i)->printTransitionStates();

        cout << endl;

        smList->getSM(i)->GenerateCode(outFile);
        cout << endl;
        outFile << endl;
    }

    outFile.close();

    return 0;
}