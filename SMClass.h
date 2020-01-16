/*
 * Author: Yufan Xu
 * Assignment: CSI4330 Final Project
 * File: SMClass.h
 */

#ifndef SMPROJ_SMCLASS_H
#define SMPROJ_SMCLASS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


class StateMachine {
public:
    // standard functions
    StateMachine();

    StateMachine(const StateMachine &);

    ~StateMachine();

    StateMachine &operator=(const StateMachine &);

    // creation of the object
    bool AddInput(char);

    bool AddState(char *);

    bool AddTransition(char *, char, char *);

    void SetStart(char *);

    void SetName(char *);

    void SetFinal(char *);

    void FinalizeInputs();

    void FinalizeStates();

    void Finalize();

    bool isSane() const;

    bool isValidInput(char) const;

    int TranslateState(char *) const;

    // code generation
    int StateCount() const;

    int InputCount() const;

    char *GetStateName(int) const;

    char GetInputChar(int) const;

    char GetTransitionChar(int, int) const;

    int GetTransitionState(int, int) const;

    int GetStart() const;

    const char *GetName() const;

    bool isFinal(int) const;

    StateMachine *GetNext() const;

    void SetNext(StateMachine *);

    void printInput();

    void printStates();

    void printFinalStates();

    void printTransitionStates();

    bool isDuplicateInput(char) const;

    bool isDuplicateState(char *) const;

    void AddSM(StateMachine *);

    int getSMListSize();

    void printStart();

    StateMachine * getSM(int );

    int getSMID();

    bool isStateAnInput(char* );

    bool isInputAState(char );

    void GenerateCode(ofstream& );

    int getInputIndex(char );

protected:
    struct STrans {
    public:
        STrans *next;
        char *nextStateName;
        char *stateName;
        char inputSymbol;
        int stateNumber;

        STrans() {
            this->next = NULL;
        }

        STrans(char input) {
            this->inputSymbol = input;
            this->next = NULL;
        }
    };


    struct SContainer {
        char *stateName;
        int stateNumber;
    };

    StateMachine *Next;

    STrans *transitionList;
    SContainer *sContainer;

    char *inputArray;
    int INPUTSIZE;
    int INPUTCAPACITY;
    int STATESIZE;
    int STATECAPACITY;
    int smlistSize;
    int smID;

    STrans startState;
    STrans *finalState;

    char *machineName;
};


#endif //SMPROJ_SMCLASS_H
