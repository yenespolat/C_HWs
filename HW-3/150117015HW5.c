/*
	Yasin Enes POLAT 150117015
	This program takes song names and durations from txt file or user and lists
	them in several types like alphabetical, chronological, duration-time and random order.
	You can add and delete a song from lists and print list to consol display or another txt file.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct song {
	char songName[25];
	int duration;
	struct song *chrono_next;
	struct song *alpha_next;
	struct song *duration_next;
	struct song *random_next;
}Song, *SongPtr;
	
	int total = 0;
	unsigned int duration;
	char songName[25];
	char toTokenize[50];
	
	SongPtr alphaStartPtr 		= NULL;
	SongPtr durationStartPtr 	= NULL;
	SongPtr chronoStartPtr 		= NULL;
	SongPtr randomStartPtr 		= NULL;

void insertNode (SongPtr *alphaStartPtr, SongPtr *durationStartPtr, SongPtr *randomStartPtr, SongPtr *chronoStartPtr, char name[25], int duration);
void tokenize (char toT[], char name[], int *duration);
void printList(int toOutput);
void deleteNode(char *name);
void shuffle();
void shuffleEven();

void menu() {
	printf("Enter your choice:\n\t1 to insert a song into the list.\n\t");
	printf("2 to delete  a song from the list.\n\t3 to print the songs in the list.\n\t");
	printf("4 to print the songs to an output file.\n\t5 to end.\n?");
	
	int choice;
	scanf("%d", &choice);
	char dust[2];
	char forDelete[25];
	
	switch(choice) {
		case 1: //Adds a new song to the lists.
			puts("\nEnter a song name with duration:");
			gets(dust);
			gets(toTokenize);
			tokenize(toTokenize, songName, &duration);
			insertNode(&alphaStartPtr, &durationStartPtr, &randomStartPtr, &chronoStartPtr, songName, duration);
			printf("%s is added to playlists.\n\n", songName);
			break;
		case 2: //Deletes the song from lists if exists.
			puts("Enter a song name:");
			gets(dust);
			gets(forDelete);
			deleteNode(forDelete);
			break;
		case 3: //Prints the lists to the consol display.
			gets(dust);
			if (total % 2 == 1)
				shuffle();
			else
				shuffleEven();
			printList(0);
			break;
		case 4: //Prints the lists to the .txt file.
			if (total % 2 == 1)
				shuffle();
			else
				shuffleEven();
			printList(1);
			break;
		case 5: //Terminates the program.
			exit(29);
		default:
			puts("Wrong input for choice!");
			gets(dust);
			menu();
			break;
		
	}
	
	if (choice != 5) //Provides the program to continiously prints the menu to the consol display.
		menu();
	else
		return;
	
}

int main () {
	
	
	FILE *file;
	if ((file = fopen("songs.txt", "r")) == NULL) {
		puts("File could not be opened");
	}
	else {
		
		while (!feof(file)) { //Creates the lists, takes inputs from the .txt file.
			fgets(toTokenize, 50, file);
			tokenize(toTokenize, songName, &duration);
			insertNode(&alphaStartPtr, &durationStartPtr, &randomStartPtr, &chronoStartPtr, songName, duration);
		}
	}
	
	fclose(file);
	
	if (total % 2 == 1)
		shuffle();
	else
		shuffleEven();
	printList(0);
	
	menu();
	
	return 0;
}

void insertNode (SongPtr *alphaStartPtr, SongPtr *durationStartPtr, SongPtr *randomStartPtr, SongPtr *chronoStartPtr, char name[25], int duration) {
	SongPtr newPtr = malloc(sizeof(Song));
	
	if (newPtr == NULL) {
		return;
	}
	
	strcpy(newPtr->songName, name);
	newPtr->duration = duration;
	
	//Alpha part
	SongPtr alpha_previousPtr = NULL;
	SongPtr alpha_currentPtr = *alphaStartPtr;
	
	int cmp_a;
	
	if (alpha_currentPtr != NULL)
		cmp_a = strcmp(alpha_currentPtr->songName, name);
	
	while (alpha_currentPtr != NULL && cmp_a < 0) { //Finds the corresponding place.
		alpha_previousPtr = alpha_currentPtr;
		alpha_currentPtr = alpha_currentPtr->alpha_next;
		if (alpha_currentPtr != NULL)
			cmp_a = strcmp(alpha_currentPtr->songName, name);
	}
	
	
	if (alpha_previousPtr == NULL) {
		newPtr->alpha_next = *alphaStartPtr;
		*alphaStartPtr = newPtr;
	
	}
	else {
		alpha_previousPtr->alpha_next = newPtr;
		newPtr->alpha_next = alpha_currentPtr;
	}
	
	//Duration part
	SongPtr duration_previousPtr = NULL;
	SongPtr duration_currentPtr = *durationStartPtr;
	
	int cmp_d;
	
	if (duration_currentPtr != NULL)
		cmp_d = duration_currentPtr->duration;
	
	while (duration_currentPtr != NULL && cmp_d < duration) { //Finds the corresponding place.
		duration_previousPtr = duration_currentPtr;
		duration_currentPtr = duration_currentPtr->duration_next;
		if (duration_currentPtr != NULL)
			cmp_d = duration_currentPtr->duration;
	}
	
	if (duration_previousPtr == NULL) {
		newPtr->duration_next = *durationStartPtr;
		*durationStartPtr = newPtr;
	
	}
	else {
		duration_previousPtr->duration_next = newPtr;
		newPtr->duration_next = duration_currentPtr;
	}
	
	//Chrono part
	
	if (chronoStartPtr == NULL) {
		*chronoStartPtr = newPtr;
	}
	else {
		newPtr->chrono_next = *chronoStartPtr;
		*chronoStartPtr = newPtr;
	}
	
	//Random part
	
	if (randomStartPtr == NULL) { //Program first adds the songs to random list same as chronological order, then shuffles it.
		*randomStartPtr = newPtr;
	}
	else {
		newPtr->random_next = *randomStartPtr;
		*randomStartPtr = newPtr;
	}
	
	total++;	
}

void shuffle () { //Shuffles the random list if total number of songs is odd number.
	SongPtr move = randomStartPtr;
	SongPtr previous_move = NULL;
	SongPtr dest = randomStartPtr;
	SongPtr previous_dest = NULL;
	SongPtr temp = NULL;
	SongPtr temp2 = NULL;
	SongPtr temp_i = NULL;
	
	srand(time(NULL));
	int i = 0, j;
	for (; i < total / 2 + 1; i++) { //Shuffles the first half with second half.
		temp_i = move->random_next;
		int index = total / 2 + rand() % (total / 2) + 1;
		if (i == total / 2) {
			while (index == total / 2 + 1)
				index = total / 2 + rand() % (total / 2) + 1;
		}
		for (j = 0; j < index; j++) {
			previous_dest = dest;
			dest = dest->random_next;
			temp2 = previous_dest->random_next->random_next;
		}
		
		temp = move->random_next;
		
		if (previous_move != NULL) {
			previous_dest->random_next = move;
			previous_move->random_next = dest;
			dest->random_next = temp;
			move->random_next = temp2;
		}
		else {
			previous_dest->random_next = move;
			move->random_next = temp2;
			dest->random_next = temp;
			randomStartPtr = dest;
		}
		move = temp_i;
		previous_move = dest;
		dest = randomStartPtr;
		previous_dest = NULL;
	}
	
	
	
}

void shuffleEven () { //Shuffles the random list if total number of songs is even number.
	SongPtr move = randomStartPtr;
	SongPtr previous_move = NULL;
	SongPtr dest = randomStartPtr;
	SongPtr previous_dest = NULL;
	SongPtr temp = NULL;
	SongPtr temp2 = NULL;
	SongPtr temp_i = NULL;
	
	srand(time(NULL));
	int i = 0, j;
	for (; i < total / 2 - 1; i++) { //Shuffles the first half of list with second half.
		temp_i = move->random_next;
		int index = total / 2 + rand() % (total / 2);
		if (i == total / 2) {
			while (index == total / 2 + 1 || index == total / 2) //If (index - i) is 1, program will face with infinite loop.
				index = total / 2 + rand() % (total / 2) + 1;
		}
		for (j = 0; j < index; j++) {
			previous_dest = dest;
			dest = dest->random_next;
			temp2 = previous_dest->random_next->random_next;
		}
		
		temp = move->random_next;
		
		if (previous_move != NULL) {
			previous_dest->random_next = move;
			previous_move->random_next = dest;
			dest->random_next = temp;
			move->random_next = temp2;
		}
		else {
			previous_dest->random_next = move;
			move->random_next = temp2;
			dest->random_next = temp;
			randomStartPtr = dest;
		}
		move = temp_i;
		previous_move = dest;
		dest = randomStartPtr;
		previous_dest = NULL;
	}
	
	
	
}

void deleteNode(char *name) { //This function finds nodes one by one in each list which has same name as input name, then changes the connection links, at the end frees the memory of deleted nodes.
	SongPtr tempPtr;
	//alpha
	if (!strcmp(name, alphaStartPtr->songName)) {
		tempPtr = alphaStartPtr;
		alphaStartPtr = alphaStartPtr->alpha_next;
	}
	else {
		SongPtr currentPtr = alphaStartPtr->alpha_next;
		SongPtr previousPtr = alphaStartPtr;
		
		while (currentPtr != NULL && strcmp(name, currentPtr->songName)) { 
			previousPtr = currentPtr;
			currentPtr = currentPtr->alpha_next;
		}
		tempPtr = currentPtr;
		
		if (currentPtr != NULL) { 
			tempPtr = currentPtr;
			previousPtr->alpha_next = currentPtr->alpha_next;
		}
		else {	//If given song name does not exists in alphabetical list;
			printf("There is no song named \"%s\" in lists!\n\n", name);
			return;
		}
	}
	
	//duration
	if (tempPtr->duration == durationStartPtr->duration) {
		durationStartPtr = durationStartPtr->duration_next;
	}
	else {
		SongPtr currentPtr = durationStartPtr->duration_next;
		SongPtr previousPtr = durationStartPtr;
		
		while (currentPtr != NULL && tempPtr->duration != currentPtr->duration) { 
			previousPtr = currentPtr;
			currentPtr = currentPtr->duration_next;
		}
		
		if (currentPtr != NULL) { 
			previousPtr->duration_next = currentPtr->duration_next;
		}
	}
	
	//chrono
	if (!strcmp(name, chronoStartPtr->songName)) {
		chronoStartPtr = chronoStartPtr->chrono_next;
	}
	else {
		SongPtr currentPtr = chronoStartPtr->chrono_next;
		SongPtr previousPtr = chronoStartPtr;
		
		while (currentPtr != NULL && strcmp(name, currentPtr->songName)) { 
			previousPtr = currentPtr;
			currentPtr = currentPtr->chrono_next;
		}
		
		if (currentPtr != NULL) { 
			previousPtr->chrono_next = currentPtr->chrono_next;
		}
	}
	
	//random
	if (!strcmp(name, randomStartPtr->songName)) {
		randomStartPtr = randomStartPtr->random_next;
	}
	else {
		SongPtr currentPtr = randomStartPtr->random_next;
		SongPtr previousPtr = randomStartPtr;
		
		while (currentPtr != NULL && strcmp(name, currentPtr->songName)) { 
			previousPtr = currentPtr;
			currentPtr = currentPtr->random_next;
		}
		
		if (currentPtr != NULL) { 
			previousPtr->random_next = currentPtr->random_next;	
		}
	}
	free(tempPtr);
	total--;
	printf("The song \"%s\" is deleted from lists!\n\n", name); //If node successfully deleted.
}

void tokenize (char *toT, char *name, int *duration) { //Tokenizes the input string from songs.txt or user.
	strcpy(name, strtok(toT, "\t"));
	char durationStr[10];
	strcpy(durationStr, strtok(NULL, "\t"));
	int minutes = atoi(strtok(durationStr, ":"));
	int seconds = atoi(strtok(NULL, ":"));
	*duration = minutes * 60 + seconds;		
}

void printList(int toOutput) { //Prints out the each list one by one, if toOutput is 0, function prints the list to the consol, otherwise function prints the lists to .txt file.
	int i = 1;
	if (!toOutput) {
		puts("\nThe list in alphabetical order: ");
		SongPtr forPrint = alphaStartPtr;
		while (forPrint != NULL) {
			printf("\t%d) %-25s0%d:%d\n", i, forPrint->songName, forPrint->duration / 60, forPrint->duration % 60);
			forPrint = forPrint->alpha_next;
			i++;	
		}
		i = 1;
		puts("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
		
		puts("\nThe list in duration-time order: ");
		SongPtr forPrint2 = durationStartPtr;
		while (forPrint2 != NULL) {
			printf("\t%d) %-25s0%d:%d\n", i, forPrint2->songName, forPrint2->duration / 60, forPrint2->duration % 60);
			forPrint2 = forPrint2->duration_next;
			i++;	
		}
		i = 1;
		puts("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
		
		puts("\nThe list in chronological order: ");
		SongPtr forPrint3 = chronoStartPtr;
		while (forPrint3 != NULL) {
			printf("\t%d) %-25s0%d:%d\n", i, forPrint3->songName, forPrint3->duration / 60, forPrint3->duration % 60);
			forPrint3 = forPrint3->chrono_next;
			i++;
		}
		i = 1;
		puts("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
		
		puts("\nThe list in random order: ");
		SongPtr forPrint4 = randomStartPtr;
		while (forPrint4 != NULL) {
			printf("\t%d) %-25s0%d:%d\n", i, forPrint4->songName, forPrint4->duration / 60, forPrint4->duration % 60);
			forPrint4 = forPrint4->random_next;
			i++;
		}
		i = 1;
		puts("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
		
	}
	else {
		FILE *out;
		if ((out = fopen("playlist.txt", "w")) == NULL) {
			puts("File could not be opened");
		}
		else { //If toOutput is not 0.
			fputs("\nThe list in alphabetical order: \n", out);
			SongPtr forPrint = alphaStartPtr;
			while (forPrint != NULL) {
				fprintf(out, "\t%d) %-25s0%d:%d\n", i, forPrint->songName, forPrint->duration / 60, forPrint->duration % 60);
				forPrint = forPrint->alpha_next;	
				i++;
			}
			i = 1;
			fputs("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_", out);
		
			fputs("\nThe list in duration-time order: \n", out);
			SongPtr forPrint2 = durationStartPtr;
			while (forPrint2 != NULL) {
				fprintf(out, "\t%d) %-25s0%d:%d\n", i, forPrint2->songName, forPrint2->duration / 60, forPrint2->duration % 60);
				forPrint2 = forPrint2->duration_next;
				i++;	
			}
			i = 1;
			fputs("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_", out);
			
			fputs("\nThe list in chronological order: \n", out);
			SongPtr forPrint3 = chronoStartPtr;
			while (forPrint3 != NULL) {
				fprintf(out, "\t%d) %-25s0%d:%d\n", i, forPrint3->songName, forPrint3->duration / 60, forPrint3->duration % 60);
				forPrint3 = forPrint3->chrono_next;	
				i++;
			}
			i = 1;
			fputs("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_", out);
			
			fputs("\nThe list in random order: \n", out);
			SongPtr forPrint4 = randomStartPtr;
		
			int i = total;
			while (forPrint4 != NULL) {
				fprintf(out, "\t%d) %-25s0%d:%d\n", i, forPrint4->songName, forPrint4->duration / 60, forPrint4->duration % 60);
				forPrint4 = forPrint4->random_next;
				i++;
			}
			i = 1;
			fputs("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_", out);
			}
		fclose(out);
		puts("Playlist is successfully printed.");
	}
}
