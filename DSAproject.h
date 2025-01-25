#ifndef DSAPROJECT_H
#define DSAPROJECT_H

#include <iostream>
#include <string>
using namespace std;

// Custom stack structure for characters
struct CharStack {
    struct Node {
        char data;
        Node* next;
    };
    Node* top = nullptr;
};

// Custom stack structure for integers
struct IntStack {
    struct Node {
        int data;
        Node* next;
    };
    Node* top = nullptr;
};

// Functions for CharStack
void pushChar(CharStack& stack, char value);
char popChar(CharStack& stack);
bool isEmptyChar(const CharStack& stack);

// Functions for IntStack
void pushInt(IntStack& stack, int value);
int popInt(IntStack& stack);
bool isEmptyInt(const IntStack& stack);

// Conversion and evaluation functions
int precedence(char op);
void infixToPostfix(const string& infix, string& postfix);
int evaluatePostfix(const string& postfix);

// GUI Functions
void drawInterface();
void displayText(int x, int y, const char* text);
void displayResult(int x, int y, const char* label, const string& result);
void getGraphicalInput(int x, int y, char* input, int maxLength);

#endif
