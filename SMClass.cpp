/*
 * Author: Yufan Xu
 * Assignment: CSI4330 Final Project
 * File: SMClass.cpp
 */

#include "SMClass.h"
#include "globals.h"

StateMachine::StateMachine() {

    Next = NULL;

    this->transitionList = NULL;
    this->finalState = NULL;
    this->INPUTSIZE = 0;
    this->INPUTCAPACITY = 5;
    this->STATESIZE = 0;
    this->STATECAPACITY = 5;
    this->smlistSize = 0;

    this->inputArray = new char[INPUTCAPACITY];
    this->sContainer = new SContainer[STATECAPACITY];
}

StateMachine::StateMachine(const StateMachine &sm) {
    if (sm.transitionList != NULL) {
        this->transitionList = new STrans;

        this->transitionList->inputSymbol = sm.transitionList->inputSymbol;
        this->transitionList->stateName = strdup(sm.transitionList->stateName);
        this->transitionList->stateNumber = sm.transitionList->stateNumber;
        this->transitionList->nextStateName = strdup(sm.transitionList->nextStateName);

        // copy start and final states
        this->startState.inputSymbol = sm.startState.inputSymbol;
        this->startState.stateName = strdup(sm.startState.stateName);
        this->startState.stateNumber = sm.startState.stateNumber;

        this->machineName = strdup(sm.machineName);

        this->INPUTSIZE = sm.INPUTSIZE;
        this->INPUTCAPACITY = sm.INPUTCAPACITY;
        this->STATESIZE = sm.STATESIZE;
        this->STATECAPACITY = sm.STATECAPACITY;
        this->smlistSize = sm.smlistSize;
        this->smID = sm.smID;

        this->inputArray = new char[this->INPUTCAPACITY];
        this->sContainer = new SContainer[this->STATECAPACITY];

        for (int i = 0; i < this->INPUTSIZE; i++) {
            this->inputArray[i] = sm.inputArray[i];
        }

        for (int i = 0; i < this->STATESIZE; i++) {
            this->sContainer[i].stateNumber = sm.sContainer[i].stateNumber;
            this->sContainer[i].stateName = strdup(sm.sContainer[i].stateName);
        }

        STrans *temp = this->transitionList;
        STrans *tempOther = sm.transitionList->next;

        while (tempOther != NULL) {
            temp->next = new STrans;
            temp->next->inputSymbol = tempOther->inputSymbol;
            temp->next->stateName = strdup(tempOther->stateName);
            temp->next->stateNumber = tempOther->stateNumber;
            temp->next->nextStateName = strdup(tempOther->nextStateName);

            temp->next->next = NULL;
            temp = temp->next;
            tempOther = tempOther->next;
        }
    }

    if (sm.finalState != NULL) {
        this->finalState = new STrans;

        this->finalState->inputSymbol = sm.finalState->inputSymbol;
        this->finalState->stateName = strdup(sm.finalState->stateName);
        this->finalState->stateNumber = sm.finalState->stateNumber;

        STrans *temp = this->finalState;
        STrans *tempOther = sm.finalState->next;

        while (tempOther != NULL) {
            temp->next = new STrans;
            temp->next->inputSymbol = tempOther->inputSymbol;
            temp->next->stateName = strdup(tempOther->stateName);
            temp->next->stateNumber = tempOther->stateNumber;
            temp->next->nextStateName = strdup(tempOther->nextStateName);

            temp->next->next = NULL;
            temp = temp->next;
            tempOther = tempOther->next;
        }
    }
}

