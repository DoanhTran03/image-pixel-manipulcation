#include <stdio.h>

#define SIZE 5  // Define the maximum size of the stack

typedef struct {
    int x, y;
    int r, g, b, a;
} Object;

Object stack[SIZE];
int top = -1;

// Function to check if the stack is empty
int isEmpty() {
    return top == -1;
}

// Function to check if the stack is full
int isFull() {
    return top == SIZE - 1;
}

// Function to push an element onto the stack
void push(Object value) {
    if (isFull()) {
        printf("Stack is full!\n");
        return;
    }
    stack[++top] = value;
    printf("Pushed: Object(%d, %d, %d, %d, %d, %d)\n", value.x, value.y, value.r, value.g, value.b, value.a);
}

// Function to pop an element from the stack and return it
Object pop() {
    Object emptyObject = {-1, -1, -1, -1, -1, -1};
    if (isEmpty()) {
        printf("Stack is empty!\n");
        return emptyObject;
    }
    Object poppedObject = stack[top--];
    printf("Popped: Object(%d, %d, %d, %d, %d, %d)\n", poppedObject.x, poppedObject.y, poppedObject.r, poppedObject.g, poppedObject.b, poppedObject.a);
    return poppedObject;
}

// Function to display the stack
void display() {
    if (isEmpty()) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements:\n");
    for (int i = top; i >= 0; i--) {
        printf("Object(%d, %d, %d, %d, %d, %d)\n", stack[i].x, stack[i].y, stack[i].r, stack[i].g, stack[i].b, stack[i].a);
    }
}
