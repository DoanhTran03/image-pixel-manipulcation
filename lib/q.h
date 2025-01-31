#ifndef Q_H
#define Q_H

#include <stdio.h>

#define SIZE 5  // Define the maximum size of the queue

typedef struct {
    int x, y;
    int r, g, b, a;
} Object;

extern Object queue[SIZE];
extern int front, rear;

// Function prototypes
int isEmpty();
int isFull();
void enqueue(Object value);
void dequeue();
void display();

#endif // QUEUE_H
