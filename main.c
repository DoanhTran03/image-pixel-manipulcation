#include "stack.h"

// To compile, run: gcc -o main main.c lib/stack.c -Ilib

int main() {
    Object obj1 = {10, 20, 255, 0, 0, 255};
    Object obj2 = {30, 40, 0, 255, 0, 255};
    Object obj3 = {50, 60, 0, 0, 255, 255};
    
    push(obj1);
    push(obj2);
    push(obj3);
    display();
    
    pop();
    display();
    
    Object obj4 = {70, 80, 255, 255, 0, 255};
    Object obj5 = {90, 100, 128, 128, 128, 255};
    Object obj6 = {110, 120, 76, 76, 76, 255};
    
    push(obj4);
    push(obj5);
    push(obj6);
    display();
    
    pop();
    pop();
    display();
    
    return 0;
}
