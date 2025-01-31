#ifndef STACK_H
#define STACK_H

#include <stdio.h>

#define SIZE 5  // Define the maximum size of the stack

typedef struct {
    int x, y;
    int r, g, b, a;
} Object;

extern Object stack[SIZE];
extern int top;

// Function prototypes
int isEmpty();
int isFull();
void push(Object value);
Object pop();
void display();

#endif // STACK_H