StateMachine &StateMachine::operator=(const StateMachine &sm) {

    if (this != &sm) {
        while (this->transitionList != NULL) {
            STrans *temp;
            temp = this->transitionList;
            this->transitionList = this->transitionList->next;
            temp->next = NULL;
            delete temp;
        }
        if (sm.transitionList != NULL) {
            this->transitionList = new STrans;
            this->finalState = new STrans;

            this->transitionList->inputSymbol = sm.transitionList->inputSymbol;
            this->transitionList->stateName = strdup(sm.transitionList->stateName);
            this->transitionList->stateNumber = sm.transitionList->stateNumber;
            this->transitionList->nextStateName = strdup(sm.transitionList->nextStateName);

            // copy start and final states
            this->startState.inputSymbol = sm.startState.inputSymbol;
            this->startState.stateName = strdup(sm.startState.stateName);
            this->startState.stateNumber = sm.startState.stateNumber;

            this->machineName = strdup(sm.machineName);

            delete[] this->inputArray;

            delete[] this->sContainer;

            this->INPUTSIZE = sm.INPUTSIZE;
            this->INPUTCAPACITY = sm.INPUTCAPACITY;
            this->STATESIZE = sm.STATESIZE;
            this->STATECAPACITY = sm.STATECAPACITY;
            this->smlistSize = sm.smlistSize;
            this->smID = sm.smID;

            this->inputArray = new char[this->INPUTCAPACITY];
            this->sContainer = new SContainer[this->STATECAPACITY];

            for (int i = 0; i < this->INPUTSIZE; i++) {
                this->inputArray[i] = sm.inputArray[i];
            }

            for (int i = 0; i < this->STATESIZE; i++) {
                this->sContainer[i].stateNumber = sm.sContainer[i].stateNumber;
                this->sContainer[i].stateName = strdup(sm.sContainer[i].stateName);
            }

            STrans *temp = this->transitionList;
            STrans *tempOther = sm.transitionList->next;

            while (tempOther != NULL) {
                temp->next = new STrans;
                temp->next->inputSymbol = tempOther->inputSymbol;
                temp->next->stateName = strdup(tempOther->stateName);
                temp->next->stateNumber = tempOther->stateNumber;
                temp->next->nextStateName = strdup(tempOther->nextStateName);

                temp->next->next = NULL;
                temp = temp->next;
                tempOther = tempOther->next;
            }
        }

        if (sm.finalState != NULL) {
            this->finalState = new STrans;

            this->finalState->inputSymbol = sm.finalState->inputSymbol;
            this->finalState->stateName = strdup(sm.finalState->stateName);
            this->finalState->stateNumber = sm.finalState->stateNumber;

            STrans *temp = this->finalState;
            STrans *tempOther = sm.finalState->next;

            while (tempOther != NULL) {
                temp->next = new STrans;
                temp->next->inputSymbol = tempOther->inputSymbol;
                temp->next->stateName = strdup(tempOther->stateName);
                temp->next->stateNumber = tempOther->stateNumber;
                temp->next->nextStateName = strdup(tempOther->nextStateName);

                temp->next->next = NULL;
                temp = temp->next;
                tempOther = tempOther->next;
            }
        }
    }

    return *this;
}

StateMachine::~StateMachine() {
    STrans *temp;
    STrans *temp2;

    while (this->transitionList != NULL) {
        temp = this->transitionList;
        this->transitionList = this->transitionList->next;
        temp->next = NULL;
        delete temp;
    }

    while (this->finalState != NULL) {
        temp2 = this->finalState;
        this->finalState = this->finalState->next;
        temp2->next = NULL;
        delete temp2;
    }

    delete[] this->inputArray;
    this->inputArray = NULL;

    delete[] this->sContainer;
    this->sContainer = NULL;
}

bool StateMachine::AddInput(char input) {

    if (isDuplicateInput(input)) {
        return true;
    }

    if (this->INPUTSIZE == this->INPUTCAPACITY) {
        char *old = this->inputArray;
        this->INPUTCAPACITY += 5;
        this->inputArray = new char[this->INPUTCAPACITY];
        for (int i = 0; i < this->INPUTSIZE; i++) {
            this->inputArray[i] = old[i];
        }
    }
    this->inputArray[this->INPUTSIZE] = input;
    this->INPUTSIZE++;

    return false;
}

