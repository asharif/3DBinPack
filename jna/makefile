default:
	gcc -c -fPIC libpack3d.c -o libpack3d.o
	gcc -shared -Wl,-soname,libpack3d.so.1 -o libpack3d.so libpack3d.o
	rm libpack3d.o
clean:
	rm libpack3d.so
