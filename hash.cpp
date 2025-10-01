#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

string skaitytiFaila(string failas);
string konvertuotiASCII(string tekstas);
vector<string> paversti64(string tekstasASCII);
int sudeti(string pirmas, string antras);

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

    cout << tekstasASCII.length() << endl;

    vector<string> dalys = paversti64(tekstasASCII);

    cout << "daliu skaicius: " << dalys.size() << endl;
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

    if (dalys.size() > 8)
    {
        int skir = dalys.size() - 8;
        for (int i = 0; i < skir; i++)
        {
            int sum = sudeti(dalys[i], dalys[i + 8]);
            string naujas = to_string(sum);
            dalys[i] = naujas;
        }
        for (int i = 0; i < skir; i++)
            dalys.pop_back();
    }

    for (int i = 0; i < dalys.size(); i++)
    {
        cout << dalys[i] << endl;
    }

    return dalys;
}

int sudeti(string pirmas, string antras)
{
    int sum = stoi(pirmas) + stoi(antras);
    if (sum / 100000000 >= 1)
        sum = sum % 100000000;

    return sum;
}
