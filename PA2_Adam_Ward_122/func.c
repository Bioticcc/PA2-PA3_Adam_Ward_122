#include "Header.h"
//opening file

void pa3Warning() {
	system("cls");
	printf("\n[AREA OFF LIMITS] - Come back when PA3 is due ;3\n");
	system("pause");
}

int ErrorPanic(){
	system("cls");
	for (int i = 0; i < 250; i++) {
		
		printf("<[ERROR]>");
		Sleep(1);
	}
	printf("\n\nJUST KIDDING! :D\n\n");
	system("pause");
	//clear();
}

FILE* openFR(char* fileName) {
	FILE* input = fopen(fileName, "r");
	if (input == NULL) {
		printf("File failed to open\n");
		return -1;
	}
	else {
		printf("File opened for mode READ successfully!\n");
		return input;
	}
}

FILE* openFW(char* fileName) {
	FILE* input = fopen(fileName, "w");
	if (input == NULL) {
		printf("File failed to open\n");
		return -1;
	}
	else {
		printf("File opened for mode WRITE successfully!\n");
		return input;
	}
}

int menu() {
	int choice = 0;
	printf("|----------Musinx, Your Digital Music Manager!----------|\n");
	printf("|\t\t        (1) LOAD\t\t\t|\n");
	printf("|\t\t        (2) STORE\t\t\t|\n");
	printf("|\t\t       (3) DISPLAY\t\t\t|\n");
	printf("|\t\t       (4) INSERT\t\t\t|\n");
	printf("|\t\t       (5) DELETE\t\t\t|\n");
	printf("|\t\t        (6) EDIT\t\t\t|\n");
	printf("|\t\t        (7) SORT\t\t\t|\n");
	printf("|\t\t        (8) RATE\t\t\t|\n");
	printf("|\t\t        (9) PLAY\t\t\t|\n");
	printf("|\t\t      (10) SHUFFLE\t\t\t|\n");
	printf("|\t\t       (11) EXIT\t\t\t|\n");
	printf("|\t\t       (12) RUN TESTS\t\t\t|\n");
	printf("|-------------------------------------------------------|\n");
	printf("|---Now then, where to? (#)--->: ");
	//printf("%d",_getch());
	scanf("%d", &choice);

	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11 && choice != 12) {
		printf("|---Choose a menu option, please! (#)--->: ");
		scanf("%*s"); //should clear buffer
		scanf("%d", &choice);
	}
	return choice;
}

//node things
Node* create_node(Record* data) {
	Node* mem_ptr = malloc(sizeof(Node));

	if (mem_ptr != NULL) {
		mem_ptr->next = NULL;
		mem_ptr->prev = NULL;
		mem_ptr->data = *data;
	}
	return mem_ptr;
}

NodeShuff* create_shuff_node(Shuff* data) {
	NodeShuff* mem_ptr = malloc(sizeof(NodeShuff));

	if (mem_ptr != NULL) {
		mem_ptr->next = NULL;
		mem_ptr->prev = NULL;
		mem_ptr->data = *data;
	}
	return mem_ptr;
}

//inserting at front of list
void insert(Node** list_ptr, Record* data) {
	Node* mem_ptr = create_node(data);
	//an empty list
	if (*list_ptr == NULL) {
		*list_ptr = mem_ptr;
		//empty
	}
	else {
		//not empty
		mem_ptr->next = *list_ptr;
		(*list_ptr)->prev = mem_ptr;
		*list_ptr = mem_ptr;
	}
}

void insertShuff(NodeShuff** list_ptr, Shuff* data){
	NodeShuff* mem_ptr = create_shuff_node(data);
	if (*list_ptr == NULL) {
		*list_ptr = mem_ptr;
	}
	else {
		mem_ptr->next = *list_ptr;
		(*list_ptr)->prev = mem_ptr;
		*list_ptr = mem_ptr;
	}
}

//better fgets
int getStr(char *buffer, int size) {
	int clear;
	//while ((clear = getchar()) != '\n' && clear != EOF);
	fgets(buffer, size, stdin);
	int length = strlen(buffer);
	if (length > 0 && buffer[length - 1] == '\n') {
		//replaces newline with null char ;3
		buffer[length - 1] = '\0';
	}
	return 1;
}

//better strtok()
char* stok(char** p, const char* delim) {
	if (*p == NULL||**p=='\n') return NULL;
	char* s = *p;
	if (s) {
		char* e = s + strcspn(s, delim);
		if (*e)
			*e++ = '\0';
		else
			e = 0;
		*p = e;
	}
	return s;
}

