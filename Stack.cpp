#include<iostream>
using namespace std;

/* Stack.cpp
 * Implementation of STACK ADT using array.
 */

template <typename datatype>
class Stack{
    private:
    int top = -1;
    int const MAXSIZE = 50;
    datatype *datatype_stack;

    public:
    // CONSTRUCTOR
    Stack() {
        datatype_stack = new datatype[MAXSIZE];
    }

    // function to check if the stack is empty
    bool isEmpty() {
        return (top == -1);
    }
    
    // function to check if the stack is full
    bool isFull() {
        return (top == (MAXSIZE - 1));
    }

    // function to push an element into the stack
    void push(datatype element) {
        if (isFull()) {
            return;
        } else {
            datatype_stack[++top] = element;
        }
    }

    // function to pop the top element of the function
    datatype pop() {
        if (isEmpty()) {
            return -1;
        } else {
            datatype top_element = datatype_stack[top];
            top--;
            return top_element;
        }
    }

    // function to release memory allocated by the stack
    void Clear() {
        delete[] datatype_stack;
    }

    // function to return the top of the stack
    datatype peak() {
        if (isEmpty()) {
            return -1;
        } else {
            return datatype_stack[top];
        }
    }

    // function to display the current elements in the stack
    void display() {
        for (int counter = top; counter >= 0; counter--) {
            cout<< datatype_stack[counter]<<endl;
        }
    }
};