bool StateMachine::AddState(char *stateName) {

    if (isDuplicateState(stateName)) {
        return true;
    }

    if (this->STATESIZE == this->STATECAPACITY) {
        SContainer *old = this->sContainer;
        this->STATECAPACITY += 5;
        this->sContainer = new SContainer[this->STATECAPACITY];
        for (int i = 0; i < this->STATESIZE; i++) {
            this->sContainer[i].stateName = strdup(old[i].stateName);
            this->sContainer[i].stateNumber = old[i].stateNumber;
        }
    }
    this->sContainer[this->STATESIZE].stateName = strdup(stateName);
    this->sContainer[this->STATESIZE].stateNumber = this->STATESIZE;

    this->STATESIZE++;

    return false;
}

bool StateMachine::AddTransition(char *transState, char input, char *gotoState) {

    if (!isValidInput(input)) {
        return true;
    }

    if (this->transitionList == NULL) {
        this->transitionList = new STrans;
        this->transitionList->stateName = strdup(transState);
        this->transitionList->inputSymbol = input;
        this->transitionList->nextStateName = strdup(gotoState);

    } else {
        STrans *temp = this->transitionList;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new STrans;
        temp->next->stateName = strdup(transState);
        temp->next->inputSymbol = input;
        temp->next->nextStateName = strdup(gotoState);

        temp->next->next = NULL;
    }
    this->transitionList->stateNumber = this->TranslateState(transState);

    return false;
}

void StateMachine::SetStart(char *startStateName) {
    this->startState.stateName = strdup(startStateName);

    this->printStates();
    for (int i = 0; i < this->STATESIZE; i++) {
        if (strcmp(this->startState.stateName, this->sContainer[i].stateName) == 0) {
            this->startState.stateNumber = this->sContainer[i].stateNumber;
        }
    }
}

void StateMachine::SetName(char *machineName) {
    this->machineName = strdup(machineName);
}

void StateMachine::SetFinal(char *finalStateName) {
    if (isDuplicateState(finalStateName)) {
        if (this->finalState == NULL) {
            this->finalState = new STrans;
            this->finalState->stateName = strdup(finalStateName);

            for (int i = 0; i < this->STATESIZE; i++) {
                if (strcmp(finalStateName, this->sContainer[i].stateName) == 0) {
                    this->finalState->stateNumber = this->sContainer[i].stateNumber;
                }
            }

        } else {
            STrans *temp = this->finalState;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new STrans;
            temp->next->stateName = strdup(finalStateName);

            for (int i = 0; i < this->STATESIZE; i++) {
                if (strcmp(finalStateName, this->sContainer[i].stateName) == 0) {
                    temp->next->stateNumber = this->sContainer[i].stateNumber;
                }
            }

            temp->next->next = NULL;
        }
    }
}

void StateMachine::FinalizeInputs() {

}

void StateMachine::FinalizeStates() {

}

void StateMachine::Finalize() {

}

bool StateMachine::isSane() const {
    STrans *temp = this->transitionList;
    bool flag = false;

    int sTransCount = 0;
    while (temp->next != NULL) {
        for (int i = 0; i < this->STATESIZE; i++) {
            if (strcmp(temp->stateName, this->sContainer->stateName) == 0) {
                sTransCount++;
            }
        }
        temp = temp->next;
    }

    if (sTransCount == STATESIZE) {
        flag = true;
    } else {
        flag = false;
    }

    if (this->startState.stateName != NULL) {
        flag = true;
    } else {
        flag = false;
    }

    if (this->finalState->stateName != NULL) {
        flag = true;
    } else {
        flag = false;
    }

    return flag;
}

bool StateMachine::isValidInput(char input) const {
    for (int i = 0; i < INPUTSIZE; i++) {
        if (input == inputArray[i]) {
            return true;
        }
    }

    return false;
}

int StateMachine::TranslateState(char *stateName) const {

    for (int i = 0; i < this->STATESIZE; i++) {
        if (strcmp(stateName, this->sContainer[i].stateName) == 0) {
            return this->sContainer[i].stateNumber;
        }
    }

    return -1;
}

int StateMachine::StateCount() const {
    return this->STATESIZE;
}

int StateMachine::InputCount() const {
    return this->INPUTSIZE;
}

