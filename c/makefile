default:
	echo no default action.  please specify build_exec, build_lib, clean
build_exec:
	gcc -o pack3d libpack3d.c pack3d.c
build_lib:
	gcc -c -fPIC libpack3d.c -o libpack3d.o
	gcc -shared -Wl,-soname,libpack3d.so.1 -o libpack3d.so libpack3d.o
	rm libpack3d.o
clean:
	rm -f pack3d
	rm -f libpack3d.so

