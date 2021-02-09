//
//  main.cpp
//  Project 4
//
//  Created by Rehan Kedia on 11/13/17.
//  Copyright © 2017 Rehan Kedia. All rights reserved.
//

#include <iostream>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;


void PrintMessage(string message, bool printTop = true, bool printBottom = true)
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
    
    if (printBottom)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}


void DrawHangman(int guessCount = 0)
{
    if (guessCount >= 0)
        PrintMessage("|", false, false);
    if (guessCount >= 1)
        PrintMessage("O", false, false);
    else
        PrintMessage("", false, false);
    if (guessCount == 2)
        PrintMessage("/", false, false);
    if (guessCount == 3)
        PrintMessage("/|", false, false);
    if (guessCount >= 4)
        PrintMessage("/|\\", false, false);
    else
        PrintMessage("", false, false);
    if (guessCount == 5)
        PrintMessage("/", false, false);
    if (guessCount >= 6)
        PrintMessage("/ \\", false, false);
    else
        PrintMessage("", false, false);
}


void PrintLetters(string input, char from, char to)
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    PrintMessage(s, false, false);
}



bool PrintWordAndCheckWin(string word, string guessed)
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
        
    {
        tolower(word[i]);
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s, false);
    return won;
}


string LoadRandomWord(string path)
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader("/users/rehan/Downloads/capitals.txt");
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);
        
        int randomLine = rand() % v.size();
        
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}


int TriesLeft(string word, string guessed)
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}


int main()
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess = LoadRandomWord("/users/rehan/Downloads/capitals.txt");
    int tries = 0;
    bool win = false;
    do
    {
        cout << endl;
        cout << endl;
        PrintMessage("HANGMAN");
        DrawHangman(tries);
        PrintMessage("Guess the word");
        win = PrintWordAndCheckWin(wordToGuess, guesses);
        if (win)
            break;
        
        char x;
        cout << ">"; cin >> x;
        if (guesses.find(x) == string::npos)
            guesses += x;
        
        tries = TriesLeft(wordToGuess, guesses);
    } while (tries < 7);
    
    if (win)
        PrintMessage("YOU WON!");
    else
    {
        PrintMessage("GAME OVER");
        cout << "The correct answer was: " << wordToGuess << endl;
    }
    
    system("pause");
    getchar();
    return 0;
}
