#include<iostream>
#include<string>
#include<istream>
#include<cmath>
#include "Stack.cpp"
using namespace std;

/* InfixtoPostfix.cpp
 * Conversion from infix expression to postfix expression 
 * and postfix expression evaluation.
 */

// function to check if a mathematical expression is correct by checking the braces
bool checkExpression(string infix_expression) {
    char current_char;
    Stack<char> brace_stack;
    
    for (int i = 0; i < infix_expression.length(); i++) {
        current_char = infix_expression[i];
        // pushing into the stack
        if (current_char == '(' || current_char == '{' || current_char == '[') {
            brace_stack.push(current_char);
        } // popping from the stack if the braces match 
        else if ((current_char == ')' && brace_stack.peak() == '(') || (current_char == '}' && brace_stack.peak() == '{') 
        || (current_char == ']' && brace_stack.peak() == '[')) {
            brace_stack.pop();
        } else continue;
    }
    // checking if the expression is valid or not
    if (brace_stack.isEmpty()) {
        return true;
    } else return false;
}

// function that checks the precedence of the operator
// returns false if operator of higher or equal precedence is already present in the stack
// true otherwise
bool checkPrecedence(char symbol, Stack<char> operator_stack) {
    char peak = operator_stack.peak();
    // if the symbol is + or -
    if (symbol == 43 || symbol == 45) {
        if (peak == 43 || peak == 45 || peak == 42 || peak == 47 || peak == 94) 
            return false;
        else return true;
    } // if the symbol is * or /
    if (symbol == 42 || symbol == 47) {
        if (peak == 42 || peak == 47 || peak == 94)
            return false;
        else return true;
    } // if the symbol is ^
    else return true;
}

string infixToPostfixConversion(string &infix_expression) {
    string postfix_expression;
    Stack<char> operator_stack;
    char current_char;
    int infix_exp_length = infix_expression.length();

    for(int i = 0; i <= infix_exp_length; i++) {
        current_char = infix_expression[i];

        // if the element is a number
        if (current_char > 47 && current_char < 58) {
            postfix_expression.append(1, current_char);
        } // if the element is a left parenthesis
        else if (current_char == '(') {
            operator_stack.push(current_char);
        } // if the element is a right parenthesis 
        else if (current_char == ')') {
            while (operator_stack.peak() != '(') {
                postfix_expression = postfix_expression + ' ' + operator_stack.peak();
                operator_stack.pop();
            }
            operator_stack.pop();
        } // if the element is an operator
        else if (current_char == 43 || current_char == 45 || current_char == 42 || current_char == 47 || current_char == 94) {
            // a space will be added to the postfix string whenever there is an operator in the infix expression
            while (!checkPrecedence(current_char, operator_stack)) {
                postfix_expression = postfix_expression + ' ' + operator_stack.peak();
                operator_stack.pop();
            }
            operator_stack.push(current_char);
            postfix_expression.append(1, ' ');
        } // if the element is something else 
        else{
            continue;
        } 
    }

    // if the operator stack is not empty after the entire infix expression has been iterated through,
    // append all the operators at the end of the postfix expression
    while (!operator_stack.isEmpty()) {
        postfix_expression = postfix_expression + ' ' + operator_stack.peak();
        operator_stack.pop();
    }

    // returning the postfix expression
    return postfix_expression;
}

float postfixEvaluation(string &postfix_expression) {
    Stack<float> float_stack;
    char current_char;
    float  operand_1, operand_2;
    // varible that stores a multi-digit number till space is reached
    string number;
    // this variable is true if a space is encountered after an operator, false otherwise
    bool check_operator;
    int expression_length = postfix_expression.length();

    for (int i = 0; i <= expression_length; i++) {
        current_char = postfix_expression[i];

        // if the element is a number
        if (current_char > 47 && current_char < 58) {
            number += current_char;
            check_operator = false;
        } // if the element is an operator
        else if (current_char == 43 || current_char == 45 || current_char == 42 || current_char == 47 || current_char == 94) {
            check_operator = true;
            // if the operator is +
            if (current_char == 43) {
                operand_2 = float_stack.pop();    operand_1 = float_stack.pop();
                float_stack.push(operand_1 + operand_2);
            } // if the operator is -
            else if (current_char == 45) {
                operand_2 = float_stack.pop();    operand_1 = float_stack.pop();
                float_stack.push(operand_1 - operand_2);
            } // if the operator is *
            else if (current_char == 42) {
                operand_2 = float_stack.pop();    operand_1 = float_stack.pop();
                float_stack.push(operand_1 * operand_2);
            } // if the operator is /
            else if (current_char == 47) {
                operand_2 = float_stack.pop();    operand_1 = float_stack.pop();
                float_stack.push(operand_1 / operand_2);
            } // if the operator is ^
            else {
                operand_2 = float_stack.pop();    operand_1 = float_stack.pop();
                float_stack.push(pow(operand_1, operand_2));
            }
        } // if the element is a space after a number
        else if (current_char == ' ' && check_operator == false) {
            float_stack.push(stof(number));
            number = "";
        }
        else continue;
    }
    // returning the result after expression evaluation
    return float_stack.pop();
}

int main() {
    string infix_expression;
    cout<< "Enter expression: ";
    getline(cin, infix_expression);

    // checking if the expression entered by the user is valid or not 
    if (checkExpression(infix_expression)) {
        // CONVERSION
        string postfix_expression = infixToPostfixConversion(infix_expression);
        cout<<"Postfix Expression: "<<postfix_expression<<endl;
        // EVALUATION
        cout<< "Result: "<< postfixEvaluation(postfix_expression)<<endl;
    } else {
        cout<< "The expression is invalid!"<<endl;
    }
    
}

