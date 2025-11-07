/* SET 1
Q2. command line ( C:\> in Windows and $ in Linux) and display the computed value of the expression.
    For example: At Linux command prompt,
    $ (23 – 8) *3+ 28/4 followed by Enter key displays
    52
    $
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// ---------- INFIX -> POSTFIX (supports multi-digit) ----------
int infixToPostfix(char *infix, char *postfix) {
    char stack[MAX];
    int top = -1, j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            // extract full number
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // separator
            i--;
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top >= 0 && stack[top] != '(')
                postfix[j++] = stack[top--];
            if (top >= 0) top--;
        }
        else if (isOperator(ch)) {
            while (top >= 0 && precedence(stack[top]) >= precedence(ch))
                postfix[j++] = stack[top--];
            stack[++top] = ch;
        }
        else if (ch == ' ' || ch == '\t') {
            continue;
        }
        else {
            printf("Error: Invalid character '%c'\n", ch);
            return 0;
        }
    }

    while (top >= 0)
        postfix[j++] = stack[top--];

    postfix[j] = '\0';
    return 1;
}

// ---------- POSTFIX EVALUATION ----------
int evaluatePostfix(char *postfix, int *result) {
    int stack[MAX], top = -1;

    for (int i = 0; postfix[i] != '\0'; ) {

        if (isdigit(postfix[i])) {
            int num = 0;

            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            stack[++top] = num;
        }
        else if (isOperator(postfix[i])) {
            if (top < 1) {
                printf("Error: Invalid expression\n");
                return 0;
            }

            int b = stack[top--];
            int a = stack[top--];

            switch (postfix[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        return 0;
                    }
                    stack[++top] = a / b;
                    break;
            }
        }

        i++;
    }

    *result = stack[top];
    return 1;
}

// ---------- MAIN ----------
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    char expression[MAX] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expression, argv[i]);
        strcat(expression, " ");
    }

    char postfix[MAX];
    if (!infixToPostfix(expression, postfix))
        return 1;

    printf("Postfix: %s\n", postfix);

    int result;
    if (!evaluatePostfix(postfix, &result))
        return 1;

    printf("Result: %d\n", result);

    return 0;
}
