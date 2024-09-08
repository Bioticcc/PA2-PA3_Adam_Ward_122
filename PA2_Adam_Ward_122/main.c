#include "Header.h"

//NOTE ABOUT musicPlayListCOPY.csv: So when you run store, it overwrites musicplaylist, and on the off chance you misclick well now its gone forever, cause its editing the 
//same file back n forth (as dictated by assignment) so i just have the COPY.csv here so if ya misclick somethin when testing you can put the set of songs given by the assignment
//back into place so you can continue

//4, 5, 7, 10, 12

int main(void) {
	//declarations
	Record* data = NULL; 
	Node* head = NULL;
	FILE* input = NULL;
	FILE* output = NULL;
	while (1) {
		system("cls");
		//printf("head: %s\n", head);

		int c = menu();
		switch (c) {
		case 1:
			//load
			system("cls");
			input = openFR("musicPlayList.csv");
			head = load(input);
			fclose(input);
			system("pause");
			break;
		case 2:
			//store
			system("cls");
			output = openFW("musicPlaylist.csv");
			store(output, head);
			fclose(output);
			system("pause");
			break;
		case 3:
			//display
			system("cls");
			display(head);
			break;
		case 4:
			pa3Warning();
			/*insert
			system("cls");
			head = add(head);
			*/
			break;
		case 5:
			pa3Warning();
			/*delete
			system("cls");
			head = delete(head);
			*/
			break;
		case 6:
			//edit
			system("cls");
			edit(head);
			break;
		case 7:
			pa3Warning();
			/*sort
			system("cls");
			head = sort(head);
			*/
			break;
		case 8:
			//rate
			system("cls");
			rate(head);
			break;
		case 9:
			//play
			system("cls");
			play(head);
			break;
		case 10:
			pa3Warning();
			/*shuffle
			system("cls");
			shuffle(head);
			*/
			break;
		case 11:
			output = openFW("musicPlaylist.csv");
			store(output, head);
			if (input != NULL && output != NULL) {
				fclose(input);
				fclose(output);
				exit(1);
			}
			else {
				exit(0);
			}
			break;
		case 12:
			pa3Warning();
			//run tests (PLEASE ONLY DO THIS AFTER USING OPTIONS 1 AND 2 THEY ARE REQUIRED.) 
			//run tests (NEVERMIND I WAS MISREADING THE ASSIGNMENT LMAO YOU CAN DO THIS SEPERATELY)
			//insertTest();
			break;
	
		default:
			ErrorPanic();
			//clear();
		}


	}
}