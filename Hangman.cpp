#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int tries = 3;
string message = "You have 3 chances!";

void hang_man(char);
int checkGuess(char, string, string&);

string pickRandomMonth(const vector<string>& months)
{
    srand(time(NULL));
    int month_number = rand() % months.size();
    return months[month_number];
}

int main()
{
    char letter;
    string month;
    vector<string> months;

   
    ifstream file("months.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            months.push_back(line);
        }
        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
        return 1;
    }

    month = pickRandomMonth(months);
    string hide_month(month.length(), 'X');

    
    int random_index = rand() % month.length();
    hide_month[random_index] = month[random_index];

    system("cls");

    while (tries != 0)
    {
        hang_man('n');
        cout << "\t\t\t\tLife: " << tries << endl;
        cout << "\t\t\t\t" << hide_month << endl;
        cout << "\t\t\t\tGuess a letter: ";
        cin >> letter;
        system("cls");

        if (checkGuess(letter, month, hide_month) == 0)
        {
            message = "Incorrect letter!";
            tries--;
        }
        else
        {
            message = "Nice! Correct Guess";
        }

        if (hide_month == month)
        {
            message = "You're Free!";
            hang_man('f');
            cout << "\t\t\t\tLife: " << tries << endl;
            cout << "\t\t\t\tThe month is: " << month << endl;
            break;
        }
    }

    if (tries == 0)
    {
        message = "You're Hanged!";
        hang_man('h');
        cout << "\t\t\t\tLife: " << tries << endl;
        cout << "\t\t\t\tThe month is: " << month << endl;
    }

    return 0;
}

int checkGuess(char guess, string real_month, string& hidden_month)
{
    int matches = 0;
    int len = real_month.length();
    for (int i = 0; i < len; i++)
    {
        if (guess == hidden_month[i])
        {
            return 0;
        }
        if (guess == real_month[i])
        {
            hidden_month[i] = guess;
            matches++;
        }
    }
    return matches;
}

void hang_man(char state)
{
    string head_string = "|" ; 
    if(state == 'f')
    {
        head_string = " " ;
    }
    string floor_string = "=";
   if (state == 'h')
    {
    	floor_string = " " ;
	}
	string rope_string = "|" ;
	 if(state == 'h')
	{
		rope_string="/" ;
	}
    cout << "\t\t\t\t__________________" << endl;
    cout << "\t\t\t\t        "<<head_string<<"        |" << endl;
    cout << "\t\t\t\t        o        |" << endl;
    cout << "\t\t\t\t       / \\       |" << "\t  " << message << endl;
    cout << "\t\t\t\t        |        | " << "\t    /" << endl;
    cout << "\t\t\t\t       / \\       |         o" << endl;
    cout << "\t\t\t\t    =="<<floor_string<<floor_string<<floor_string<<floor_string<<floor_string<<floor_string<<"==   |        / \\" << endl;
    cout << "\t\t\t\t    |        |   |         |  " << endl;
    cout << "\t\t\t\t    |        |   |    "<<rope_string<<"   / \\" << endl;
    cout << "\t\t\t\t=====================|=|============" << endl;
}