//reading from .csv
char* load(FILE* input) {
	int track = 1;
	Node* head = NULL;
	char* record[100];
	char* tok;
	char* tokS;
	//printf("|-------------PLAYLIST-------------->\n");
	while (fgets(record, 100, input) != NULL) {
		Record data;
		int c = 0;
		int a = 0;
		//printf("\-------------\n");
		for (char* p = record; (tok = stok(&p, ",\n")); ) {
			switch (c)
			{
			case 0:
				//printf("\n%c\n", tok[0]);
				if (tok[0] == '"') { //means has first and last name
					//printf("testing: %s\n", tok);
					strcpy(data.artist, tok);
					tokS = stok(&p, ",");
					//printf("%s", tokS);
					strcat(data.artist, ",");
					strcat(data.artist, tokS);
					//getting rid of them damned quotations
					int length = strlen(data.artist);
					memmove(data.artist, data.artist + 1, length);
					data.artist[strlen(data.artist) - 1] = '\0';
					//printf("%s\n", data.artist);

				}
				else {
					//printf("%s\n", tok);
					strcpy(data.artist, tok);
				}
				break;
			case 1:
				//if (a) stok(&p, ",\n");
				//printf("%s\n", tok);
				strcpy(data.albumTitle, tok);
				break;
			case 2: 
				//printf("%s\n", tok);
				strcpy(data.songTitle, tok);
				break;
			case 3:
				//printf("%s\n", tok);
				strcpy(data.genre, tok);
				break;
			case 4:
				//printf("%s\n", tok);
				tokS = strtok(tok, ":");
				data.songLength.minutes = atoi(tokS);
				tokS = strtok(NULL, ":");
				data.songLength.seconds = atoi(tokS);
				break;
			case 5:
				//printf("%s\n", tok);
				data.numPlayed = atoi(tok);
				break;
			case 6:
				//printf("%s\n", tok);
				data.rating = atoi(tok);
				break;
			}
			c++;
		}
		track++;
		insert(&head, &data);
	}
	printf("Songs loaded successfully!\n");
	return head; //THE PROBLEM CHILD. shit aint returning what I want it to be returning idk. sadge
}

int store(FILE* output, Node* head) {

	if (head == NULL) {
		printf("SHIT AINT WORKIN CHIEF\n");
		return 0;
	}
	Node* curr = head;
	while (curr != NULL) {

		if (strlen(curr->data.artist) >= 10) {
			fprintf(output, "\"%s\",", curr->data.artist);
		}
		else {
			fprintf(output, "%s,", curr->data.artist);
		}


		fprintf(output, "%s,", curr->data.albumTitle);
		fprintf(output, "%s,", curr->data.songTitle);
		fprintf(output, "%s,", curr->data.genre);
		fprintf(output, "%d:", curr->data.songLength.minutes);
		fprintf(output, "%d,", curr->data.songLength.seconds);
		fprintf(output, "%d,", curr->data.numPlayed);
		fprintf(output, "%d,", curr->data.rating);
		fprintf(output, "\n");
		//printf("makin progress, chief.\n");
		curr = curr->next;
	}
	printf("Songs stored successfully!\n");
	return 1;
}

int display(Node* head) {
	int clear;
	int x = 0;
	printf("|--------DISPLAY-------->\n");
	printf("|(1) view all tracks\n");
	printf("|(2) view tracks by (artist)\n");
	printf("|(1/2): ");
	scanf("%d", &x);
	
	if (x == 1) {
		system("cls");
		printf("|-------PLAYLIST------>\n");
		int track = 1;
		Node* curr = head;
		while (curr != NULL) {
			printf("\n|----TRACK:[%d]---->\n", track); track++;
			printf("|%s\n", curr->data.artist);
			printf("|%s\n", curr->data.albumTitle);
			printf("|%s\n", curr->data.songTitle);
			printf("|%s\n", curr->data.genre);
			printf("|%d:", curr->data.songLength.minutes);
			printf("%d\n", curr->data.songLength.seconds);
			printf("|%d\n", curr->data.numPlayed);
			printf("|%d\n", curr->data.rating);
			curr = curr->next;
		}
		system("pause");
	}
	if (x == 2) {
		system("cls");
		printf("|----Currently Loaded Artists---->\n");
		Node* curr = head;
		while (curr != NULL) {
			printf("|%s\n", curr->data.artist);
			curr = curr->next;
		}
		
		//clearing input buffer
		int clear;
		while ((clear = getchar()) != '\n' && clear != EOF);
		
		char artist[100];
		printf("\n|Artist for lookup (PLEASE ENTER NAME EXACTLY AS SHOWN): ");
		getStr(artist, 100);
		printf("\n|Displaying songs by: %s\n", artist);
		/*
		//clearing input buffer
		while ((clear = getchar()) != '\n' && clear != EOF);*/
		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.artist, artist) == 0) {
				printf("|Album: %s, Song: %s\n", curr->data.albumTitle, curr->data.songTitle);
			}
			else {
				//printf("|Target: %s - Artist: %s - strcmp(): %d\n", artist, curr->data.artist, strcmp(artist, curr->data.artist));
			}
			curr = curr->next;
		}
		system("pause");
	}
	return 1;
}

