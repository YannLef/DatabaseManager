exec: main.o fonctions.o interpreteRequeteSQL.o recupereFichiers.o
	gcc main.o fonctions.o interpreteRequeteSQL.o recupereFichiers.o -o  exec
	
main.o: main.c fonctions.h interpreteRequeteSQL.h recupereFichiers.h
	gcc -c -Wall main.c
	
interpreteRequeteSQL.o: interpreteRequeteSQL.c fonctions.h interpreteRequeteSQL.h recupereFichiers.h
	gcc -c -Wall interpreteRequeteSQL.c

fonctions.o: fonctions.c fonctions.h interpreteRequeteSQL.h recupereFichiers.h
	gcc -c -Wall fonctions.c
	
recupereFichiers.o: recupereFichiers.c  recupereFichiers.h fonctions.h interpreteRequeteSQL.h
	gcc -c -Wall recupereFichiers.c
