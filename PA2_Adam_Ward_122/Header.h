/*
Author: Adam Ward
Date: 5/13/2024
Description: PA2, a music thing. 
*/


#pragma once

#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<windows.h>

typedef struct duration {
	int minutes;
	int seconds;
}Duration;

typedef struct record {
	char artist[50];
	char albumTitle[50];
	char songTitle[50];
	char genre[50];
	int numPlayed;
	int rating;
	Duration songLength;
}Record;

typedef struct node {
	Record data;
	struct node* next;
	struct node* prev;
}Node;

//Linked list manipulation
//create node
Node* create_node(Record* data);
void insert(Node** list_ptr, Record* data);

//opening file
FILE* openFR(char* fileName);
FILE* openFW(char* fileName);

//menu
int menu();

//better strtok
char* stok(char** p, const char* delim);

//better fgets
int getStr(char* buffer, int size);
//load
char* load(FILE* input);

//store
int store(FILE* output, Node* head);

//display
int display(Node* head);

//edit
int edit(Node* head);

//rate
int rate(Node* head);

//play
int play(Node* head);

//teehee
int ErrorPanic();

//insert (named "add")
char* add(Node* head);

//delete
char* delete(Node* head);

//sort
int compare(Node* cmp1, Node* cmp2, int cmp);
char* sort(Node* head);

//shuffle

//okay this gon be weird but trust i think im cooking here
typedef struct shuff {
	int orderInShuff;
}Shuff;

typedef struct nodeShuff {
	Shuff data;
	struct node* next;
	struct node* prev;
}NodeShuff;

NodeShuff* create_shuff_node(Shuff* data);
void insertShuff(NodeShuff** list_ptr, Shuff* data);

int shuffle(Node* head);

void pa3Warning();
#endif
