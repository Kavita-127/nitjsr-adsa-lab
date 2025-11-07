/* SET 1 Q1. Implement a function to convert an infix arithmetic expression involving the operators +, -, /, *, (, ) and
single digit constant integer operands to postfix expression. Assume usual precedence of operators in
the order of /, *, + and -. Parentheses ( ) are used to override the precedence of operators. */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

//function to return operator precedence
int precedence(char operator){
    switch(operator){
        case '/': return 3;
        case '*': return 2;
        case '+': return 1;
        case '-': return 0;
        default: return -1; 
    }
}

//function checks if a character is an operator
int yes(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

//convert infix to postfix
void infixToPostfix(char *infix, char *postfix){
    //allocate memory for "operator array"
    char *operArray = malloc(200 * sizeof(char));
    int top = -1;  //top = index of the last element in the stack
    int i = 0; //i = current position in the infix string
    int j = 0; //j = current position in the postfix string

    while (infix[i] != '\0')
    {
        char c = infix[i]; //c storing the current character
        //skip spaces or newline characters
        if(c == ' ' || c == '\t' || c == '\n'){
            i++;
            continue;
        }

        if(isdigit(c)){
            while (isdigit(infix[i])){
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; //separate operands by space
            continue;
        }

        else if (c == '(') //handle left parenthesis
        {
            operArray[++top] = c; //push '(' onto the stack
        }

        else if (c == ')') //handle right parenthesis
        {
            while (top >= 0 && operArray[top] != '('){
                //pop all operators from the stack until '(' comes
                postfix[j++] = operArray[top--];
                postfix[j++] = ' ';
            }
            if(top >= 0 && operArray[top] == '(')
                top--; //remove '('
        }

        else if(yes(c)){
            //check if stack top has an operator with >= precedence
            while(top >= 0 && precedence(operArray[top]) >= precedence(c)){
                //if yes then pop it from stack and put it into postfix
                postfix[j++] = operArray[top--];
                postfix[j++] = ' ';
            }
            //else push the new one
            operArray[++top] = c;
        }

        i++;
    }

        while(top >= 0){
            //pop any remaining operators from the stack and add them to postfix
            postfix[j++] = operArray[top--];
            postfix[j++] = ' ';
        }

        postfix[j] = '\0'; //null terminate
        free(operArray); //free memory
}

int main(){
    //allocate memory for input/output arrays
    char *infix = malloc(200 * sizeof(char));
    char *postfix = malloc(200 * sizeof(char));

    printf("Enter an Infix Expression: ");
    fgets(infix, 200, stdin);

    infixToPostfix(infix, postfix);

    printf("\nInfix Expression: %s", infix);
    printf("Postfix Expression: %s\n", postfix);

    free(infix);
    free(postfix);

    return 0;

}
