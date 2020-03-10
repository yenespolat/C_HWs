/*
150117015 Yasin Enes Polat
This program calculates the shortest path from begining metro station to end.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Math.h>
#define SIZE 10

	typedef struct MetroStation {
		char name[20];
		int x;
		int y;
	} MetroStation;
	
	typedef struct MetroLine {
		char color[20];
		MetroStation MetroStations[SIZE];
	} MetroLine;
	
	typedef struct MetroSystem {
		char name[20];
		MetroLine MetroLines[SIZE];
	} MetroSystem;
	
	
int equals (MetroStation s1, MetroStation s2);

void addStation (MetroLine *line, MetroStation st);

int hasStation (MetroLine line, MetroStation st);

MetroStation getFirstStop (MetroLine line);

MetroStation getPriorStop (MetroLine line, MetroStation st);

MetroStation getNextStop (MetroLine line, MetroStation st);

void addLine (MetroSystem *system, MetroLine line);

void printLine (MetroLine line);

void printPath (MetroStation *stations);

double getDistanceTravelled (MetroStation *path);

MetroStation findNearestStation (MetroSystem system, double x, double y);

void getNeighboringStations (MetroSystem system, MetroStation station, MetroStation *neighboringStations);

void findPath (MetroStation start, MetroStation finish, MetroStation *path);

void recursiveFindPath (MetroStation start, MetroStation finish, MetroStation *partialPath, MetroStation *bestPath);

MetroStation findNearestStation (MetroSystem system, double x, double y);
	

//Declare a MetroSystem with the name of istanbul and an empty content.
MetroSystem istanbul = {"istanbul", '\0'};

int main()
{
	int i;
	double myX=9, myY=4; 
	double goalX=48, goalY=22;
	
	// define 3 metro lines, 9 metro stations, and an empty myPath
	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};
	
	strcpy(red.color, "red"); 
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");

	
	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;
	
	//Add several metro stations to the given metro lines.
	addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);
	
	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);
	
	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);
	
	// Add red, blue, green metro lines to the Istanbul metro system.
	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);
	
	// print the content of the red, blue, green metro lines
	printLine(red); 
	printLine(blue);
	printLine(green);
		
		
	// find the nearest stations to the current and target locations
	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);
	
	printf("\n");
	
	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);
	
	// if the nearest current and target stations are the same, then print a message and exit.
	if(equals(nearMe, nearGoal)){
		printf("It is better to walk!\n");
		return 0;
	}
	
	// Calculate and print the myPath with the minimum distance travelled from start to target stations.
	findPath(nearMe, nearGoal, myPath);
	
	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
	}
	
	return 0;

}

int equals (MetroStation s1, MetroStation s2) { //this function checks if the given metro stations same or not.
	
	if (!strcmp(s1.name, s2.name))
		return 1;
	
	return 0;
}

void addStation (MetroLine *line, MetroStation st) { //this adds given station to given line.
	int i = 0;
	while (line->MetroStations[i].name[0] != '\0') {
		i++;
	}
	line->MetroStations[i] = st;
}

int hasStation (MetroLine line, MetroStation st) { //this function checks if given line contains the given station or not.
	int i;
	for (i = 0; strlen(line.MetroStations[i].name) != 0; i++) {
		if (strcmp(line.MetroStations[i].name, st.name))
			return 1;
	}
	return 0;
}

MetroStation getFirstStop (MetroLine line) { //this function returns the first stop of given line
		return line.MetroStations[0];
}

MetroStation getPriorStop (MetroLine line, MetroStation st) { //this function returns the station just before the given station on given line.
	MetroStation mS;
	int i = 0;
	
	while (!strcmp(line.MetroStations[i].name, st.name))	i++;
	
	if (i != 0) {
		mS = line.MetroStations[i-1];
		return mS;
	}
	
	return mS;	
}

MetroStation getNextStop (MetroLine line, MetroStation st) { //this function returns the station just after the given station on given line.
	MetroStation mS;
	int i = 0;
	
	while (!strcmp(line.MetroStations[i].name, st.name))	i++;
	
	if (i != SIZE - 1) {
		mS = line.MetroStations[i+1];
		return mS;
	}
	
	return mS;
}

void addLine (MetroSystem *system, MetroLine line) { //adds new line to given metro system.
	int i = 0; 
	while (strlen(system->MetroLines[i].color) != 0)	i++;
	system->MetroLines[i] = line;
}

void printLine (MetroLine line) { //prints out the stations of given line.
	int i;
	printf("Metroline %s:   ", line.color);
	for (i = 0; i < 10; i++) {
		if (line.MetroStations[i].name[0] != '\0') {
			printf("%s ", line.MetroStations[i].name);
		}
		else
			continue;
	}
	puts("");
}

void printPath (MetroStation *stations) { //prints the stations on given path.
	int i;
	for (i = 0; strlen(stations[i].name) != 0; i++) {
			printf("%d. %s\n", i+1, stations[i].name);
	}
}

double getDistanceTravelled (MetroStation *path) { //returns the total distance between each stations on given path.
	double total = 0;
	int i, x, y;
	
	x = path[0].x;
	y = path[0].y;
	
	for (i = 1; i < sizeof(path); i++) {
		if (path[i].name == NULL) {
			if (i == 1) 
				return 0;
			else
				break;
		}
		else {
			total += sqrt(pow(path[i].x - x, 2) + pow(path[i].y - y, 2));
			x = path[i].x;
			y = path[i].y;
		}
	}
	
	return total;
}

MetroStation findNearestStation (MetroSystem system, double x, double y) { //finds and returns the closest metro station base on given x and y values.
	double distance, temp, nx, ny, pow1, pow2;
	int i, j;
	MetroStation next, nearest;
	
	nearest = getFirstStop(system.MetroLines[0]);
	distance = sqrt(pow(getFirstStop(system.MetroLines[0]).x - x, 2) + pow(getFirstStop(system.MetroLines[0]).y - y, 2));
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			next = system.MetroLines[i].MetroStations[j];
			nx = next.x; nx -= x;
			ny = next.y; ny -= y;
			pow1 = nx * nx;
			pow2 = ny * ny;
			temp = pow1 + pow2; 
			temp = sqrt(temp);
			if (next.name != NULL) { 
				if (temp < distance) { //if current distance smaller than previous one, update previous one to new distance.
					distance = temp;
					nearest = next;
				}
			}
			else
				break;
		}
	}
	return nearest;
}

void getNeighboringStations (MetroSystem system, MetroStation station, MetroStation *neighboringStations) { //updates the neighboringStations with the stations which are the previous or next stations of given station on each line.
	int i, j, index = 0;
	
	for (i = 0; strlen(system.MetroLines[i].color) != 0; i++) {
		for (j = 0; strlen(system.MetroLines[i].MetroStations[j].name) != 0; j++) {
			if (!strcmp(station.name, system.MetroLines[i].MetroStations[j].name)) {
				if (!contains(neighboringStations, system.MetroLines[i].MetroStations[j-1].name) && !contains(neighboringStations, system.MetroLines[i].MetroStations[j+1].name)) {
					if (j > 0) {
						neighboringStations[index++] = system.MetroLines[i].MetroStations[j - 1];
						neighboringStations[index++] = system.MetroLines[i].MetroStations[j + 1];
					}
					else {
						neighboringStations[index++] = system.MetroLines[i].MetroStations[j + 1];
					}
						
				}
			}
		}
	}
}

int contains (MetroStation *arr, MetroStation st) { //if array contains the given station st, function returns 1, otherwise 0.
	int i;
	for (i = 0; i < strlen(arr[i].name) != 0; i++) {
		if (!strcmp(arr[i].name, st.name)) {
			return 1;
		}
			
	}
	return 0;
}

void findPath (MetroStation start, MetroStation finish, MetroStation *path) { //finds the path with the help of recursiveFindPath function.
	MetroStation partialPath[SIZE] = {'\0'};
	
	
	recursiveFindPath(start, finish, path, partialPath);
}

void recursiveFindPath (MetroStation start, MetroStation finish, MetroStation *partialPath, MetroStation *bestPath) { //this function does not works properly.
	int i;
	double distance = 10000;
	
	for (i = 0; i < SIZE; i++) {
		if (equals(partialPath[i], start))
			return;
	}
	
	if (equals(start, finish)) {
		for (i = 0; i < SIZE; i++) {
			if (strlen(partialPath[i].name) < 5){
				partialPath[i] = finish;
				break;
			}
		}
		for (i = 0; strlen(partialPath[i].name) != 0; i++) {
			strcpy(bestPath[i].name, partialPath[i].name);
			bestPath[i].x = partialPath[i].x;
			bestPath[i].y = partialPath[i].y;
		}
	//	bestPath = partialPath;
		return;
	}
	
	
	
	MetroStation neighbors[SIZE] = {'\0'};
	getNeighboringStations(istanbul, start, neighbors);	
	
	MetroStation duplicatePath[SIZE] = {'\0'};
	for (i = 0; strlen(partialPath[i].name) != 0; i++) {
		strcpy(duplicatePath[i].name, partialPath[i].name);
		duplicatePath[i].x = partialPath[i].x;
		duplicatePath[i].y = partialPath[i].y;
	}
	
	for (i = 0; i < SIZE; i++) {
			if (strlen(duplicatePath[i].name) < 5){
				duplicatePath[i] = start;
				break;
			}
		}
	
	for (i = 1; strlen(neighbors[i].name) != 0; i++) {
		if (!contains(duplicatePath, neighbors[i])) {
			recursiveFindPath(neighbors[i], finish, duplicatePath, partialPath);
		}	
		else {
			recursiveFindPath(neighbors[i+1], finish, duplicatePath, partialPath);
			i++;
		}
				
	}	
		
	for (i = 0; strlen(duplicatePath[i].name) != 0; i++) {
		strcpy(partialPath[i].name, duplicatePath[i].name);
		partialPath[i].x = duplicatePath[i].x;
		partialPath[i].y = duplicatePath[i].y;
	}
	
	if (strlen(partialPath[0].name) != 0){
		if (getDistanceTravelled(partialPath) < distance) {
				*bestPath = *partialPath;
		}	
	}
}























