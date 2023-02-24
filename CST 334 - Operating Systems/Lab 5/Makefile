#Name: Jennah Yasin
#Date: April 5, 2022
#Title: Lab5 - Makefile
#Description: Makefile for steps 1-3 for Lab5

threadHello_step1: threadHello_step1.o
	gcc -o threadHello_step1 threadHello_step1.o

threadHello_step1.o: threadHello_step1.c
	gcc -c -o threadHello_step1.o threadHello_step1.c -lpthread

threadHelloFixed_step1_Fixed: threadHelloFixed_step1_Fixed.o
	gcc -o threadHelloFixed_step1_Fixed threadHelloFixed_step1_Fixed.o

threadHelloFixed_step1_Fixed.o: threadHelloFixed_step1_Fixed.c
	gcc -c -o threadHelloFixed_step1_Fixed.o threadHelloFixed_step1_Fixed.c -lpthread

matrix_multiplication: matrix_multiplication.o
	gcc -o matrix_multiplication matrix_multiplication.o

matrix_multiplication.o: matrix_multiplication.c
	gcc -c -o matrix_multiplication.o matrix_multiplication.c -lpthread
