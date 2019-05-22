//
// EECS2031 encrypt.c
//

//
//
// Program that reads file and encrypts it .
//
// Author: <Mohamed Hagi>
// Student Info: <213780929>

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_LEN 256

int encrypt(char *filename, int shiftValue);
void checkArgs(int argcount);
const char* addEnc(char *filename);


int main(int argc, char *argv[])
{

checkArgs(argc);
char* filename = argv[1]; // second argument is the file name.
int shiftValue = atoi(argv[2]); // third argument is the shiftValue.

if(shiftValue  < 1) {  // check if shit is in range
	
	
	shiftValue = -shiftValue; // if negative change to pos
}

	if(shiftValue > 26) {  // Check if shift amount is in range 

shiftValue = shiftValue % 26;  // mod 26 to make sure it is less than 26 

 
}


encrypt(filename, shiftValue);

}


void checkArgs(int argcount){
	
	// Check if there is more then 3 arguments

if(argcount != 3){
	 printf("Too many arguments !\n");
	printf("Usage: encrypt <filename> <shift number>\n");

	exit(0);
	
	
	
}
}


const char* addEnc(char *filename){


const char* newfilename = strcat(filename,".enc");  // adding the .enc to the end of the output file
return newfilename;




}

int encrypt(char *filename, int shiftValue){

const char * rb = "rb";
FILE *fInput = fopen(filename, rb); //  file input using the rb mode, opening for reading in binary mode.
FILE *fOutput = fopen(addEnc(filename), "w+"); // using w+ to open for both reading and writing
char c;
char new_c;


if (fInput == NULL|| fOutput == NULL)
{
	printf("Error: File Cannot be opened \n"); // Error msg if file cannot be opened
	return 1;
}


while ((c = fgetc(fInput)) != EOF)
{
	if(isalpha(c))
	{
		if(islower(c))
			new_c = (c + shiftValue - 'a') % 26 + 'a';  // shift for lowercase
		else
			new_c = (c + shiftValue - 'A') % 26 + 'A';  // shift for uppercase
	}
	else
		new_c = c;
	if (fputc(new_c, fOutput) == EOF)
	{
	   //This is a error
	}
}

fclose(fInput);  // close file input
fclose(fOutput); // close file output 

return 0;
}






































