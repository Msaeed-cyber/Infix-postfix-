#include <graphics.h>
#include "DSAproject.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawInterface();

    string infix, postfix;
    char infixInput[50];

    displayText(50, 200, "Enter infix expression:");
    getGraphicalInput(50, 220, infixInput, 50);
    infix = string(infixInput);

    try {
        infixToPostfix(infix, postfix);
        displayResult(50, 250, "Postfix Expression: ", postfix);

        int result = evaluatePostfix(postfix);
        displayResult(50, 300, "Evaluation Result: ", to_string(result));
    } catch (const runtime_error& e) {
        displayResult(50, 350, "Error: ", e.what());
    }

    getch();
    closegraph();
    return 0;
}
