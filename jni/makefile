default:
	gcc -c -fPIC -I /usr/lib/jvm/java-6-openjdk/include -I /usr/lib/jvm/java-6-openjdk/include/linux libpack3d.c -o libpack3d.o
	gcc -shared -Wl,-soname,libpack3d.so.1 -o libpack3d.so libpack3d.o
	rm libpack3d.o
clean:
	rm libpack3d.so
