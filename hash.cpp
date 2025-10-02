#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <chrono>
#include <limits>
#include "timer.h"

using namespace std;

string skaitytiFaila(string failas);
string konvertuotiASCII(string tekstas);
vector<int> paversti64(string tekstasASCII);
int sudeti(string pirmas, string antras);
string vertimas(vector<int> dalys);
string skaitytiKonst(int n);
string sukurtiZodi(int n);
void kolizijos(int n);
void lavinosEfektas();

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
        string ats;
        srand(time(0));
        cout << "tikrinti Konstitucija?" << endl;
        cin >> ats;
        if (ats == "t")
        {
            int num;
            cout << "kiek eiluciu skaityti?" << endl;
            cin >> num;
            tekstas = skaitytiKonst(num);
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string a;
            cout << "iveskite teksta, kuri norite uzsifruoti:" << endl;
            getline(cin, a);
            tekstas = a;
        }
        cout << "tikrinti kolizijas?" << endl;
        cin >> ats;
        if (ats == "t")
        {
            int n;
            cout << "kokio ilgio string lyginti?" << endl;
            cin >> n;

            kolizijos(n);
        }
        cout << "tikrinti lavinos efekta?" << endl;
        cin >> ats;
        if (ats == "t")
        {
            lavinosEfektas();
        }
    }
    Timer t;
    string tekstasASCII = konvertuotiASCII(tekstas);

    vector<int> dalys = paversti64(tekstasASCII);

    string ats = vertimas(dalys);
    cout << ats << endl;
    cout << "ilgis: " << ats.length() << endl;
    cout << "praejes laikas: " << t.elapsed() << endl;
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
    tekstasASCII = to_string(tekstasASCII.length()) + to_string(tekstasASCII.length() - 1) + to_string(tekstasASCII.length() - 2) + tekstasASCII;
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
            int sum = sudeti(dalys[i], dalys[8]);
            string naujas = to_string(sum);
            dalys[i] = naujas;
            dalys.erase(dalys.begin() + 8);
            if (i == 7)
            {
                skir -= 8;
                i = -1;
            }
        }
    }
    else if (dalys.size() < 8)
    {
        int skir = 8 - dalys.size();
        for (int i = 0; i < skir; i++)
        {
            string pad = to_string(tekstasASCII.length());
            while (pad.length() < 8)
                pad = "0" + pad;
            dalys.push_back(pad);
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

string vertimas(vector<int> dalys)
{
    string salt = "asdfghjkl";
    for (int i = 0; i < 8; i++)
    {
        dalys[0] += dalys[i];
        if (dalys[0] / 100000000 >= 1)
        {
            dalys[0] = dalys[0] % 100000000;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        dalys[i] += i * 1234;
        dalys[i + 4] += i * 4321;
    }
    for (int i = 0; i < 4; i++)
    {
        dalys[i] += dalys[1];
        dalys[i + 4] += dalys[4];
    }
    for (int i = 0; i < 8; i++)
    {
        dalys[i] += dalys[0];
        dalys[i] = dalys[i] / (i % 4 + 1);
    }
    for (int i = 0; i < 8; i++)
    {
        dalys[i] = dalys[i] * (i % 3 + 1);
        dalys[i] += dalys[i] / 10000;
    }
    for (int i = 0; i < 8; i++)
    {
        while (dalys[i] / 100000000 >= 1)
        {
            dalys[i] = dalys[i] % 100000000;
        }
        while (dalys[i] / 10000000 == 0)
        {
            dalys[i] = dalys[i] * 10;
        }
    }
    for (int i = 0; i < 8; i++)
        dalys[i] ^= (dalys[(i + 1) % 8] >> (i + 3));

    for (int i = 0; i < dalys.size(); i++)
    {
        dalys[i] ^= (int(salt[i % salt.size()]) << (i % 4));
    }

    string ats = "";
    for (int i = 0; i < 8; i++)
    {
        string dalis = to_string(dalys[i]);
        for (int j = 0; j < 8; j++)
        {
            if (j % 4 == 0)
            {
                int num = int(dalis[j]) - 48 + 6;
                if (num == 10)
                    ats.append("a");
                else if (num == 11)
                    ats.append("b");
                else if (num == 12)
                    ats.append("c");
                else if (num == 13)
                    ats.append("d");
                else if (num == 14)
                    ats.append("e");
                else if (num == 15)
                    ats.append("f");
                else
                    ats.append(to_string(num));
            }
            else
            {
                ats.append(to_string(dalis[j] - 48));
            }
        }
    }
    return ats;
}

string skaitytiKonst(int n)
{
    ifstream fd("konstitucija.txt");
    string tekstas = "";
    string eilute;
    for (int i = 0; i < n; i++)
    {
        getline(fd, eilute);
        tekstas.append(eilute);
    }
    return tekstas;
}

string sukurtiZodi(int n)
{
    static const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    string zodis = "";
    for (int j = 0; j < n; j++)
    {
        zodis.push_back(chars[rand() % chars.size()]);
    }
    return zodis;
}

void kolizijos(int n)
{
    int kolizijos = 0;
    for (int i = 0; i < 100000; i++)
    {
        string s1 = sukurtiZodi(n);
        string s2 = sukurtiZodi(n);

        string k1 = konvertuotiASCII(s1);
        string k2 = konvertuotiASCII(s2);

        vector<int> d1 = paversti64(k1);
        vector<int> d2 = paversti64(k2);

        string h1 = vertimas(d1);
        string h2 = vertimas(d2);

        if (h1 == h2)
            kolizijos++;
    }
    cout << "koliziju skaicius: " << kolizijos << endl;
}

void lavinosEfektas()
{
    for (int i = 0; i < 1; i++)
    {
        string s1 = sukurtiZodi(100);
        string s2 = s1;
        static const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        while (s1[s1.length() - 1] == s2[s2.length() - 1])
        {
            s2[s2.length() - 1] = chars[rand() % chars.size()];
        }

        cout << "---" << endl;
        cout << s1 << endl;
        cout << s2 << endl;

        string k1 = konvertuotiASCII(s1);
        string k2 = konvertuotiASCII(s2);

        vector<int> d1 = paversti64(k1);
        vector<int> d2 = paversti64(k2);

        string h1 = vertimas(d1);
        string h2 = vertimas(d2);

        cout << "hashai:" << endl;
        cout << h1 << endl;
        cout << h2 << endl;

        float proc = 0;
        for (int j = 0; j < 64; j++)
        {
            if (h1[j] == h2[j])
            {
                proc++;
            }
        }
        proc = proc / 64.0 * 100.0;
        cout << "dvieju hash'u panasumas: " << proc << endl;
    }
}
