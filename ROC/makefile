ROCmain : testReconnaissance.o image.o tab2Ddynamique.o affichage.o
	gcc -lm ROCmain.o testReconnaissance.o image.o tab2Ddynamique.o affichage.o -o ROCmain

ROCmain.o : ROCmain.c
	gcc -c ROCmain.c

testReconnaissance.o : testReconnaissance_v2.c testReconnaissance_v2.h
	gcc -c testReconnaissance_v2.c 

image.o : image.c image.h
	gcc -c image.c

tab2Ddynamique.o : tab2Ddynamique.c tab2Ddynamique.h
	gcc -c tab2Ddynamique.c

affichage.o : affichage.c affichage.h
	gcc -c affichage.C
