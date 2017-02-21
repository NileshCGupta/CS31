//
//  mindreading.cpp
//  CS31 Winter 2015
//  File: HW #2 – Reading my mind
//  Author: Nilesh Gupta (nileshcgupta@gmail.com)
//  SID: 604489201
//  Date: 2015-1-21
//  Version: 1.0
//  Description: This is the HW #2
//
//  Created by Nilesh Gupta on 1/21/15.
//
//

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    string name;
    int difficulty;
    int smallestInt;
    int largestInt;
    int easyGuess;
    int hardGuess;
    int guess;
    int number;
    int i = 1;
    char playAgain;
    
    cout << "======================================\nMindreading (v1.0)\nCopyright 2015 Bruinie\n\nWelcome to Mindreading Game!\nGood luck and have fun!\n======================================\n";
    cout << "Please make the following selections:\n";
    cout << "Your Name: ";
    getline (cin, name);
    while (name == "")
    {
        cout << "You must enter your name.\n";
        getline (cin, name);
    }
    cout << "Level of Difficulty (1 – Easy; 2 – Hard): ";
    cin >> difficulty;
    while (difficulty != 1 && difficulty != 2)
    {
        cout << "Level of difficulty must be 1 (Easy) or 2 (Hard).\n";
        cin >> difficulty;
    }
    cout << "The smallest positive integer you want to guess: ";
    cin >> smallestInt;
    while (smallestInt < 1)
    {
        cout << "It must be a positive integer.\n";
        cin >> smallestInt;
    }
    cout << "The largest positive integer you want to guess: ";
    cin >> largestInt;
    while (largestInt < 1)
    {
        cout << "It must be a positive integer.\n";
        cin >> largestInt;
    }
    while (largestInt <= smallestInt)
    {
        cout << "The biggest integer must be greater than the smallest integer.\n";
        cin >> largestInt;
    }
   
    number = rand() % (largestInt - smallestInt + 1) + smallestInt;
    easyGuess = (int)(ceil(.8 * log2(largestInt - smallestInt + 1)));
    hardGuess = (int)(ceil(.4 * log2(largestInt - smallestInt + 1)));
    
    
    if (difficulty == 1)
    {
        cout << "Awesome, " << name << "! I’m thinking of an integer between " << smallestInt << " and " << largestInt << ". Make a guess.\n";
        while (i <= easyGuess)
        {
            cin >> guess;
            if (guess == number)
            {
                cout << "Congratulations, " << name << "! You guessed the secret number " << number << "!\n";
                cout << "<Play Statistics>\n" << "- Name: " << name << "\n- Level: 1\n" << "- Total number of times to guess " << number << ": " << i << endl;
                cout << "Do you want to play another game (Y/N)?\n";
                cin >> playAgain;
                while (playAgain != 'Y' && playAgain != 'N')
                {
                    cout << "You must enter either Y or N.\n";
                    cin >> playAgain;
                }
                if (playAgain == 'Y')
                {
                    number = rand() % (largestInt - smallestInt) + smallestInt;
                    i = 1;
                    cout << "Awesome, " << name << "! I’m thinking of an integer between " << smallestInt << " and " << largestInt << ". Make a guess.\n";
                }
                else
                {
                    cout << "Thank you for reading my mind, " << name << "! Goodbye!\n";
                    return 0;
                }
            }
            else if (guess == -1)
            {
                cout << "Sorry, " << name << "! Goodbye!\n";
                return 0;
            }
            else if (i == easyGuess)
            {
                cout << "Sorry, " << name << "! Game Over!\n";
                cout << "Do you want to play another game (Y/N)?\n";
                cin >> playAgain;
                while (playAgain != 'Y' && playAgain != 'N')
                {
                    cout << "You must enter either Y or N.\n";
                    cin >> playAgain;
                }
                if (playAgain == 'Y')
                {
                    number = rand() % (largestInt - smallestInt) + smallestInt;
                    i = 1;
                    cout << "Awesome, " << name << "! I’m thinking of an integer between " << smallestInt << " and " << largestInt << ". Make a guess.\n";
                }
                else
                {
                    cout << "Thank you for reading my mind, " << name << "! Goodbye!\n";
                    return 0;
                }
                
            }
            else if (guess < number)
            {
                cout << "Sorry, " << name << "! I’m thinking of a larger number. Try again or enter -1 to exit.\n";
                i++;
            }
            else if (guess > number)
            {
                cout << "Sorry, " << name << "! I’m thinking of a smaller number. Try again or enter -1 to exit.\n";
                i++;
            }
        }
    }
    else if (difficulty == 2)
    {
        cout << "Awesome, " << name << "! I’m thinking of an integer between " << smallestInt << " and " << largestInt << ". Make a guess.\n";
        while (i <= hardGuess)
        {
            cin >> guess;
            if (guess == number)
            {
                cout << "Congratulations, " << name << "! You guessed the secret number " << number << "!\n";
                cout << "<Play Statistics>\n" << "- Name: " << name << "\n- Level: 1\n" << "- Total number of times to guess " << number << ": " << i << endl;
                cout << "Do you want to play another game (Y/N)?\n";
                cin >> playAgain;
                while (playAgain != 'Y' && playAgain != 'N')
                {
                    cout << "You must enter either Y or N.\n";
                    cin >> playAgain;
                }
                if (playAgain == 'Y')
                {
                    number = rand() % (largestInt - smallestInt + 1) + smallestInt;
                    i = 1;
                }
                else
                {
                    cout << "Thank you for reading my mind, " << name << "! Goodbye!";
                    return 0;
                }
            }
            else if (i == hardGuess)
            {
                cout << "Sorry, " << name << "! Game Over!\n";
                cout << "Do you want to play another game (Y/N)?\n";
                cin >> playAgain;
                while (playAgain != 'Y' && playAgain != 'N')
                {
                    cout << "You must enter either Y or N.\n";
                    cin >> playAgain;
                }
                if (playAgain == 'Y')
                {
                    number = rand() % (largestInt - smallestInt + 1) + smallestInt;
                    i = 1;
                    cout << "Awesome, " << name << "! I’m thinking of an integer between " << smallestInt << " and " << largestInt << ". Make a guess.\n";
                }
                else
                {
                    cout << "Thank you for reading my mind, " << name << "! Goodbye!\n";
                    return 0;
                }
                
            }
            else if (guess == -1)
            {
                cout << "Sorry, " << name << "! Goodbye!\n";
                return 0;
            }
            else
            {
                cout << "Sorry, " << name << "! Try again or enter -1 to exit\n";
                i++;
            }
        }
    }
    return 0;
}
