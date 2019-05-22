#include <ctype.h>
#include <stdio.h>



int main(void)
{
    int i, letters[26] = {0};    /* intializing variables and alphabet array */
    char c;

    printf("Enter first word: ");
    while ((c = getchar()) != '\n' ) {   /*read each character that is not the new line */
        if (isalpha(c) && c != ' ') {    /* if the character is in the aplhabet and is not null, proceed to body */ 
            c = tolower(c);  
            letters[c - 'a']++;    /* Filling integer array with occurencing of each char */
        }
    }

    printf("Enter second word: ");
    while ((c = getchar()) != '\n') {
        if (isalpha(c) && c != ' ' ) {
            c = tolower(c);
            letters[c - 'a']--;  /* if a char in the first word is in the second subtract a char occurence */
        }
    }

    for (i = 0; i < 26; i++) {                          /*Loop through the size of the array */
        
        if (letters[i] != 0) {                          /* if the integer array is not empty that means they do not have all the same char */
           
            printf("The words are not anagrams.\n");
            return 0;
        }
    }

    printf("The words are anagrams.\n");    /* We skip the previous step if the integer array is empty indicating that
                                            all the chars in the first are in the second */

    return 0;
}
