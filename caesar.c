    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>

    #define SIZE 80   /*defining constants*/
    #define UPPER_START 'A'
    #define LOWER_START 'a'
    #define UPPER_END 'Z'
    #define LOWER_END 'z'

    int main(void)
    {
        char message[SIZE];  /* initialize char array message */
        char c;
        int i, l, samount;

        printf("Enter message to be encrypted: "); /* Prompt user for message to be encrypted */
    i = 0;
       while((c = getchar())!= '\n') {  /*read character from userinput
    */

    if( i > SIZE ){

    printf("Size of message too big, try again\n");   /* If message exceeds 80 chars, exit and prompt user to try again*/

    return 0;

    }
            message[i] = c; /* read each char of the message, and put in char array message*/
    i++;
        }
    	
    	int j;

    l = i; /* Length of message */

    printf("Enter shift amount (1-25): "); /* Read shift ammount */

    if((scanf("%d", &samount)) != 1 || (samount < 1 || samount >= 26)){  /* Check if shift amount is in range */

    printf("Input is either not a valid integer or is out of range, run program again\n");

      return 0;
    }
    else{


    printf("Encrypted message: ");

        for (j = 0; j < l; j++) {
            c = message[j];
            
            if (c >= UPPER_START && c <= UPPER_END){
                c = (( c - UPPER_START) + samount) % 26 + UPPER_START;      /* shift characters in uppercase with wrap around */
            }
            
            if (c >= LOWER_START && c <= LOWER_END){
                c = (( c - LOWER_START) + samount) % 26 + LOWER_START;    /* shift characters in lowercase with wrap around */
            }
     
            

            printf("%c", c);      /* print out encrypted message*/
        }
        puts("");
        return 0;
    }
    }
