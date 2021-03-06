

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>



typedef  struct {

     char  word[101] ;

     int   freq ;

} WordArray;


//WordArray wordList [10000];
int numOfWords = 0;


// methode compare for the qsort function
int cmp (WordArray *w1, WordArray *w2)
{
	if ((*w1).freq < (*w2).freq)
	{
		return -1;
	}
	else if ((*w1).freq > (*w2).freq)
	{
		return 1;
	}
	else if ((*w1).freq == (*w2).freq)
	{
        return *(char *)w1 - *(char *)w2;
	}
	else
		return 0;
}
void findMedian(void *arg)
{
	//FILE *fp;
	//fp = fopen(fileName, "r");

	char *file = (char*)malloc(sizeof(char));
	file = (char*)arg;

	WordArray wordList [10000];
	
	FILE *fp;
	fp= fopen(file, "r");


	if (fp == NULL){
		printf("Can't open file");
	}

	else{

	//Make the 1st array
	char string[101];

	//Scan through each word and copy it in array
	while((fscanf(fp, "%s", string)) != EOF)
	{
		int i;
		int new = 1; 	//variable to indicate if a new word is encountered

		for(i = 0; i <= numOfWords; i++)
		{
			//compare the word with the ith word in the wordList dataset
			if (strcmp(wordList[i].word, string) == 0)
			{
				new = 0; 				//the word is in the set
				wordList[i].freq++; 	//Increase its freq
				break; 
			}
		}

		if (new == 1)
		{
			//If not in the set, add it in and set freq to one and increase num of words
			strcpy(wordList[numOfWords].word, string);
			wordList[numOfWords].freq = 1;
			numOfWords++;
		}
	}

	int median;

		if((numOfWords % 2) == 0)
		{
			median = numOfWords / 2;
		}
		else
		{
			median = ((numOfWords + 1) / 2);
		}


	//sort the words to find the most freq words using qsort amd cmp
	char *result = (char*)malloc(sizeof(result)*100);
	qsort(wordList, numOfWords, sizeof(WordArray), cmp);
	printf(result, 10000, "%s %d %s \n", fp, numOfWords, wordList[median].word);
	fclose(fp);
	printf("%s\n", result);
}
}

int main (int argc, char *argv[])
{
	//Declare thread
	pthread thread[argc-1];
	int status;
	
	//Run the threads together at the same time 
	int i;
	for(i = 0; i < argc-1; i++)
	{
		char* fileName = (char*)malloc(sizeof(argv[i]+1));
		fileName = argv[i];

		//Creates a new thread per argument and finds the median word
		pthread_create(&thread[i], NULL, (void*) findMedian, (void*) fileName);

		
	}

	for (i = 0; i < argc - 1; i++)
	{
		//Must join the threads again
		pthread_join(thread[i], NULL);
	}
	return(0);
}


