#CFLAGS  += `pkg-config --cflags glib-2.0`
#LDFLAGS += `pkg-config --libs glib-2.0`
Object := main.o list.o
List:$(Object)
#	echo "pwd"
	cc -o List $(Object) `pkg-config --libs glib-2.0` -lpthread
#	cd ./mt
#	pwd

main.o:main.c list.h
#	echo "makefie main"
	cc `pkg-config --cflags glib-2.0` -c main.c
list.o:list.c list.h
#	echo "makefie list"
	cc -c list.c

.PHONY:clean
clean:
	rm List *.o

