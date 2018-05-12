#include "console.hpp"

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

/* Differents affichages de texte console
for(int k = 1; k < 255; k++)
{
    SetConsoleTextAttribute(hConsole, k);
    cout << k << " I want to be nice today!" << endl;
}
system("pause");
*/

int saisie()
{
    int nombre;
    bool valide;
    do
    {
        try
        {
            std::cin >> nombre;
            valide = true;
            if(!std::cin.good()) throw 1;
        }
        catch(int e)
        {
            std::cout << "Entre un entier : ";
            valide = false;
            std::cin.clear();
            do
            {}while(std::cin.get() != '\n');
        }
    }while(!valide);
    return nombre;
}
