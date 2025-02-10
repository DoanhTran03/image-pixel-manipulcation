gcc $(pkg-config --cflags gtk4) -o main main.c lib/stack.c $(pkg-config --libs gtk4) -Ilib

./main
