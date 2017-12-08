COMP 2401 Assignment 5 ReadMe.txt

Purpose of Software: To implement a linked list to be used by another program or file.
Developer: Patrick Shipton (101046328)
Development Date: 08/12/2017

File Structure:
	isPrime.c – the base program for checking whether a number is a prime number
	prime.bin – a file that contains 12 unsigned numbers in binary format
	prime.txt – a file that contains 12 unsigned numbers in ASCII format. The numbers correspond to the numbers in the file prime.bin
	createBinary.c – a program that creates a binary file from a given set of numbers
	singlePrime.c - takes in an unsigned int from a binary file and morphs into isPrime.c
	singleSpawn.c - takes in an unsigned int from a binary file and output if the number is prime or not
	multiSpawn.c - takes 10 unsigned ints from a binary file and outputs the prime numbers
	Makefile - makefile for singlePrime
	Makefile2 - makefile for singleSpawn
	Makefile3 - makefile for multiSpawn
	

singlePrime
	How to compile:
		1. go to the containing directory 
		2. run "make -f Makefile singlePrime"
		
	How to use program:
		1. run "./singlePrime filename" 
		(ex: "./singlePrime prime.bin")
		Will return if -1 for error
						1 if prime
						0 if not prime
		
singleSpawn
	How to compile:
		1. go to the containing directory 
		2. run "make -f Makefile2 singleSpawn"
		
	How to use program:
		1. run "./singleSpawn filename" 
		(ex: "./singleSpawn prime.bin")
		Will print if inputed integer is prime or not

multiSpawn
	How to compile:
		1. go to the containing directory 
		2. run "make -f Makefile3 multiSpawn"
		
	How to use program:
		1. run "./multiSpawn filename" 
		(ex: "./multiSpawn prime.bin")
		The prime numbers from the file will be printed

Issues/Limitations: 
	Assumtions: 
	- the input files for singlePrime and singleSpawn contain at least one unsigned integer
	- the input file for multiSpawn contains at least 10 unsigned integers 
	