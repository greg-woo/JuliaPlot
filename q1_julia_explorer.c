
/*
Created by: GREG WOO
Program: Produce Julia plots interactively
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// method to make sure the file contains the both #A# and #B#
int fileSearcher(char *fileName, char *str, char *argv[]) {


  FILE* fp = fopen(fileName, "r");
  char temp[600];
  int lineNumber = 0;
  int matchFound = 0;
  int tempInt = 0;

  // Exits the program if there is a problem with the file
  if(fp == NULL) {

    printf("Error: bad file\n");
    exit(-1);

  }

  // while loop to check if #A# and #B# appear
  while (fgets(temp, 600, fp) != NULL) {

    if((strstr(temp, str)) != NULL) {
      matchFound ++;
      tempInt = lineNumber;
    }
    lineNumber ++;

  }

if(fp) {
      fclose(fp);

    }

  if(matchFound == 0) {

    printf("Error: bad file\n");
    exit(-1);
  }




  return tempInt - 1;
}

// this method prints the contents of the file and replaces
// the #A# and #B# by the input
int fileWriter(char *fileName, float userInputA, float userInputB, int numberLineA, int numberLineB) {

  FILE* fp = fopen(fileName, "r");
  char temp[1000];
  //char c = getc(fp);
  int lineCounter = 0;

	//char firstChar = fgetc(fp);
//printf("%c", firstChar);

  // prints all the lines of the file
  while (fgets(temp, 1000, fp) != NULL) {

    // when we reach the line with #A# we print the user input
    if(lineCounter == numberLineA) {

      printf("a= %.6f\n", userInputA);

      // same thing for #B#
    } else if(lineCounter == numberLineB ) {

      printf("b= %.6f\n", userInputB);

    } else {

      fputs(temp, stdout);


    }
	lineCounter ++;
  }

if(fp) {
      fclose(fp);

    }

  return 0;

}


/////////////////////////////////////////////////

int main(int argc, char *argv[]) {

// Check if the number of arguments is correct
if (argc != 4) {

  printf("Error: too many arguments\n");
  exit(-1);

}

// Here we check if the floats are compatible

// we first check for argv[2]
char compatibleChar[12] = {'0','1','2','3','4','5','6','7','8','9','.'};

for(int j = 0; j < strlen(argv[2]); j++) {
  int counter = 0;

  for(int i = 0; i < 12; i++) {

    if(argv[2][j] == compatibleChar[i]) {
      counter ++;
    }
  }

  if(counter != 1) {
    printf("Error: bad float arg\n");
    exit(-1);
  }
}
// then we check for argv[3]
for(int j = 0; j < strlen(argv[3]); j++) {
  int secondCounter = 0;

  for(int i = 0; i < 12; i++) {

    if(argv[3][j] == compatibleChar[i]) {
      secondCounter ++;
    }
  }

  if(secondCounter != 1) {
    printf("Error: bad float arg\n");
    exit(-1);
  }
}


  char *filePath = argv[1];
  float valueA = atof(argv[2]);
  float valueB = atof(argv[3]);

  // these int are the line numbers for #A# and #B#
  int numberA = fileSearcher(filePath, "#A#", argv) + 1;
  int numberB = fileSearcher(filePath, "#B#", argv) + 1;

  fileWriter(filePath, valueA, valueB, numberA, numberB);


  return 0;
}