char *StateMachine::GetStateName(int stateNumber) const {
    for (int i = 0; i < this->STATESIZE; i++) {
        if (stateNumber == this->sContainer[i].stateNumber) {
            return this->sContainer[i].stateName;
        }
    }

    return NULL;
}

char StateMachine::GetInputChar(int index) const {
    return this->inputArray[index];
}

char StateMachine::GetTransitionChar(int stateNum, int pos) const {

    for (int i = 0; i < this->STATESIZE; i++) {
        if (this->sContainer[i].stateNumber == stateNum) {
            STrans *temp = this->transitionList;

            while (temp != NULL) {
                if (strcmp(temp->stateName, sContainer[i].stateName) == 0
                    && strcmp(temp->nextStateName, sContainer[pos].stateName) == 0) {
                    return temp->inputSymbol;
                }
                temp = temp->next;
            }
        }
    }

    return '\0';
}

int StateMachine::GetTransitionState(int stateNum, int pos) const {
    STrans *temp = this->transitionList;

    for (int i = 0; i < STATESIZE; i ++) {
        if (stateNum == this->sContainer[i].stateNumber) {
            for (int j = 0; j < INPUTSIZE; j ++) {
                if (pos == j) {
                    while (temp != NULL) {
                        if (this->inputArray[j] == temp->inputSymbol && strcmp(this->sContainer[i].stateName, temp->stateName) == 0) {
                            for (int k = 0; k < this->STATESIZE; k ++) {
                                if (strcmp(temp->nextStateName, this->sContainer[k].stateName) == 0 ) {
                                    return sContainer[k].stateNumber;
                                }
                            }
                        }
                        temp = temp->next;
                    }
                }
            }
        }
    }

    return -1;
}

int StateMachine::GetStart() const {
    return this->startState.stateNumber;
}

const char *StateMachine::GetName() const {
    return this->machineName;
}

bool StateMachine::isFinal(int stateNumber) const {

    STrans *ftemp = this->finalState;

    while (ftemp != NULL) {
        if (stateNumber == ftemp->stateNumber) {
            return true;
        }
        ftemp = ftemp->next;
    }

    return false;
}

StateMachine *StateMachine::GetNext() const {
    return this->Next;
}

void StateMachine::SetNext(StateMachine *nextSM) {
    this->Next = nextSM;
}

void StateMachine::printInput() {
    cout << "Valid input symbols: ";
    for (int i = 0; i < INPUTSIZE; i++) {
        cout << inputArray[i] << " ";
    }
    cout << endl;
}

void StateMachine::printStates() {
    cout << "Valid state names: ";
    for (int i = 0; i < STATESIZE; i++) {
        cout << sContainer[i].stateName << "[" << sContainer[i].stateNumber << "] ";
    }
    cout << endl;
}

void StateMachine::printTransitionStates() {
    cout << "State Transitions:" << endl;

    STrans *temp = this->transitionList;

    while (temp != NULL) {
        cout << temp->stateName << "('" << temp->inputSymbol << "') -> " << temp->nextStateName << endl;
        temp = temp->next;
    }
}

bool StateMachine::isDuplicateInput(char input) const {
    for (int i = 0; i < INPUTSIZE; i++) {
        if (input == inputArray[i]) {
            return true;
        }
    }

    return false;
}

bool StateMachine::isDuplicateState(char *stateName) const {
    for (int i = 0; i < STATESIZE; i++) {
        if (strcmp(stateName, sContainer[i].stateName) == 0) {
            return true;
        }
    }

    return false;
}

void StateMachine::printFinalStates() {
    STrans *ftemp = this->finalState;

    cout << "Final state: ";
    while (ftemp != NULL) {
        cout << ftemp->stateName << "[" << ftemp->stateNumber << "] ";
        ftemp = ftemp->next;
    }
    cout << endl;
}

