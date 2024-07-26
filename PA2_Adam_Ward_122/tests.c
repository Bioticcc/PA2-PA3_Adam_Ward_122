#include "Header.h"


char* addT(Node* headT) {
	int clear;
	//while ((clear = getchar()) != '\n' && clear != EOF);
	Record newRec;
	char songLenMin[10];
	char songLenSec[10];
	char rating[10];
	char numPlayed[10];
	printf("|----New Song Info---->\n");
	printf("|Artist: Perry, Katy\n");
	//getStr(newRec.artist, 50);
	printf("|Song: Chained to the Rhythm\n");
	//getStr(newRec.songTitle, 50);
	printf("|Album: Witness\n");
	//getStr(newRec.albumTitle, 50);
	printf("|Genre: pop\n");
	//getStr(newRec.genre, 50);
	printf("|Song Length MINUTES: 4:36\n");
	//getStr(songLenMin, 10);
	//newRec.songLength.minutes = atoi(songLenMin);
	//printf("|Song Length SECONDS: ");
	//getStr(songLenSec, 10);
	//newRec.songLength.seconds = atoi(songLenSec);
	printf("|Rating: 6\n");
	//getStr(rating, 50);
	//newRec.rating = atoi(rating);
	printf("|Num Played: -1\n");
	//getStr(numPlayed, 50);
	//newRec.numPlayed = atoi(numPlayed);
	/*
	printf("|--Entering into playlist-->\n");
	printf("|Artist: %s\n", newRec.artist);
	printf("|Album: %s\n", newRec.albumTitle);
	printf("|Song: %s\n", newRec.songTitle);
	printf("|Genre: %s\n", newRec.genre);
	printf("|Song Length: %d:", newRec.songLength.minutes);
	printf("%d\n", newRec.songLength.seconds);
	printf("|Num Played: %d\n", newRec.numPlayed);
	printf("|Rating: %d\n", newRec.rating);
	*/

	strcpy(newRec.albumTitle, "Witness");
	strcpy(newRec.artist, "Perry, Katy");
	strcpy(newRec.genre, "pop");
	newRec.numPlayed = -1;
	newRec.rating = 6;
	newRec.songLength.minutes = 4;
	newRec.songLength.seconds = 36;
	strcpy(newRec.songTitle, "Chained to the Rhythm");

	insert(&headT, &newRec);
	//system("pause");
	return headT;
}

void editT(Node* headT) {
	headT->data.rating = 5;
	headT->data.numPlayed = 3;
}

void displayT(Node* headT) {
	printf("\nDISPLAYING SONGS:\n");
	printf("|-------PLAYLIST------>\n");
	int track = 1;
	Node* curr = headT;
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
	system("cls");
}

