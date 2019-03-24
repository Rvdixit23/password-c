#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>


int scaledRand(int minVal, int maxVal)
{
    /*
    randomNum is the number to be scaled
    Returning a random number in the range minVal to maxVal
    maxVal not in the interval
    */
    
    int number = (rand()*rand()) % (maxVal - minVal);
    number = number + minVal;
    return number;
    
    //Did not do number % maxVal + minVal
    //This makes sure each number is equally likely
}

int letterIn(char letter, char password[])
{
    /*
    Same as 'in' from python
    Given a letter and a string, returns 1 if the letter is in the string
    0 otherwise
    */
    int len = strlen(password);
    for(int count = 0; count < len; count++)
    {
        if (letter == password[count])
        {
            return 1;
        }
    }
    return 0;
}

void genRandomPassword(char password[])
{
    /*
    Generates a random password and stores it in the given char array
    Functions used:
        scaledRand()
        rand()
        letterIn
    */
    
    char letter;
    int passwordLength = scaledRand(9,16);
    int randomNumber;
    int test;
    for(int count = 0; count < passwordLength; count++)
    {
        randomNumber = scaledRand(33, 126);
        //printf("Random number is %d \nrand() %d\n", randomNumber, rand());
        //To prevent the letter from being repeated
        while(letterIn((char)randomNumber, password))
        {
            randomNumber = scaledRand(33,126);
        }
        
        letter = randomNumber;
        password[count] = letter;
    }
}

int main()
{
    char password[20];
    srand(time(0));
    genRandomPassword(password);
    printf("The random password is %s \n", password);
    //printf("a in aieo is %d", letterIn('a', "beeiouuuuuuuuuuuuu"));
}