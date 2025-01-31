#include "stack.h"

// To compile, run: gcc -o main main.c lib/redo_stack.c -Ilib

int main() {
    Pixel obj1 = {10, 20, 255, 0, 0, 255};
    Pixel obj2 = {30, 40, 0, 255, 0, 255};
    Pixel obj3 = {50, 60, 0, 0, 255, 255};
    
    redo_push(obj1);
    redo_push(obj2);
    redo_push(obj3);

    undo_push(obj1);
    undo_push(obj2);
    undo_push(obj3);

    redo_display();
    undo_display();
    
    redo_pop();
    redo_display();
    
    Pixel obj4 = {70, 80, 255, 255, 0, 255};
    Pixel obj5 = {90, 100, 128, 128, 128, 255};
    Pixel obj6 = {110, 120, 76, 76, 76, 255};
    
    redo_push(obj4);
    redo_push(obj5);
    redo_push(obj6);

    undo_push(obj4);
    undo_push(obj5);
    undo_push(obj6);

    redo_display();
    
    redo_pop();
    redo_pop();
    redo_display();

    undo_pop();
    undo_pop();
    undo_display();
    
    return 0;
}