char* deleteT(Node* head) {
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
	strcpy(song, "Chained to the Rhythm");
	printf("Chosen Song: %s\n", song);

	if (checka == 1) {
		int z = 0;
		//only one song in list, so deletes list as a whole? i guess?
		printf("\nWARNING: There is only ONE song in your playlist. Deleting will delete entire playlist.\n");
		printf("(1) continue\n(0) go back! save yourself!\nDecision: 1");
		z = 1;
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
}

char* addT3(Node* headT) {

	Record newRec;
	strcpy(newRec.albumTitle, "Witness");
	strcpy(newRec.artist, "Perry, Katy");
	strcpy(newRec.genre, "pop");
	newRec.numPlayed = 3;
	newRec.rating = 5;
	newRec.songLength.minutes = 4;
	newRec.songLength.seconds = 36;
	strcpy(newRec.songTitle, "Chained to the Rhythm");
	insert(&headT, &newRec);

	strcpy(newRec.albumTitle, "Bananas");
	strcpy(newRec.artist, "Minion, Grand");
	strcpy(newRec.genre, "Sauce");
	newRec.numPlayed = 69;
	newRec.rating = 2;
	newRec.songLength.minutes = 9;
	newRec.songLength.seconds = 59;
	strcpy(newRec.songTitle, "Goin Bananas for Mah-Nanas");
	insert(&headT, &newRec);

	strcpy(newRec.albumTitle, "ssentiW");
	strcpy(newRec.artist, "ytaK, yrreP");
	strcpy(newRec.genre, "pop");
	newRec.numPlayed = 3;
	newRec.rating = 5;
	newRec.songLength.minutes = 4;
	newRec.songLength.seconds = 63;
	strcpy(newRec.songTitle, "mhtyhR eht ot deniahC");
	insert(&headT, &newRec);

	//system("pause");
	return headT;
}

int shuffleT(Node* head) {
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
	//srand(time(0));
	

	//wow jesus looking back at this a few monthes later is crazy what the actual HELL Was i on (coffee and snacks) when i made this???
	int a = 2, b = 1, c = 3;
	int i = a;
	while (shuffLen < len) {

		//printf("\ntesting i: %d\n", i);
		//checking if current order.orderInShuff is already IN the shuffle order list
		NodeShuff* curr = headShuff;
		if (shuffLen == 0) {
			data.orderInShuff = a;
		}
		else if (shuffLen == 1) {
			data.orderInShuff = b;
		}
		else if (shuffLen == 2) {
			data.orderInShuff = c;
		}
		/*int ch = 1;
		while (curr != NULL) { //all this is doing is checking if its in the list
			if (curr->data.orderInShuff == i) {
				//printf("current i found in list. getting new one!\n");
				ch = 0;
				i = b;
				b = 0;
				if (!b) { i = c; };
			}
			curr = curr->next;
		}
		if (ch) {*/
			//printf("inserting node!: %d\n", data.orderInShuff);
		insertShuff(&headShuff, &data);
		shuffLen++;
		//}
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



void insertTest() {
	/*
	so im not really sure how you want us to do this, I had a few ideas
	first off, i thought i could do the various functions requiring scanf
	and user inputs to instead be seperate, reading the user inputs into a seperate .csv file,
	and letting the insert function read from that, instead of directly asking for user input.
	doing such would then allow me to make THIS function simply put those entries into the .csv file,
	and then run the insert function with the given .csv. however that would have been weird to implement,
	and could fuck with what ive currenly got actually working. If the purpose of this is to TEST my
	functions with various values, I instead figured the best way that also wouldnt fuck with my actual 
	program was to simply copy paste the entire insert function here, and just not ask for user
	values and instead give it my own. That fulfills the condition of not having args or return values,
	and I think works perfectly fine. Anywho, back to it! <3

	7/26 - coming back to this a few monthes later (was in europe sue me smh) im realizing i may have misread what it wanted me to do.
		   what I THOUGHT was meant to happen was my adding these test cases to the already existing linked list that ive been using for everything else. 
		   that woulda been hard as balls without being able to use argument or returns, so i was at a loss for words on what to do
		   aaaaand then i reread the assignment and realized NOPE these are actually supposed to be completely self suffecient off in wonderland. yippee!
	*/ 

	//insert test
	Record* dataT = NULL;
	Node* headT = NULL;
	system("cls");
	printf("RUNNING TESTS!\n");
	printf("\n\nTESTING INSERT FUNCTION:\n");
	headT = addT(headT);
	//displying newly created song list with given song test:
	displayT(headT);


	//delete test
	//first gotta change the currently inserted song cause the assignment demand it ig idk tis a cruel world
	editT(headT);
	printf("TESTING DELETE FUNCTION:\n");
	headT = deleteT(headT);
	printf("\nDELETING....\n");
	displayT(headT);

	//shuffle test
	//gotta add like 3 songs with this weird method i HATE testcases like this so much >.> if only it could accept arguments my life would be glorious
	headT = addT3(headT);
	printf("TESTING SHUFFLE FUNCTION:\n");
	printf("PRESHUFFLED PLAYLIST:\n");
	displayT(headT);
	//now then, the shuffler:
	//hey presto, i think this works but i can clean it up if needed (literally never opening this project again until I have to turn it in lmao)
	shuffleT(headT);
}
