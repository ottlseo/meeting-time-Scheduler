server: server.o db.o duplicate.o setFinalTime.o
	gcc -o server server.o db.o duplicate.o setFinalTime.o

server.o : server.c db.h clientCheck.h duplicate.h setFinalTime.h

client: client.o clientCheck.o
	gcc -o client client.o clientCheck.o 
db.o: db.h db.c

setFinalTime.o: setFinalTime.h setFinalTime.c

duplicate.o: duplicate.h duplicate.c

client.o: client.c clientCheck.h

clientCheck.o: clientCheck.h clientCheck.c
