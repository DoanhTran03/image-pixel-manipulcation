#include <stdio.h>

#define SIZE 100  // Define the maximum size of the undo_stack

typedef struct {
    int x, y;
    int r, g, b, a;
} Pixel;

Pixel undo_stack[SIZE];
int undo_top = -1;

// Function to check if the undo_stack is empty
int undo_isEmpty() {
    return undo_top == -1;
}

// Function to check if the undo_stack is full
int undo_isFull() {
    return undo_top == SIZE - 1;
}

// Function to push an element onto the undo_stack
void undo_push(Pixel value) {
    if (undo_isFull()) {
        printf("undo_stack is full!\n");
        return;
    }
    undo_stack[++undo_top] = value;
    printf("Pushed: Pixel(%d, %d, %d, %d, %d, %d)\n", value.x, value.y, value.r, value.g, value.b, value.a);
}

// Function to pop an element from the undo_stack and return it
Pixel undo_pop() {
    Pixel emptyPixel = {-1, -1, -1, -1, -1, -1};
    if (undo_isEmpty()) {
        printf("undo_stack is empty!\n");
        return emptyPixel;
    }
    Pixel poppedPixel = undo_stack[undo_top--];
    printf("Popped: Pixel(%d, %d, %d, %d, %d, %d)\n", poppedPixel.x, poppedPixel.y, poppedPixel.r, poppedPixel.g, poppedPixel.b, poppedPixel.a);
    return poppedPixel;
}

// Function to display the undo_stack
void undo_display() {
    if (undo_isEmpty()) {
        printf("undo_stack is empty!\n");
        return;
    }
    printf("undo_stack elements:\n");
    for (int i = undo_top; i >= 0; i--) {
        printf("Pixel(%d, %d, %d, %d, %d, %d)\n", undo_stack[i].x, undo_stack[i].y, undo_stack[i].r, undo_stack[i].g, undo_stack[i].b, undo_stack[i].a);
    }
}

Pixel redo_stack[SIZE];
int redo_top = -1;

// Function to check if the redo_stack is empty
int redo_isEmpty() {
    return redo_top == -1;
}

// Function to check if the redo_stack is full
int redo_isFull() {
    return redo_top == SIZE - 1;
}

// Function to push an element onto the redo_stack
void redo_push(Pixel value) {
    if (redo_isFull()) {
        printf("redo_stack is full!\n");
        return;
    }
    redo_stack[++redo_top] = value;
    printf("Pushed: Pixel(%d, %d, %d, %d, %d, %d)\n", value.x, value.y, value.r, value.g, value.b, value.a);
}

// Function to pop an element from the redo_stack and return it
Pixel redo_pop() {
    Pixel emptyPixel = {-1, -1, -1, -1, -1, -1};
    if (redo_isEmpty()) {
        printf("redo_stack is empty!\n");
        return emptyPixel;
    }
    Pixel poppedPixel = redo_stack[redo_top--];
    printf("Popped: Pixel(%d, %d, %d, %d, %d, %d)\n", poppedPixel.x, poppedPixel.y, poppedPixel.r, poppedPixel.g, poppedPixel.b, poppedPixel.a);
    return poppedPixel;
}

// Function to display the redo_stack
void redo_display() {
    if (redo_isEmpty()) {
        printf("redo_stack is empty!\n");
        return;
    }
    printf("redo_stack elements:\n");
    for (int i = redo_top; i >= 0; i--) {
        printf("Pixel(%d, %d, %d, %d, %d, %d)\n", redo_stack[i].x, redo_stack[i].y, redo_stack[i].r, redo_stack[i].g, redo_stack[i].b, redo_stack[i].a);
    }
}