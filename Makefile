#Makefile for Hashtags program

make: hashtags.c main.c
	gcc -std=c99 hashtags.c main.c -o hashtags	
