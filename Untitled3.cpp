#include "DSAproject.h"
#include <graphics.h>
#include <stdexcept>

// Functions for CharStack
void pushChar(CharStack& stack, char value) {
    CharStack::Node* newNode = new CharStack::Node;
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

char popChar(CharStack& stack) {
    if (stack.top == nullptr) throw runtime_error("Stack underflow");
    CharStack::Node* temp = stack.top;
    char value = temp->data;
    stack.top = stack.top->next;
    delete temp;
    return value;
}

bool isEmptyChar(const CharStack& stack) {
    return stack.top == nullptr;
}

// Functions for IntStack
void pushInt(IntStack& stack, int value) {
    IntStack::Node* newNode = new IntStack::Node;
    newNode->data = value;
    newNode->next = stack.top;
    stack.top = newNode;
}

int popInt(IntStack& stack) {
    if (stack.top == nullptr) throw runtime_error("Stack underflow");
    IntStack::Node* temp = stack.top;
    int value = temp->data;
    stack.top = stack.top->next;
    delete temp;
    return value;
}

bool isEmptyInt(const IntStack& stack) {
    return stack.top == nullptr;
}

// Conversion and evaluation functions
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(const string& infix, string& postfix) {
    CharStack stack;
    postfix = "";
    bool expectOperand = true;

    for (char ch : infix) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix += ch;
            expectOperand = false;
        } else if (ch == '(') {
            pushChar(stack, ch);
            expectOperand = true;
        } else if (ch == ')') {
            while (!isEmptyChar(stack) && stack.top->data != '(') {
                postfix += popChar(stack);
            }
            if (!isEmptyChar(stack) && stack.top->data == '(') {
                popChar(stack);
            } else {
                throw runtime_error("Unmatched parentheses");
            }
            expectOperand = false;
        } else {
            if (expectOperand) throw runtime_error("Invalid operator placement");
            while (!isEmptyChar(stack) && precedence(stack.top->data) >= precedence(ch)) {
                postfix += popChar(stack);
            }
            pushChar(stack, ch);
            expectOperand = true;
        }
    }

    while (!isEmptyChar(stack)) {
        if (stack.top->data == '(') throw runtime_error("Unmatched parentheses");
        postfix += popChar(stack);
    }
    if (expectOperand) throw runtime_error("Expression ends with an operator");
}

int evaluatePostfix(const string& postfix) {
    IntStack stack;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            pushInt(stack, ch - '0');
        } else {
            if (stack.top == nullptr || stack.top->next == nullptr) {
                throw runtime_error("Stack underflow: Missing operands");
            }
            int b = popInt(stack);
            int a = popInt(stack);

            switch (ch) {
                case '+': pushInt(stack, a + b); break;
                case '-': pushInt(stack, a - b); break;
                case '*': pushInt(stack, a * b); break;
                case '/':
                    if (b == 0) throw runtime_error("Division by zero");
                    pushInt(stack, a / b);
                    break;
                default: throw runtime_error("Invalid operator");
            }
        }
    }

    if (stack.top == nullptr || stack.top->next != nullptr) {
        throw runtime_error("Invalid postfix expression");
    }

    return popInt(stack);
}

// GUI Functions
void drawInterface() {
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLUE);
    rectangle(10, 10, 630, 470);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(200, 20, (char*)"Expression Evaluator");
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

void displayText(int x, int y, const char* text) {
    setcolor(BLACK);
    outtextxy(x, y, "Enter infix Expression : ");
}

void displayResult(int x, int y, const char* label, const string& result) {
    string output = string(label) + result;
    char writableOutput[output.size() + 1];
    strcpy(writableOutput, output.c_str());
    setcolor(BLACK);
    outtextxy(x, y, writableOutput);
}

void getGraphicalInput(int x, int y, char* input, int maxLength) {
    char ch;
    int i = 0;

    while (true) {
        ch = getch();
        if (ch == 13) { // Enter key
            input[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                setcolor(WHITE);
                outtextxy(x + i * 10, y, " ");
            }
        } else if (i < maxLength - 1) {
            input[i++] = ch;
            char tempStr[2] = {ch, '\0'};
            outtextxy(x + (i - 1) * 10, tempStr);
        }
    }
}