int edit(Node* head) {
	//clearing buffer
	int clear;
	while ((clear = getchar()) != '\n' && clear != EOF);
	printf("|----Currently Loaded Songs----|\n");
	Node* curr = head;
	while (curr != NULL) {
		printf("|%s(%d:%d) - %s\n", curr->data.songTitle, curr->data.songLength.minutes, curr->data.songLength.seconds, curr->data.artist);
		curr = curr->next;
	}
	printf("\n|Artist for lookup: ");
	char artist[50];
	getStr(artist, 50);
	
	curr = head;
	int i = 0;
	while (curr != NULL) {
		if (strcmp(curr->data.artist, artist) == 0) {
			i++;
		}
		curr = curr->next;
	}
	char song[100];
	if (i > 1) {
		//means more then 1 song for given artist
		printf("\n|----Songs By: %s----|\n", artist);
		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.artist, artist) == 0) {
				printf("|Album: %s, Song: %s\n", curr->data.albumTitle, curr->data.songTitle);
			}
			curr = curr->next;
		}
		printf("\n|More then one song found.\n|Please type in desired song name EXACTLY as displayed: ");
		getStr(song, 100);
		printf("Chosen Song: %s\n", song);

		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.songTitle, song) == 0) {
				int z = 1;
				while (z) {
					system("cls");
					printf("|----Edit Attributes of Selected Song---->\n");
					printf("|(1)Artist: %s\n", curr->data.artist);
					printf("|(2)Song: %s\n", curr->data.songTitle);
					printf("|(3)Album: %s\n", curr->data.albumTitle);
					printf("|(4)Genre: %s\n", curr->data.genre);
					printf("|(5)Length: %d:%d\n", curr->data.songLength.minutes, curr->data.songLength.seconds);
					printf("|(6)Played: %d\n", curr->data.numPlayed);
					printf("|(7)Rating: %d\n", curr->data.rating);
					printf("|(1-7): ");
					int toEdit;
					char Edit[100];
					int EditI;
					scanf("%d", &toEdit);
					int clear;
					while ((clear = getchar()) != '\n' && clear != EOF);
					switch (toEdit)
					{
					case 1:
						printf("|--Now editing:[Artist]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.artist, Edit);
						break;
					case 2:
						printf("|--Now editing:[Song]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.songTitle, Edit);

						break;
					case 3:
						printf("|--Now editing:[Album]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.albumTitle, Edit);
						break;
					case 4:
						printf("|--Now editing:[Genre]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.genre, Edit);
						break;
					case 5:
						printf("|--Now editing:[Length]--\n");
						printf("|(int) Min: ");
						scanf("%d", &EditI);
						curr->data.songLength.minutes = EditI;
						printf("|(int) Sec: ");
						scanf("%d", &EditI);
						curr->data.songLength.seconds = EditI;
						break;
					case 6:
						printf("|--Now editing:[Played]-->\n");
						printf("|(int): ");
						scanf("%d", &EditI);
						curr->data.numPlayed = EditI;

						break;
					case 7:
						printf("|--Now editing:[Rating]-->\n");
						printf("|(int): ");
						scanf("%d", &EditI);
						curr->data.rating = EditI;
						break;
					default:
						printf("\nBad choice idiot\n");
						for (int i = 0; i < 10000; i++) {
							printf("[ERROR]");
						}
						break;
					}
					printf("\n|Edit more?\n|(1) Yes\n|(0) No\n|(1-0): ");
					scanf("%d", &z);
				}
				//now the switch case D:
			}
			curr = curr->next;
		}
	}
	else {
		char song[100];
		printf("\n|----Songs By: %s----|\n", artist);
		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.artist, artist) == 0) {
				printf("|Album: %s, Song: %s\n", curr->data.albumTitle, curr->data.songTitle);
				strcpy(song, curr->data.songTitle);
			}
			curr = curr->next;
		}
		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.songTitle, song) == 0) {
				int z = 1;
				while (z) {
					system("cls");
					printf("|----Edit Attributes of Selected Song---->\n");
					printf("|(1)Artist: %s\n", curr->data.artist);
					printf("|(2)Song: %s\n", curr->data.songTitle);
					printf("|(3)Album: %s\n", curr->data.albumTitle);
					printf("|(4)Genre: %s\n", curr->data.genre);
					printf("|(5)Length: %d:%d\n", curr->data.songLength.minutes, curr->data.songLength.seconds);
					printf("|(6)Played: %d\n", curr->data.numPlayed);
					printf("|(7)Rating: %d\n", curr->data.rating);
					printf("|(1-7): ");
					int toEdit;
					char Edit[100];
					int EditI;
					scanf("%d", &toEdit);
					int clear;
					while ((clear = getchar()) != '\n' && clear != EOF);
					switch (toEdit)
					{
					case 1:
						printf("|--Now editing:[Artist]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.artist, Edit);
						break;
					case 2:
						printf("|--Now editing:[Song]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.songTitle, Edit);

						break;
					case 3:
						printf("|--Now editing:[Album]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.albumTitle, Edit);
						break;
					case 4:
						printf("|--Now editing:[Genre]-->\n");
						printf("|(str): ");
						getStr(Edit, 100);
						strcpy(curr->data.genre, Edit);
						break;
					case 5:
						printf("|--Now editing:[Length]--\n");
						printf("|(int) Min: ");
						scanf("%d", &EditI);
						curr->data.songLength.minutes = EditI;
						printf("|(int) Sec: ");
						scanf("%d", &EditI);
						curr->data.songLength.seconds = EditI;
						break;
					case 6:
						printf("|--Now editing:[Played]-->\n");
						printf("|(int): ");
						scanf("%d", &EditI);
						curr->data.numPlayed = EditI;

						break;
					case 7:
						printf("|--Now editing:[Rating]-->\n");
						printf("|(int): ");
						scanf("%d", &EditI);
						curr->data.rating = EditI;
						break;
					default:
						printf("\nBad choice idiot\n");
						for (int i = 0; i < 10000; i++) {
							printf("[ERROR]");
						}
						break;
					}
					printf("\n|Edit more?\n|(1) Yes\n|(0) No\n|(1-0): ");
					scanf("%d", &z);
				}
				//now the switch case D:
			}
			curr = curr->next;
		}

	}


	system("pause");
}

