#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
//letterToSymbol.txt for letter mappings
//Can be altered as it is read only within the program

int scaledRand(int minVal, int maxVal)
{
    /*
    randomNum is the number to be scaled
    Returning a random number in the range minVal to maxVal
    maxVal not in the interval
    */
    
    //MAKING CHANGE FROM RAND*RAND TO JUST RAND
    int number = (rand()) % (maxVal - minVal);
    number = number + minVal;
    return number;
    
    //Did not do number % maxVal + minVal
    //This makes sure each number is equally likely
}

//****************************************
//Data collection and phrase/word checkers
//****************************************

void getUserInput(char userInput[])
{
    //Function to take in the base phrase for the password
    printf("This generator requires a starting word to base the password off of.\n");
    printf("Enter the data : ");
    gets(userInput);
}


int isPhrase(char userInput[])
{
    int spaceCount = 0;
    int len = strlen(userInput);
    for(int count = 0; count < len; count++)
    {
        if(userInput[count] == ' ')
        {
            //To handle segmentation error for last element
            //Handles multiple adjacent spaces and counts them as one space
            if(count < len - 1 && userInput[count + 1] != ' ')
            {
                spaceCount = spaceCount + 1;
            }
        }
        if (spaceCount >= 1) 
        {
            return 1;
        }
    }
    return 0;
}


//****************************
//Password Generator functions
//****************************

char toCapital(char letter)
{
    //Takes a character and returns the capital letter of it
    int capiGap = 'a' - 'A';
    return(letter - capiGap);
}


char toSmall(char letter)
{
    //Takes in a character and returns the small letter of it
    int smallGap = 'a' - 'A';
    return(letter + smallGap);
}


int isCapital(char letter)
{
    if(letter >= 65 && letter <= 90)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}


