#include "Header.h"

int main(void) {
	//declarations
	Record* data = NULL; 
	Node* head = NULL;
	FILE* input = NULL;
	FILE* output = NULL;
	while (1) {	
		system("cls");
		printf("head: %s\n", head);

		int c = menu();
		switch (c) {
		case 1:
			//load
			system("cls");
			input = openFR("musicPlayListCOPY.csv");
			head = load(input);
			system("pause");
			break;
		case 2:
			//store
			system("cls");
			output = openFW("musicPlaylist.csv");
			store(output, head);

			system("pause");
			break;
		case 3:
			//display
			system("cls");
			display(head);
			break;
		case 4:
			//insert
			system("cls");
			head = add(head);
			break;
		case 5:
			//delete
			system("cls");
			head = delete(head);
			break;
		case 6:
			//edit
			system("cls");
			edit(head);
			break;
		case 7:
			//sort
			system("cls");
			head = sort(head);
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
		case 11:
			if (input!=NULL && output != NULL) {
				fclose(input);
				fclose(output);
				exit(1);
			}
			else {
				exit(0);
			}
			break;

		default:
			ErrorPanic;
			break;
		}
	}
	
	
}