int rate(Node* head) {
	//clearing buffer
	int clear;
	int i = 1;
	while ((clear = getchar()) != '\n' && clear != EOF);
	Node* curr = head;
	printf("|----Currently Rateable Songs----|\n");
	while (curr != NULL) {
		printf("|[%d] %s(%d:%d) - %s\n",i, curr->data.songTitle, curr->data.songLength.minutes, curr->data.songLength.seconds, curr->data.artist);
		curr = curr->next;
		i++;
	}
	char toRate[100];
	printf("|Please enter the song name EXACTLY as it appears.\n|Song name: ");
	getStr(toRate, 100);
	curr = head;
	while (curr != NULL) {
		if (strcmp(curr->data.songTitle, toRate) == 0) {
			printf("|%s (%d:%d) - %s | RATING: %d\n", curr->data.songTitle, curr->data.songLength.minutes, curr->data.songLength.seconds, curr->data.artist, curr->data.rating);
			printf("|New rating from 1 to 5: ");
			int rating;
			scanf("%d", &rating);
			if (rating <= 5 && rating >= 1) {
				curr->data.rating = rating;
				system("pause");
				break;
			}
			else {
				printf("|Please enter a number between 1 and 5: ");
				scanf("%d", &rating);
				curr->data.rating = rating;
				system("pause");
				break;
			}
		}
		curr = curr->next;
	}

}

