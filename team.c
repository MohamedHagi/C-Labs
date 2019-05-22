//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Mohamed Hagi>
// Student Info: <213780929>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE

//struct for player contains the familyName, firstName, position, value, and pointer to next node:

struct Player {
    
    char * familyName;
    char * firstName;
    char position;
    int value;
    struct Player * next;   
};


//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE

//functions used throughout program:

struct Player * createPlayerNode(char * familyName, char * firstName, char position, int value);
struct Player * insertPlayer(struct Player * head, struct Player *player);
void familySearch(struct Player * head, char familyName[]);
void valueSearch(struct Player * head, int value);
struct Player * deletePlayer(struct Player * head, char familyName[]);
struct Player * quit(struct Player * head);
bool catchDuplicate(struct Player * head, char familyName[]);
void printTeam(struct Player * head);
void printPlayerInfo( struct Player *player);
bool checkValue(int value);
bool tooMany(char position);
void tooManyPrint(void);
void checkValuePrint(void);


//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.

              struct Player *head = NULL;

 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    
    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            char familyName[MAX_LENGTH+1];
            char firstName[MAX_LENGTH+1];
            char charValue[MAX_LENGTH+1];
            char position;
            int value;
            
            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            printf("  family name: ");
            safegets(familyName,MAX_LENGTH+1);
            printf("  first name: ");
            safegets(firstName,MAX_LENGTH+1);
            printf("  position: ");
            position = toupper(getchar());
            if(!tooMany(position)){         //Checking if the input for position is too long

                tooManyPrint();
                continue;

            }


            printf("  value: ");
            safegets(charValue,MAX_LENGTH+1);
            value = atoi(charValue);
            if(!checkValue(value)){         // Checking if the value is positive

            checkValuePrint();
            continue;

            }    

            if(catchDuplicate(head, familyName)){   // catching duplicate last names
                familyNameDuplicate(familyName);
                continue;
            }

            struct Player * player = createPlayerNode(familyName,firstName,position,value);  // creating new player node
            head = insertPlayer(head, player);    // inserting player into linked list

        }
        else if (response == 'D')
        {
           // Delete a player from the list.
            char familyName[MAX_LENGTH+1];
            printf("\nEnter family name for entry to delete: ");
            safegets(familyName,MAX_LENGTH+1); //read the familyName from user
      
			head = deletePlayer(head, familyName);  // use deletePlayer func to remove node from list

        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            char familyName[MAX_LENGTH+1];
            printf("\nEnter family name to search for: ");
            safegets(familyName,MAX_LENGTH+1); // read the familyName from user
           familySearch(head, familyName);	// use familySearch func to return the user with the given family name
        }
        else if (response == 'V')
        {
            char charValue[MAX_LENGTH+1];
            int value;
            printf("\nEnter value: ");
            safegets(charValue,MAX_LENGTH+1); // read value
            value = atoi(charValue);   // convert into int

              checkValue(value);  // check if the value is negative or not
            
            valueSearch(head, value);   // use the valueSearch func to find players with the given value range

        }
        else if (response == 'P')
        {
            // Print the team.

            printTeam(head);

        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');
  
    // Delete the whole linked list that hold the team.

	head = quit(head); //remove all nodes in the lsit, empty list


    // Print the linked list to confirm deletion.
   
   printTeam(head);  


    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);
	
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.

//Function to create a new player node:


struct Player * createPlayerNode(char * familyName, char * firstName, char position, int value){
   

    struct Player * newPlayer = malloc(sizeof(struct Player));
    
    if(newPlayer == NULL)  // base case when node is empty
    {
        printf("Memory Error: Player node is empty ! \n");
        exit(EXIT_FAILURE);
    }


    newPlayer->familyName = (char*) malloc(strlen(familyName)*sizeof(char));
   
