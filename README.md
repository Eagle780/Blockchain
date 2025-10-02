# Hash Generatorius

Ši programa realizuoja paprastą hash funkciją C++ kalba.
Funkcija paima įvestį, ją apdoroja blokais ir paverčia į pastovaus ilgio hash'ą.
Dirbome komandoje, vienas iš mūsų įdėją galvojo pats, kitas viską rašė su ChatGPT.

Toliau pateikiamas pseudo-kodas, aprašantis pagrindinius hash'o skaičiavimo etapus.

---

## Pseudo-kodas

### Rašant ranka

### 1. Teksto pavertimas į ASCII atitikmenis (`konvertuotiASCII`)

    def konvertuotiASCII(tekstas):
      tekstasASCII = ""
      for x in tekstas:
          tekstasASCII += str(ord(x))
      return tekstasASCII

### 2. ASCII pavertimas į 8 blokus po 8 skaičius (`paversti64`)

    def paversti64(tekstas):
        if ilgis(tekstas) liekana 8 != 0:
            prideti (8 - (ilgis(tekstas) liekana 8)) "0" simbolius
        dalys = []
        for i in range(0,ilgis(tekstas)/8):
            dalys.append(tekstas substring(i*8, 8))
        if size(dalys) > 8:
            skirtumas = size(dalys) - 8
                for i in range(0,skirtumas):
                    sum = sudeti(dalys[i], dalys[i+8])
                    dalys[i] = sum
                    if i == 7:
                      skirtumas = skirtumas - 8
                      i = 0
                pašalinti tiek dalių, kiek buvo už 8 pirmųjų
        if size(dalys) < 8:
            skirtumas = 8 - size(dalys)
            for i in range(0,skirtumas)
                dalys.append("00000000")
        dalysInt = []
        for d in dalys:
            dalysInt.append(to_integer(d))
        return dalysInt

### 3. sudėti du skaičius, išreikštus simboliais (`sudeti`)

    def sudeti(pirmas, antras):
        sum = to_integer(pirmas) + to_integer(antras)
        if sum >= 100000000:
            sum = sum liekana 100000000
        return sum

### 4. pagrindinė skaičių transformavimo funkcija (`vertimas`)

    def vertimas(dalys):
        for i from 0 to 3:
            dalys[i] += i * 1234
            dalys[i+4] += i * 4321
        for i from 0 to 3:
            dalys[i] += dalys[1]
            dalys[i+4] += dalys[4]
        for i from 0 to 7:
            dalys[i] = (dalys[i] + dalys[1]) / (i liekana 4 + 1)
        for i from 0 to 7:
            dalys[i] = dalys[i] * (i liekana 3 + 1)
            dalys[i] += dalys[i] / 10000
        for i from 0 to 7:
            while dalys[i] >= 100000000:
                dalys[i] = dalys[i] liekana 100000000
            while dalys[i] < 10000000:
                dalys[i] = dalys[i] * 10
        ats = ""
        for d in dalys:
            tekstas = to_string(d)
            for j from 0 to 7:
                if j liekana 4 == 0:
                    num = integer(tekstas[j]) + 6
                    ats += convert_to_hex_digit(num)
                else:
                    ats += tekstas[j]
        return ats

### naudojant ChatGPT

```Vartotojas parašo input'ą.
Inputas perskaitomas su getline().
Sukuriamas 32 baitų masyvas: unsigned char hash[32] = {0};

FOR kiekvienas simbolis input’e
    Paimti simbolio ASCII reikšmę → c
    Pasukti c bitus pagal simbolio poziciją → rotated
    Pridėti ASCII reikšmę prie hash[i mod 32] → hash[i % 32] = (hash[i % 32] + c) mod 256
    Apskaičiuoti pseudo-atsitiktinę poziciją: pos = (i * 7 + c) mod 32
    XOR rotated reikšmę su hash[pos] → hash[pos] = hash[pos] XOR rotated
    Pridėti ASCII reikšmę * 31 prie kito hash elemento → hash[(pos + 13) mod 32] = (hash[(pos + 13) mod 32] + c * 31) mod 256
END FOR

Norint įvertinti kodo efektyvumą, buvo atliekami eksperimentai.

## Eksperimentai

Buvo testuojami 4 failai:

- failas su vienu simboliu (test1),
- failas su daug (>1000) simbolių (test2),
- failas, kuris nuo praeito skiriasi vienu simboliu (test3),
- tuščias failas (test4).

Visi gauti hash'ai (rašant ranka):
test1 -> hash: f3587667a5157493d378b3648104a834b005b2807038c5409704d270d742f444
test2 -> hash: f5029677a4597276c93164769352a7117566c284f02885588693d693d579f315
test3 -> hash: d258d027f6179573b086c372c092b973b3676763d9259401e553e9159461d327
test4 -> hash: a0557569a5598650d36377918114b714a928f7657004e6409717c656d7177145

Visi gauti hash'ai (naudojant ChatGPT):
text1.txt file        -> hash: 333b032039bef039c6eb417c030c56591c782cd18c98698d18446fc3f02a7f93
text2.txt file        -> hash: 32ab04ab717ca70af359dd70eb7f4b3a38860b6f065b290238d36667ec01e47b
konstitucija.txt file -> hash: a68b86f57c42b9321bcbcc80c26ede09627675aa827b67b68fe4fdd06f2181fa
text3.txt file        -> hash: cb1719b3fd6c50651a7d15513aed34a03ea506b14d461a642c8d0ac9fb49784f

Kaip galima pastebėti žiūrint į hash'us, jie visi yra vienodo (64 simbolių) ilgio ir jie visi yra kardinaliai skirtingi.
Paleidus programą kelisi kartus ir naudojant tuos pačius failus, gaunami hash'ai nesiskiria.

Ekperimentai taip pat buvo atliekami su konstitucija.txt failu, iš jo paimant pasirinktą skaičių eilučių:

| eilutės    | 1         | 10        | 100       | 700       |
| ---------- | --------- | --------- | --------- | --------- |
| laikas (s) | 0.0003846 | 0.0004841 | 0.0011514 | 0.0081529 |

Kuriant skirtingo dydžio string poras buvo tikrinama, kaip dažnai vyksta kolizijos (lyginant 100,000 string porų):

| string ilgis | 10  | 100 | 500 | 1000 |
| ------------ | --- | --- | --- | ---- |
| kolizijos    | 0   | 0   | 0   | 0    |

Generuojant hash'us, neįvyko nei viena kolizija.

Taip pat tikrinama, ar prie teksto pridėjus "salt" hash'ai yra neatpažįstami:

"lietuva" - a9736795a3386904c394a68170556637a473c5799324d390d447812071199883
"lietuva123" - a9736795a3387149c301d21683486963a473c6759324d418d44781687119a351
"123lietuva" - f49283298251e328a185e438b341a6058442e772a310d753b418a412e110b470
```
