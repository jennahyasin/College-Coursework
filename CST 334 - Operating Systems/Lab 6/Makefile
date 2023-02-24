#Name: Jennah Yasin
#Date: April 12, 2022
#Title: Makefile Lab 6
#Description: Makefile for both steps, 1 & 2 of Lab 6. 

threadSync: threadSync.o
	gcc -o threadSync threadSync.o
	
threadSync.o: threadSync.c
	gcc -c -o threadSync.o threadSync.c -lpthread

Lab6: Lab6.o
	gcc -o Lab6 Lab6.o

Lab6.o: Lab6.c
	gcc -c -o Lab6.o Lab6.c -lpthread

