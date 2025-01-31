#ifndef UNDO_REDO_STACK_H
#define UNDO_REDO_STACK_H

#include <stdio.h>

#define SIZE 5  // Define the maximum size of the stacks

typedef struct {
    int x, y;
    int r, g, b, a;
} Pixel;

// Undo stack
extern Pixel undo_stack[SIZE];
extern int undo_top;
int undo_isEmpty();
int undo_isFull();
void undo_push(Pixel value);
Pixel undo_pop();
void undo_display();

// Redo stack
extern Pixel redo_stack[SIZE];
extern int redo_top;
int redo_isEmpty();
int redo_isFull();
void redo_push(Pixel value);
Pixel redo_pop();
void redo_display();

#endif // UNDO_REDO_STACK_H
