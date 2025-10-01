#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

string skaitytiFaila(string failas);
string konvertuotiASCII(string tekstas);
vector<int> paversti64(string tekstasASCII);
int sudeti(string pirmas, string antras);
void vertimas(vector<int> dalys);

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
    string tekstasASCII = konvertuotiASCII(tekstas);

    vector<int> dalys = paversti64(tekstasASCII);

    vertimas(dalys);

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

vector<int> paversti64(string tekstasASCII)
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
            if (i == 7)
            {
                skir -= 8;
                i == 0;
            }
        }
        for (int i = 0; i < skir; i++)
            dalys.pop_back();
    }
    else if (dalys.size() < 8)
    {
        int skir = 8 - dalys.size();
        for (int i = 0; i < skir; i++)
        {
            dalys.push_back("00000000");
        }
    }

    vector<int> dalysint;
    for (int i = 0; i < dalys.size(); i++)
        dalysint.push_back(stoi(dalys[i]));
    return dalysint;
}

int sudeti(string pirmas, string antras)
{
    int sum = stoi(pirmas) + stoi(antras);
    if (sum / 100000000 >= 1)
        sum = sum % 100000000;

    return sum;
}

void vertimas(vector<int> dalys)
{

    for (int i = 0; i < 8; i++)
    {
        cout << dalys[i] << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        dalys[i] += i * 1234;
        dalys[i + 4] += i * 4321;
    }
    for (int i = 0; i < 4; i++)
    {
        dalys[i] += dalys[3];
        dalys[i + 4] += dalys[7];
    }
    for (int i = 0; i < 8; i++)
    {
        dalys[i] = dalys[i] / (i % 4 + 1);
    }
    for (int i = 0; i < 8; i++)
    {
        dalys[i] = dalys[i] * (i % 3 + 1);
        dalys[i] += dalys[i] / 10000;
    }
    for (int i = 0; i < 8; i++)
    {
        if (dalys[i] / 100000000 >= 1)
        {
            dalys[i] = dalys[i] % 100000000;
        }
        if (dalys[i] / 10000000 == 0)
        {
            dalys[i] = dalys[i] * 10;
        }
    }
    cout << "---" << endl;
    string ats = "";
    for (int i = 0; i < 8; i++)
    {
        cout << dalys[i] << endl;
    }
}