int isSmall(char letter)
{
    //Wrote the if statement for readability
    if(letter >= 97 && letter <= 122)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


int isLetter(char letter)
{
    //Returns true i.e 1 if the input is a letter
    if((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}


int noOfSpaces(char string[])
{
    char *pointer = string;
    int spaceCount;
    while(*pointer++)
    {
        //Need to fix issue
        //Spaces at the end of the string are all counted
        if (*pointer == ' ' && *(pointer + 1)!= ' ')
        {
            spaceCount++;
        }
    }
    return spaceCount;

}


//**************
//Crux functions
//**************

void removeSpaces(char userInput[])
{
    //Function to remove spaces from the password pointer
    char *traverser = userInput;
    int inputLength = strlen(userInput);
    char *temp = (char *)malloc(sizeof(int)*inputLength);
    char *temptemp = temp;


    while(*traverser)
    {
        if (*traverser != ' ')
        {
            *temp = *traverser;
            temp++;
        }
        traverser++;

    }

    //Making the end of temp into null character
    *temp = '\0';
    
    traverser = userInput;
    temp = temptemp;
    //printf("Traverser :%s\n", traverser);
    //printf("Temp :%s", temp);

    while(*temp)
    {
        *traverser = *temp;
        traverser++;
        temp++;  
    }
    //Costly lesson, making the end of every string I modify into null character
    *traverser = '\0';

    //printf("New userInput in removeSpace function:%s", userInput);

    //freeing temp
    //Oddly, program stopped working after removeSpace func call when temp was freed
    //free(temp);

}

void appendSymbol(char letter, char password[])
{

    /*
    FROM MAIN
    //Creating file pointer
    FILE *userData;
    userData = fopen("userData.txt", "w");
    fputs("My name is bullbaba", userData);
    fprintf(userData, "%s", "Bullbaba");
    fclose(userData);
    File handling example
    Cause I don't know how to do this yet XD
    */
    
    FILE *letterToSymbol;
    letterToSymbol = fopen("letterToSymbol.txt", "r");
    char dict[20] = {'\0'};
    
    char smLetter;
    if(isCapital(letter))
    {
        smLetter = toSmall(letter);
    }
    else
    {
        //Forgot to do this and took 20 minutes to fix :(
        smLetter = letter;
    }
    
    //printf("letter is :'%c'\n", letter);
    //printf("isCapital(letter) :'%d'\n", isCapital(letter));
    //printf("Small letter is :'%c'\n", smLetter);
    //BUG CHECK

    
    while(dict[0] != smLetter)
    {
       fgets(dict, 20, letterToSymbol);
       //I need to learn to use fscanf
    }


    int choice = noOfSpaces(dict)+1;
    int random = scaledRand(0, choice);
    char *dictPointer = dict;
    
    //printf("%s", dict);
    //printf("Choices = %d\n", choice);
    //choose number of spaces and append that from file
    //printf("0 <= Random < choices = %d\n", random);
    

    //Getting to the random symbol combination
    int spaceCount = 0;
    while(spaceCount < random)
    {
       if (*dictPointer == ' ')
       {
           spaceCount++;
       }
       dictPointer++;
    }


    //Moving the password pointer till the end
    char *passwordPointer = password;
    while(*passwordPointer)
    {
        passwordPointer++;
    }
    
    //Writing the symbol and the end of the password string
    while(*dictPointer != ' ' && *dictPointer != '\n')
    {
        *passwordPointer = *dictPointer;
        passwordPointer++;
        dictPointer++;
    }

    //Manually making the last character to null to prevent segmentation fault
    *(passwordPointer) = '\0';

    //Closing the file
    fclose(letterToSymbol);
    
    // printf("The password : %s\n", password);

}


void appendSpecial(char password[])
{
    /*
    Appends a special character
    Serves the purpose of replacing one special character given by the user
    With another random one
    Functions used inside
        scaledRand()
    */
    
    //Contains all possible standard special characters
    char sampleSpace[33] = {'!', '\"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~', '\0'};
    int specLen = strlen(sampleSpace);
    char *pointer = password;
    
    //Moving string pointer to the end
    while(*pointer)
    {
        pointer++;
    }
    int random = scaledRand(0,specLen);
    *pointer = sampleSpace[random];

    //Manually adding the null character for created string
    pointer++;
    *pointer = '\0';
    
}


void LettersToSymbols(char password[], char userInput[])
{
    /*
    Final function for single word input into password
    Funcions used inside
        isLetter()
        appendSymbol()
        appendSpecial()
        removeSpaces()
    */
    
    
    //*******
    //TESTING
    //*******
    // char *tempPoint = userInput;
    // printf("Here I am printing tempPoint\n");
    // while(*tempPoint)
    // {
    //     printf("%c", tempPoint);
    //     tempPoint++;
    // }
    //*******Testing ends here
    // printf("New userInput :%s", userInput);
    
    //This stopped the junk value from appearing
    password[0] = '\0';
    
    //Remove the spaces from the input
    removeSpaces(userInput);
    
    char *pwdPoint = password;
    char *inputPoint = userInput;
    int wordLen = strlen(userInput);
    
    //Appending the new characters to the password string
    for(int trav = 0; trav < wordLen; trav++)
    {
        if(isLetter(userInput[trav]))
        {
            appendSymbol(userInput[trav], password);
        }
        else
        {
            appendSpecial(password);
        }
        //printf("The password : %s\n", password);
    }
    
}


void fineTune(char password[])
{
    //Adding numbers at the end
    char *passwordPointer = password;
    
    //Chooses a random number, either 2 or 3
    int numbersToAdd = scaledRand(2,4);

    //Moving the password pointer to the very end
    while(*passwordPointer)
    {
        passwordPointer++;
    }

    //Adding numbersToAdd numbers
    for(int count = 0; count < numbersToAdd; count++)
    {
        *passwordPointer = (char)scaledRand(48, 58);
        *passwordPointer++;
    }
    
    //As usual ,this again
    *passwordPointer = '\0';
}


//Things to do
//Handle spaces and numbers in the given string
//encrypt function
//decrypt function
//write password into file
//Read password from file
//Make a standard format for the password file



int main()
{
    char *userInput = (char *)malloc(sizeof(char)*50);
    char *password = (char *)malloc(sizeof(char)*30);
    srand(time(0));
    
    //The body of the program
    getUserInput(userInput);
    removeSpaces(userInput);
    LettersToSymbols(password, userInput);
    fineTune(password);
    
    //Printing the password
    printf("The password is %s", password);

    free(userInput);
    free(password);

}



/*
int main()
{
    //Accepting a string to base the password off of
    char userinput[200];
    //getUserInput(userinput);

    srand(time(0));
    char password[30];
    //LettersToSymbols(password, userinput);
    
    //*******************
    //Testing
    //*******************
    char test[100] = {'b', 'u', 'l', 'l', 'b', 'a', 'b', 'a', '\0'};
    printf("Enter the userInput:");
    gets(userinput);
    //printf("The user input is :%s\n", userinput);
    removeSpaces(userinput);
    printf("The string without spaces %s\n", userinput);

}

*/



//    userData = fopen("C:\\Password Generation and Encryption\\userData.txt", "w");

/*

Reference : https://www.microsoft.com/en-us/research/wp-content/uploads/2016/06/Microsoft_Password_Guidance-1.pdf

About Program
    In C, a file once compiled will give the same set of random numbers unless complied again
    srand() function alters the seed of the rand() function
    To make a random seed we use the current time as the seed for that program session

Basic requirements
    Minimum length
    Upper and lower case
    Special characters
    No common words with the username or other tag
    Banning common passwords

Semi Advanced requirements
    No repeated adjacent words


Password encryption schemes
    Move letters forward or backward
    Swap positions cyclically every n letters
    Add random number to the characters
    Random capitalization
    Substitution of letters with symbol equivalents (ex a with @)


Procedure
    To generate a random password from a given word

Find if phrase
If phrase
    Take nth letter from each word if more than 9 words

if word
    replace letters with symbol equivalents
        double slash for printing single slash
        combination of characters for a single character
        choosing combination is random

*/






/*
DUMMY CODE

void writePassword(FILE *filepointer, char *password)
{
    
    Takes in a pointer to a file variable
    Takes in a constant string
    Writes the constant string into the file
    
    fputs(password, filepointer);
}

void encrypt(char *password, char *ecrpassword)
{
    /*
    Encrypts the password and writes it into another string ecrpassword
    Things to be added
        While loop to get the length

    
   while (len(ecrpassword) < 12)

    ;
}

FROM MAIN
    //Creating file pointer
    FILE *userData;
    userData = fopen("userData.txt", "w");
    fputs("My name is bullbaba", userData);
    fprintf(userData, "%s", "Bullbaba");
    fclose(userData);

*/


/*
Data to be accepted from the user
- Length required
- Some keywords unique to the user
- Strength Scale
- 
*/