
a.out: main.o linked_list.o 
	gcc -g main.o linked_list.o bubble_sort.o

main.o: main.c linked_list.o linked_list.h
	gcc -g -c main.c


linked_list.o: linked_list.c linked_list.h
	gcc -g -c linked_list.c


clean:
	rm -f main.o linked_list.o

