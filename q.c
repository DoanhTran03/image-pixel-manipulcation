
#include <stdio.h>

#define SIZE 5  // Define the maximum size of the queue

typedef struct {
    int x, y;
    float r, g, b, a;
} Object;

Object queue[SIZE];
int front = -1, rear = -1;

// Function to check if the queue is empty
int isEmpty() {
    return front == -1;
}

// Function to check if the queue is full
int isFull() {
    return rear == SIZE - 1;
}

// Function to add an element to the queue
void enqueue(Object value) {
    if (isFull()) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    queue[++rear] = value;
    printf("Enqueued: Object(%d, %d, %.2f, %.2f, %.2f, %.2f)\n", value.x, value.y, value.r, value.g, value.b, value.a);
}

// Function to remove an element from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Dequeued: Object(%d, %d, %.2f, %.2f, %.2f, %.2f)\n", queue[front].x, queue[front].y, queue[front].r, queue[front].g, queue[front].b, queue[front].a);
    if (front == rear) {
        front = rear = -1; // Reset queue when last element is dequeued
    } else {
        front++;
    }
}

// Function to display the queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements:\n");
    for (int i = front; i <= rear; i++) {
        printf("Object(%d, %d, %.2f, %.2f, %.2f, %.2f)\n", queue[i].x, queue[i].y, queue[i].r, queue[i].g, queue[i].b, queue[i].a);
    }
}