void StateMachine::AddSM(StateMachine *curr) {

    curr->smID = this->smlistSize;

    if (this->Next == NULL) {
        this->Next = new StateMachine;
        this->Next = curr;
        this->Next->Next = NULL;
    } else {
        StateMachine *temp = this->Next;

        while (temp->Next != NULL) {
            temp = temp->Next;
        }
        temp->Next = new StateMachine;

        temp->Next = curr;
        temp->Next->Next = NULL;
    }
    this->smlistSize++;
}

int StateMachine::getSMListSize() {
    return this->smlistSize;
}

StateMachine *StateMachine::getSM(int pos) {

    if (this->smlistSize == 0) {
        return NULL;
    }

    if (pos == 0 && this->Next != NULL) {
        return this->Next;
    }
    StateMachine *temp = this;

    int count = 0;
    while (temp->Next != NULL) {
        if (count == pos) {
            return temp->Next;
        }
        temp = temp->Next;
        count++;
    }

    return NULL;
}

int StateMachine::getSMID() {
    return this->smID;
}

void StateMachine::printStart() {
    cout << "Start state: ";
    cout << this->startState.stateName << "[" << this->startState.stateNumber << "]" << endl;
}

bool StateMachine::isStateAnInput(char *state) {
    for (int i = 0; i < this->INPUTSIZE; i++) {
        if (state[0] == this->inputArray[i] && strlen(state) == 1) {
            return true;
        }
    }
    return false;
}

bool StateMachine::isInputAState(char input) {
    for (int i = 0; i < this->STATESIZE; i++) {
        if (input == this->sContainer[i].stateName[0] && strlen(this->sContainer[i].stateName) == 1) {
            return true;
        }
    }
    return false;
}

void StateMachine::GenerateCode(ofstream& outFile) {
    char* startStateFlag = strdup("false;");

    cout << "bool " << this->GetName() << "(char input) {" << endl;
    outFile << "bool " << this->GetName() << "(char input) {" << endl;

    cout << "    static int state = " << this->GetStart() << ";" << endl;
    outFile << "    static int state = " << this->GetStart() << ";" << endl;

    cout << "    if (input == '\\0') {" << endl;
    outFile << "    if (input == '\\0') {" << endl;

    cout << "        state = " << this->GetStart() << ";" << endl;
    outFile << "        state = " << this->GetStart() << ";" << endl;

    if (this->isFinal(this->GetStart())) {
        startStateFlag = strdup("true;");
    }

    cout << "        return " << startStateFlag << endl;
    outFile << "        return " << startStateFlag << endl;

    cout << "    }" << endl;
    outFile << "    }" << endl;

    cout << "    switch(state) {" << endl;
    outFile << "    switch(state) {" << endl;

    for (int i = 0; i < this->STATESIZE; i ++) {

        cout << "        case " << i << ": {" << endl;
        outFile << "        case " << i << ": {" << endl;

        cout << "            switch(input) {" << endl;
        outFile << "            switch(input) {" << endl;

        for (int j = 0; j < this->INPUTSIZE; j++) {
            cout << "                case '" << this->GetInputChar(j) << "': {"  << endl;
            outFile << "                case '" << this->GetInputChar(j) << "': {"  << endl;

            char c = this->GetTransitionChar(i, j);
            char* flagStr = strdup("false");
            int currState = this->GetTransitionState(i, j);

            if (this->isFinal(currState)) {
                flagStr = strdup("true");
            }
            cout << "                    state = " << currState << ";" << endl;
            outFile << "                    state = " << currState << ";" << endl;

            cout << "                    return " << flagStr << ";" << endl;
            outFile << "                    return " << flagStr << ";" << endl;

            cout << "                }" << endl;
            outFile << "                }" << endl;
        }
        cout << "            }" << endl;
        outFile << "            }" << endl;

        cout << "        }" << endl;
        outFile << "        }" << endl;

    }
    cout << "    }" << endl;
    outFile << "    }" << endl;

    cout <<"}" << endl << endl;
    outFile <<"}" << endl;
}

int StateMachine::getInputIndex(char c ) {
    for (int i = 0; i < INPUTSIZE; i ++) {
        if (c == inputArray[i] ) {
            return  i;
        }
    }
    return -1;
}
