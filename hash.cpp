#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void skaitytiFaila(string failas);

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        string failas = argv[1];
        skaitytiFaila(failas);
    }
    else if (argc > 3)
    {
        cout << "bloga ivestis" << endl;
    }
    else if (argc == 1)
    {
        string a;
        cout << "iveskite teksta, kuri norite uzsifruoti:" << endl;
        getline(cin, a);
        cout << a << endl;
    }
    return 0;
}

void skaitytiFaila(string failas)
{
    ifstream fd(failas);
    string eilute;
    while (getline(fd, eilute))
    {
        cout << eilute << " ";
    }
    cout << endl;
    fd.close();
}