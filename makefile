all:
	gcc -fsanitize=address -o main DLL.c testDLL.c -I. -pthread