int play(Node* head) {
	system("cls");
	printf("|----PLAYING---->\n");
	Node* curr = head;
	while (curr != NULL) {
		printf("|%s\n", curr->data.artist);
		printf("|%s\n", curr->data.albumTitle);
		printf("|%s\n", curr->data.songTitle);
		printf("|%s\n", curr->data.genre);
		printf("|%d:", curr->data.songLength.minutes);
		printf("%d\n", curr->data.songLength.seconds);
		printf("|%d\n", curr->data.numPlayed);
		printf("|%d\n", curr->data.rating);
		printf("|--------------->\n\n");

		printf("\\(*O*)/\n\n");

		Sleep(1000);
		curr = curr->next;
	}

}

char* add(Node* head) {
	int clear;
	while ((clear = getchar()) != '\n' && clear != EOF);
	Record newRec;	
	char songLenMin[10];
	char songLenSec[10];
	char rating[10];
	char numPlayed[10];
	printf("|----New Song Info---->\n");
	printf("|Artist: ");
	getStr(newRec.artist, 50);
	printf("|Song: ");
	getStr(newRec.songTitle, 50);
	printf("|Album: ");
	getStr(newRec.albumTitle, 50);
	printf("|Genre: ");
	getStr(newRec.genre, 50);
	printf("|Song Length MINUTES: ");
	getStr(songLenMin, 10);
	newRec.songLength.minutes = atoi(songLenMin);
	printf("|Song Length SECONDS: ");
	getStr(songLenSec, 10);
	newRec.songLength.seconds = atoi(songLenSec);
	printf("|Rating: ");
	getStr(rating, 50);
	newRec.rating = atoi(rating);
	printf("|Num Played: ");
	getStr(numPlayed, 50);
	newRec.numPlayed = atoi(numPlayed);

	printf("|--Entering into playlist-->\n");
	printf("|Artist: %s\n", newRec.artist);
	printf("|Album: %s\n", newRec.albumTitle);
	printf("|Song: %s\n", newRec.songTitle);
	printf("|Genre: %s\n", newRec.genre);
	printf("|Song Length: %d:", newRec.songLength.minutes);
	printf("%d\n", newRec.songLength.seconds);
	printf("|Num Played: %d\n", newRec.numPlayed);
	printf("|Rating: %d\n", newRec.rating);

	insert(&head, &newRec);
	system("pause");
	return head;
}

char* delete(Node* head) {
	int clear;
	while ((clear = getchar()) != '\n' && clear != EOF);
	char song[100];
	
	printf("|--Deleting Song-->\n");
	printf("|Currently loaded songs:\n");
	int checka = 0;
	Node* curr = head;
	while (curr != NULL) {
		printf("|%s\n", curr->data.songTitle);
		checka++;
		curr = curr->next;
	}

	printf("|Song Name: ");
	getStr(song, 100);
	printf("Chosen Song: %s\n", song);

	if (checka == 1) {
		int z = 0;
		//only one song in list, so deletes list as a whole? i guess?
		printf("\nWARNING: There is only ONE song in your playlist. Deleting will delete entire playlist.\n");
		printf("(1) continue\n(0) go back! save yourself!\nDecision: ");
		scanf("%d", &z);
		if (z) {
			//deleting entire list. que?? what do?? dunno... tis weird D:
			//set head pointer to NULL? i guess? what about the memory though.... tragedy strikes once more
			//i guess just free(curr)??? IM CONFUSEDDDD (the dramatic music in my ears makes this 10x more tragic and disasterous)
			head->prev = NULL;
			head->next = NULL;
			head = NULL;
			free(head);
			return head;
		}
	}

	curr = head;
	while (curr != NULL) {
		if (strcmp(curr->data.songTitle, song) == 0) {
			printf("\n|Deleting song...\n");

			//checking if curr is either the FIRST or LAST node in the list
			if (curr->prev == NULL) {
				//means its the first in list
				printf("\nDeleting FIRST song\n");
				curr->next->prev = NULL;
				head = curr->next;
				system("pause");
			}
			else if(curr->next == NULL){
				//means its the last in the list
				curr->prev->next = NULL;
				printf("\nDeleting LAST song\n");
				system("pause");

			}
			else {
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				printf("\nDeleting MIDDLE song\n");
				system("pause");

			}
			free(curr);
			return head;
		}

		curr = curr->next;
	}
}

int compare(Node* cmp1, Node* cmp2, int cmp) {
	switch (cmp) {
	case 1:
		return strcmp(cmp1->data.artist, cmp2->data.artist);
	case 2:
		return strcmp(cmp1->data.albumTitle, cmp2->data.albumTitle);
	case 3:
		return (cmp1->data.rating - cmp2->data.rating);
	case 4:
		return (cmp1->data.numPlayed - cmp2->data.numPlayed);
	}
}

