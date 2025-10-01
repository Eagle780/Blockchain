#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

string skaitytiFaila(string failas);
string konvertuotiASCII(string tekstas);
vector<string> paversti64(string tekstasASCII);

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

    /*
    string binary = bitset<4>(15).to_string(); // to binary
    cout << binary << "\n";

    unsigned long decimal = bitset<4>(binary).to_ulong();
    cout << decimal << "\n";
    */

    if (tekstasASCII.length() < 64)
    {
        cout << "trumpesnis: " << tekstasASCII.length() << endl;
        int ilgis = tekstasASCII.length();
        for (int i = 0; i < (64 - ilgis); i++)
            tekstasASCII.append("0");
    }
    else if (tekstasASCII.length() > 64)
    {
        cout << "ilgesnis" << endl;
        vector<string> data = paversti64(tekstasASCII);
        for (int i = 0; i < data.size(); i++)
        {
            cout << data[i] << " " << data[i].length() << endl;
        }
        tekstasASCII = to_string(stoi(data[0]) + stoi(data[1]));
        cout << stoi(data[0]) << endl;
        cout << stoi(data[1]) << endl;
        cout << tekstasASCII << endl;
    }
    else if (tekstasASCII.length() == 64)
    {
        cout << "lygu" << endl;
    }
    cout << "teksto ascii ilgis: " << tekstasASCII.length() << endl;
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

vector<string> paversti64(string tekstasASCII)
{
    vector<string> dalys;
    if (tekstasASCII.length() % 8 != 0)
    {
        int ilgis = 8 - (tekstasASCII.length() % 8);
        for (int i = 0; i < ilgis; i++)
            tekstasASCII.append("0");
    }

    int ilgis = tekstasASCII.length() / 8;
    for (int i = 0; i < ilgis; i++)
    {
        dalys.push_back(tekstasASCII.substr(i * 8, 8));
    }

    for (int i = 0; i < dalys.size(); i++)
    {
        cout << dalys[i] << endl;
    }
    return dalys;
}
