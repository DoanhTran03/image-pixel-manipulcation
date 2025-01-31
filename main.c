#include "q.h"

//To compile, run: gcc -o main main.c lib/q.c -Ilib

int main() {
    Object obj1 = {10, 20, 255, 0, 0, 255};
    Object obj2 = {30, 40, 0, 255, 0, 255};
    Object obj3 = {50, 60, 0, 0, 255, 255};
    
    enqueue(obj1);
    enqueue(obj2);
    enqueue(obj3);
    display();
    
    dequeue();
    display();
    
    Object obj4 = {70, 80, 255, 255, 0, 255};
    Object obj5 = {90, 100, 128, 128, 128, 255};
    Object obj6 = {110, 120, 76, 76, 76, 255};
    
    enqueue(obj4);
    enqueue(obj5);
    enqueue(obj6);
    display();
    
    dequeue();
    dequeue();
    display();
    
    return 0;
}