    if(newPlayer->familyName == NULL)
    {
        printf("Memory Error: unable to add familyName.\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(newPlayer->familyName,familyName); // inserting familyName
    
    newPlayer->firstName = (char*) malloc(strlen(firstName)*sizeof(char));
    
    if((*newPlayer).firstName == NULL)
    {
        printf("Memory Error: unable to add firstName.\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(newPlayer->firstName,firstName);    // inserting fisrtName
    newPlayer->position = position;           // inserting position
    newPlayer->value = value;                 // inserting value
    newPlayer->next = NULL;                   // pointer to next node
   
    return newPlayer;
}

//Function to insert the new created node into the linked list in order GDMS:


struct Player * insertPlayer(struct Player * head, struct Player *player){
    
    char position = player->position; // used to check if GDMS
    

    

     if(!(position == GOALKEEPER || position == DEFENDER || position == MIDFIELDER || position == STRIKER)){  //If the new players position doesnt match GDMS 
        free(player->familyName);
        free(player->firstName);
        free(player);
        printf("\nThe position '%c' is not a valid, must be either 'G', 'D', 'M', or 'S'\n", position);
        return head;
    }

      


    //if the list is empty just add to front.

    if(head==NULL){ 
    head=player;
    return head;
    }

//switch case to figure out where to add new node according to the order GDMS



    switch(position) {
      
        case 'G' :
            //head exist you and not G, you add new player to the front
            if((*head).position!=GOALKEEPER){
                (*player).next=head;
                head=player;
            }else{
                struct Player * pathFinder = head;  
                //pathFinder will search till it sees the last G in the list, then it will insert the new Goalie
                while( pathFinder->next != NULL && pathFinder->next->position == 'G'){
               
                pathFinder = pathFinder->next;
                
                }
                player->next = pathFinder->next;
                pathFinder->next = player;
            }
            break;
      
        case 'D' :
           
           //Check if head is at a M or S and if It is add D infront of the first M or S

            if((*head).position=='M'||(*head).position=='S'){
                (*player).next=head;
                head=player;
            }else{
                struct Player * pathFinder = head;
               //iterate through the list until you see M and put infront and if theres no M then S and put in front and if theres no M or S add Defender at end of list
                while(pathFinder->next!=NULL&&(*(*pathFinder).next).position!='M'&&(*(*pathFinder).next).position!='S'){
                pathFinder = pathFinder->next;
                }
                player->next = pathFinder->next;
                pathFinder->next = player;
            }
            break;

        case 'M' :
            //Check if head is S if so Add M to the front
            if((*head).position=='S'){
                (*player).next=head;
                head=player;
            }else{
                struct Player * pathFinder = head;
                //iterate through the list until you find the first S and place it infront of it
                while(pathFinder->next!=NULL&&(*(*pathFinder).next).position!='S'){
                pathFinder=pathFinder->next;
                }
                player->next=pathFinder->next;
                pathFinder->next=player;
            }
            break;
        case 'S' :
    //The Striker always gets put at the end
            if(1){
                struct Player * pathFinder = head;
                while(pathFinder->next != NULL){
                pathFinder = pathFinder->next;
                }
                pathFinder->next=player;
            }
            break;
       
   }
    return head;
}

struct Player * deletePlayer(struct Player * head, char familyName[])
{
    
    if(head==NULL){
        familyNameNotFound(familyName);  // error msg if family is empty
        return head;
    }
    
    struct Player * prev = NULL;
    struct Player * cur = head;
    
    
    // iterate through the list until the family name matches
    while(cur != NULL){
        if(strcmp(cur->familyName,familyName)==0){    //checking if the current familyName matches the given familyName
        break;
        }// going through the list if family name not found
        prev = cur;
        cur = cur->next;  
    }
    
    if(cur==NULL){
        familyNameNotFound(familyName);   // couldnt find given family name in team list
        return head; 
    }

    if(prev == NULL){
        //case where the node that will be deleleted is the first one
        head = head->next;     
        familyNameDeleted(cur->familyName);
    } else {
        prev->next = cur->next;     // or the node is a another one
        familyNameDeleted(cur->familyName);
    }

    //removing the node containing the given family name and assigning the prev node its position
    
	cur->next=NULL;
    free(cur->familyName);
    free(cur->firstName);
    free(cur);
    cur = head;
    prev = head;
	
    return head;            
}

void familySearch(struct Player * head, char familyName[]){
    
    //First check if the name even exist in the team list
    if(!catchDuplicate(head, familyName)){
		
		//familyName not in the list 
        familyNameNotFound(familyName);
        
    } else {
		//familyName is in the team list, proceed to delete
        familyNameFound(familyName);
        struct Player * pathFinder = head;
       
	   while(pathFinder!=NULL){ // interate through the team list until you find the player with the given family name.
            if(strcmp(pathFinder->familyName,familyName)==0){
                break; // if found leave loop
            }
            pathFinder = pathFinder->next; // go to the next node very iteration where the player wasnt found
        }
        printPlayerInfo(pathFinder);  // print the player info of the found player
        
    }
}


void valueSearch(struct Player * head, int value){
    
    bool playersExists = false;  // boolean to check is players exist that have a value less or equal to given value
   
   struct Player * pathFinder = head;
	
    while(pathFinder != NULL){					// iterate through the teamlist and check if
        if(pathFinder->value <= value){
           
		   printPlayerInfo(pathFinder);   // print the player info of each player with a value in the given range
            playersExists = true;         // player with the given range value exists
        }
        pathFinder = pathFinder->next;  // go to the next node each iteration
    }
    if(!playersExists){ 					// No Players exist in the list with given range.
	
	printNoPlayersWithLowerValue(value);  
	
	}
}

struct Player * quit(struct Player * head){
   
   struct Player * removeNode;
   
   while(head!=NULL){ // iterate through the team list and remove every node.
        
		removeNode = head;
       
	   head = head->next;

	   removeNode->next = NULL;  // nullify 
       
	   free(removeNode->familyName); //free up memory for familyName 
        free(removeNode->firstName); // free up memory for firstName
        free(removeNode);			// free up memory for the entire node
    }
	
    removeNode = head; // the emptied list is the new list 
    
	return head;
}




bool catchDuplicate(struct Player * head, char familyName[]){
    struct Player * pathFinder = head;
    while(pathFinder!=NULL){
        if(strcmp(pathFinder->familyName,familyName)==0){  // if the familyName at the current node in linked list matches the desired family name, return true
            return true;
        }
        pathFinder=pathFinder->next;  // iterate 
    }
    return false; // return false if the familyNames dont match.
}


bool checkValue(int value){ // checking if value is positive


    if(value<0){ 
                return false;
                
            }

            return true;
   

}

void checkValuePrint(void){ // error message when value is negative

              printf("\nPlayer was not entered, the player's value must be greater then 0\n" );
}


bool tooMany(char position){

bool tooMany=false;
char ch;

 while((ch=getchar())!= NEWLINE){  // checking if the input for position is Longer that 1, if more then one then it has too many
                tooMany=true;
            }
            
            if(tooMany){     // if there is more then 1 char, return false other wise return true
      
                return false;
            }

            return true;




}

void tooManyPrint(void){ // error message when there are too many characters 

              printf("\nEntered too many characters, the player position can only be 'G', 'D', 'M', or 'S'\n" );
}

//printting the team list
void printTeam(struct Player * head){
    if(head != NULL){ // if the teamlist is not empty, print the team
	
	
		printTeamTitle(); 
        struct Player * pathFinder = head;  // use pathFinder temp node to iterate through the list
        while(pathFinder != NULL){
            
            printPlayerInfo(pathFinder); // print the player info every iteration 
            pathFinder=pathFinder->next;  // go to the next node
        }
        
    } else {
		
		printTeamEmpty(); // print msg if the teamlsit is empty
       
    }
}

// printing the individual player information

void printPlayerInfo(struct Player *player){
	
   // printing the player info
	printf("\n%s\n",player->familyName);
    printf("%s\n", player->firstName);
    printf("%c\n",player->position);
    printf("%d\n",player->value);
}

