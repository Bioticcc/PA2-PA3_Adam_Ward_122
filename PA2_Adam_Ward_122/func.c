#include "Header.h"
//opening file
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
	printf("|-------------------------------------------------------|\n");
	printf("|---Now then, where to? (#)--->: ");
	//printf("%d",_getch());
	scanf("%d", &choice);
	/*
	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7 && choice != 8 && choice != 9 && choice != 10 && choice != 11) {
		printf("|---Choose a menu option, please! (#)--->: ");
		scanf("%d", &choice);
	}*/
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

		//now gotta insert the aqquired record file into the linked list.
		/*
		printf("|---------TRACK-[%d]--------->\n",track);
		track++;

		printf("|%s\n", head->data.artist);
		printf("|%s\n", head->data.albumTitle);
		printf("|%s\n", head->data.songTitle);
		printf("|%s\n", head->data.genre);
		printf("|%d:", head->data.songLength.minutes);
		printf("%d\n", head->data.songLength.seconds);
		printf("|%d\n", head->data.numPlayed);
		printf("|%d\n", head->data.rating);
		*/
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
		fprintf(output, "%s,", curr->data.artist);
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
	int x = 0;
	printf("|--------DISPLAY-------->\n");
	printf("|(1) view all tracks\n");
	printf("|(2) view tracks by (artist)\n");
	printf("|(1/2): ");
	scanf("%d", &x);
	
	if (x == 1) {
		system("cls");
		printf("|-------PLAYLIST------|\n");
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
		printf("|----Currently Loaded Artists----|\n");
		Node* curr = head;
		while (curr != NULL) {
			printf("|%s\n", curr->data.artist);
			curr = curr->next;
		}

		//clearing input buffer
		int clear;
		while ((clear = getchar()) != '\n' && clear != EOF);

		char artist[50];
		printf("\n|Artist for lookup (PLEASE ENTER NAME EXACTLY AS SHOWN): ");
		fgets(artist, 50, stdin);
		//printf("\nArtist: %s\n", artist);
		//getting rid of newline in artist:
		int size = strlen(artist);
		if (size > 0 && artist[size - 1] == '\n') {
			//replaces newline with null char ;3
			artist[size - 1] = '\0';
		}

		printf("\n|Displaying songs by: %s\n", artist);
	
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
	//clearing input buffer
	int clear;
	while ((clear = getchar()) != '\n' && clear != EOF);


	printf("|----Currently Loaded Songs----|\n");
	Node* curr = head;
	while (curr != NULL) {
		printf("|%s(%d:%d) - %s\n", curr->data.songTitle, curr->data.songLength.minutes, curr->data.songLength.seconds, curr->data.artist);
		curr = curr->next;
	}

	char artist[50];
	printf("\n");
	printf("|Enter ARTIST to edit: ");
	fgets(artist, 50, stdin);
	int size = strlen(artist);
	if (size > 0 && artist[size - 1] == '\n') {
		//replaces newline with null char ;3
		artist[size - 1] = '\0';
	}

	curr = head;
	int i = 0;
	while (curr != NULL) {
		if (strcmp(curr->data.artist, artist) == 0) {
			i++;
		}
		curr = curr->next;
	}
	char song[50];
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
		fgets(song, 50, stdin);
		int size = strlen(song);
		if (size > 0 && song[size - 1] == '\n') {
			//replaces newline with null char ;3
			song[size - 1] = '\0';
		}
		printf("\nChosen Song: %s\n", song);

		curr = head;
		while (curr != NULL) {
			if (strcmp(curr->data.songTitle, song) == 0) {
				system("cls");
				printf("|----Edit Attributes of Selected Song----|\n");
				printf("|(1)Artist: %s\n", curr->data.artist);
				printf("|(2)Song: %s\n", curr->data.songTitle);
				printf("|(3)Album: %s\n", curr->data.albumTitle);
				printf("|(4)Genre: %s\n", curr->data.genre);
				printf("|(5)Length: %d:%d\n", curr->data.songLength.minutes, curr->data.songLength.seconds);
				printf("|(6)Played: %d\n", curr->data.numPlayed);
				printf("|(7)Rating: %d\n", curr->data.rating);

				system("pause");
			}
			curr = curr->next;
		}
	}

	

	system("pause");
}