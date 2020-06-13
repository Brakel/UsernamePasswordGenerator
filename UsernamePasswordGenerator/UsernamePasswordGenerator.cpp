// UsernamePasswordGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <Windows.h>
#undef max

using namespace std;

// Password character pool - 71 characters
static const char pool[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*?";

char GetRandomChar()
{
    random_device rd; // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<> distr(0, 70); // Define the range

    return pool[distr(gen)];
}

string GeneratePassword(int length) 
{
    string password = "";
    for (int i = 0; i < length; ++i)
    {
        password += GetRandomChar();
    }

    return password;
}

// RANDOMLY SELECTS TWO WORDS FROM WORDS.TXT
// 9894 words
string GenerateUsername()
{
    int line_number = 0;
    string first_word;
    string second_word;
    string username;
    int first_stop;
    int second_stop;

    random_device rd; // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<> distr(1, 9894); // Define the range

    // Generate random numbers
    first_stop = distr(gen);
    second_stop = distr(gen);

    // Open the text file for reading
    ifstream file;
    file.open("words.txt");

    // Loop until the random stop line
    while (line_number != first_stop && getline(file, first_word)) {
        ++line_number;
    }

    file.close();
    file.open("words.txt");

    line_number = 0;
    while (line_number != second_stop && getline(file, second_word)) {
        ++line_number;
    }
    file.close();

    username = first_word + second_word;

    return username;
}

int main()
{
    // Setting up console text colors
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    string username;
    string password;
    int password_length;

    // Setting text color - see output section below
    SetConsoleTextAttribute(hConsole, 14);
    // Validating input
    for (;;)
    {
        cout << "Enter a password length (8-20): ";
        if (cin >> password_length && password_length >= 8 && password_length <= 20)
        {
            break;
        }
        else
        {
            system("cls");
            cout << "Please enter a valid input" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    password = GeneratePassword(password_length);
    username = GenerateUsername();


    // OUTPUT

    // Color your text in Windows console mode
    // Colors are 0=black 1=blue 2=green and so on to 15=white
    // Colorattribute = foreground + background * 16
    // To get red text on yellow use 4 + 14*16 = 228
    // Light red on yellow would be 12 + 14*16 = 236
    SetConsoleTextAttribute(hConsole, 3);
    cout << endl << "<@ Random username & password generator V1.0 @>" << endl;
    cout << "-----------------------------------------------" << endl << endl;

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\tUSERNAME: " + username << endl;
    cout << "\tPASSWORD: " + password << endl << endl;

    SetConsoleTextAttribute(hConsole, 3);
    cout << "-----------------------------------------------" << endl;

    system("PAUSE");
    return 0;
}