char* sort(Node* head) {
	printf("|--Sorting Playlist-->\n");
	printf("|(1)Sort by ARTIST (A-Z)\n");
	printf("|(2)Sort by ALBUM (A-Z)\n");
	printf("|(3)Sort by RATING (1-5)\n");
	printf("|(4)Sort by NUM PLAYED (large - small)\n");
	printf("|Enter (1-4): ");
	int a = 0;
	scanf("%d", &a);
	
	Node* i = head;
	Node* j;
	Node* min;
	Record temp = i->data;

	while (i != NULL) {
		j = i->next;
		min = i;
		while (j != NULL) {
			if (compare(min, j, a) > 0) {
				min = j;
			}
			j = j->next;	
		}

		if (min!=i) {
			//swap em!
			//setting temp = i
			strcpy(temp.artist, i->data.artist);
			strcpy(temp.albumTitle, i->data.albumTitle);
			strcpy(temp.songTitle, i->data.songTitle);
			strcpy(temp.genre, i->data.genre);
			temp.rating = i->data.rating;
			temp.numPlayed = i->data.numPlayed;
			temp.songLength.minutes = i->data.songLength.minutes;
			temp.songLength.seconds = i->data.songLength.seconds;

			//setting i = min
			strcpy(i->data.artist, min->data.artist);
			strcpy(i->data.albumTitle, min->data.albumTitle);
			strcpy(i->data.songTitle, min->data.songTitle);
			strcpy(i->data.genre, min->data.genre);
			i->data.rating = min->data.rating;
			i->data.numPlayed = min->data.numPlayed;
			i->data.songLength.minutes = min->data.songLength.minutes;
			i->data.songLength.seconds = min->data.songLength.seconds;

			//setting min to temp;
			strcpy(min->data.artist, temp.artist);
			strcpy(min->data.albumTitle, temp.albumTitle);
			strcpy(min->data.songTitle, temp.songTitle);
			strcpy(min->data.genre, temp.genre);
			min->data.rating = temp.rating;
			min->data.numPlayed = temp.numPlayed;
			min->data.songLength.minutes = temp.songLength.minutes;
			min->data.songLength.seconds = temp.songLength.seconds;
		}
		i = i->next;
	}
	return head;

}

int shuffle(Node* head) {
	//finding length of doubly linked list
	NodeShuff* headShuff = NULL;
	Shuff data;
	int len = 0;
	Node* curr = head;
	while (curr != NULL) {
		len++;
		curr = curr->next;
	}
	printf("length of playlist: %d\n", len);
	int shuffLen = 0;

	//generating order
	srand(time(0));
	while (shuffLen < len) {
		int i = (data.orderInShuff = rand() % len + 1);
		//printf("\ntesting i: %d\n", i);
		//checking if current order.orderInShuff is already IN the shuffle order list
		NodeShuff* curr = headShuff;
		int ch = 1;
		while (curr != NULL) { //all this is doing is checking if its in the list
			if (curr->data.orderInShuff == i) {
				//printf("current i found in list. getting new one!\n");
				ch = 0;
			}
			curr = curr->next;
		}
		if (ch) {
			//printf("inserting node!: %d\n", data.orderInShuff);
			insertShuff(&headShuff, &data);
			shuffLen++;
		}
	}


	//printing out new shuffle order now that we have generated a full new linked list of all the new orders! :D
	NodeShuff* currShuff = headShuff;
	printf("order of songs: ");
	while (currShuff != NULL) {
		printf("%d,", currShuff->data.orderInShuff);
		currShuff = currShuff->next;
	}
	system("pause");


	//Now that we have the song order, lets play then in a shuffled manner!
	//how the fuck do i do that though ;-; TEARS AGH
	currShuff = headShuff;
	int i;
	printf("shuffled songs:\n");
	while (currShuff != NULL) {
		//iterate through the SHUFF list, then iterate through the RECORD list and find the corresponding song to that order.
		int songNUM = currShuff->data.orderInShuff;
		curr = head;
		i = 1;
		while (i != songNUM) {
			curr = curr->next;
			i++;
		}
		//now that we have reached the corresponding part of the RECORDS list, we print it out!
		printf("[%d] %s\n", i, curr->data.songTitle);
		currShuff = currShuff->next;
	}
	system("pause");
}