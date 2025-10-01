#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

string skaitytiFaila(string failas);
string konvertuotiASCII(string tekstas);

int main(int argc, char **argv)
{
    string tekstas = "";
    if (argc == 2)
    {
        string failas = argv[1];
        tekstas = skaitytiFaila(failas);
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
        tekstas = a;
    }
    cout << tekstas << endl;
    string tekstasASCII = konvertuotiASCII(tekstas);
    cout << tekstasASCII << endl;

    return 0;
}

string skaitytiFaila(string failas)
{
    ifstream fd(failas);
    string tekstas = "";
    string eilute;
    while (getline(fd, eilute))
    {
        tekstas.append(eilute);
        tekstas.append(" ");
    }
    fd.close();
    return tekstas;
}

string konvertuotiASCII(string tekstas)
{
    string tekstasASCII = "";
    for (int i = 0; i < tekstas.length(); i++)
    {
        char x = tekstas.at(i);
        tekstasASCII.append(to_string(int(x)));
    }
    return tekstasASCII;
}
