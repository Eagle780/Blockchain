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

```PRADŽIA
    Paklausia vartotojo, kokiu būdu įves input'ą: skaitant failą ar įvedant ranka?
    Jei rankinis įvedimas:
        Nuskaito input'ą su getline()
    Jei failas:
        Atidaro failą
        Nuskaito visas eilutes ir sujungia į vieną string
        Uždaro failą
    Pabaiga jei

    Inicializuoja 4 lane su skirtingais pradžios seed'ais (out[4])

    FOR kiekvienas simbolis input'e
        c = ASCII simbolio reikšmė
        lane = i mod 4

        out[lane] = out[lane] XOR (c * 0x100000001b3)
        out[lane] = pasuka bitus į kairę (i*7 mod 64)
        out[lane] = out[lane] * 0xff51afd7ed558ccd
        out[lane] = out[lane] XOR (out[lane] >> 32)

        other = (lane + 1) mod 4
        out[other] = out[other] XOR pasuka bitus (c + out[lane], i*13 mod 64)
        out[other] = out[other] * 0x9e3779b97f4a7c15
    END FOR

    FOR round = 0 to 3
        FOR j = 0 to 3
            x = out[j]
            x = x XOR pasuka bitus (out[(j+1) mod 4], j*17 + round*11)
            x = x * 0xc2b2ae3d27d4eb4f
            x = x XOR (x >> 29)
            out[j] = x
        END FOR
    END FOR

    Atspausdina out[0..3] kaip 64 simbolių ilgio hex eilutę
PABAIGA

```

Norint įvertinti kodo efektyvumą, buvo atliekami eksperimentai.

## Eksperimentai

### Testiniai failai, išvedimo dydis, determiniškumas

1. Paruošti šie testiniai failai:

- 2 skirtingi failai su vienu simboliu (a.txt, b.txt)
- failas su >1000 atsitiktinių simbolių (random1.txt)
- failai su >1000 atsitiktinių simbolių, besiskiriančių tik vienu simboliu (random2.txt, random2_mod.txt)
- tuščias failas (empty.txt)

2. Išvedimo dydžio tikrinimas (be ChatGPT)

| Failas        | Hash                                                             |
| ------------- | ---------------------------------------------------------------- |
| a.txt         | e1186393c873a325d192f668a402e337a6366579c0018749b790e597e654f095 |
| b.txt         | e116c525c874c719d1939888a402f211a6358529c0008651b790d242e6557194 |
| test2.txt     | 9528a210c524b900d85383997757f1638158e0929326a545c573c531e1508806 |
| test2copy.txt | d5239399a7969465d23693777901f677c300a4659172f89797609893d022a988 |
| test3.txt     | b39582238613f30882479399b128e634b9919039f135b012c770b946a8546478 |
| tuscias.txt   | f724a466c960e5708445c429d894f126c1459821b639c8997027b467c551e837 |

3. Išvedimo dydžio tikrinimas (su ChatGPT)

| Failas          | Hash                                                             |
| --------------- | ---------------------------------------------------------------- |
| a.txt           | 43d5f88c36d90c1fd15c9a188a206b1820a9c17f817f562bdaa8c3b226b2b757 |
| b.txt           | dc473aadc7041b4c784e84c3b29f49861de8031a5bd557f22808a50c8c1dbeeb |
| random1.txt     | a753a39880b5adbc474eef9f49b29491c4b3ead90c36c9ee2733c8a032a021ff |
| random2.txt     | 49939b6a15fe4f8468c66b5a61a6fefbc71958b3f99b84d06b73afc77c825653 |
| random2_mod.txt | 68142adf8e9646a09f82e07af09d8e8b44d0614ac565a3ee8c27cc40d63e4572 |
| empty.txt       | 65d37efc8d7fbe74319f8f97dd570b623fca7827f232485138b2208970d43764 |

Kaip galima pastebėti žiūrint į hash'us, jie visi yra vienodo (64 simbolių) ilgio ir jie visi yra skirtingi.
Paleidus programą kelis kartus ir naudojant tuos pačius failus, gaunami hash'ai nesiskiria.

### Efektyvumas

Ekperimentai taip pat buvo atliekami su konstitucija.txt failu, iš jo paimant pasirinktą skaičių eilučių:

1. Efektyvumas pagal eilutes (be ChatGPT)

| eilutės     | 1      | 2      | 4      | 8     | 16     | 32     | 64     | 128    | 256    | 512    | 789    |
| ----------- | ------ | ------ | ------ | ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| laikas (ms) | 0.3574 | 0.4214 | 0.4163 | 0.441 | 0.7435 | 1.4632 | 4.4327 | 23.929 | 132.75 | 750.47 | 1888.2 |

2. Efektyvumas pagal eilutes (su ChatGPT)

| eilutės     | 1      | 2      | 4      | 8     | 16     | 32     | 64     | 128    | 256    | 512    | 789    |
| ----------- | ------ | ------ | ------ | ----- | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| laikas (ms) | 0.0016 | 0.0021 | 0.0034 | 0.006 | 0.0162 | 0.0299 | 0.0602 | 0.1507 | 0.3163 | 0.6988 | 1.1197 |

Kaip galima pastebėti iš rezultatų, su ChatGPT daryta hash'avimo funkcija yra žymiai spartesnė.

### Kolizijų paieška

Kuriant skirtingo dydžio string poras buvo tikrinama, kaip dažnai vyksta kolizijos (lyginant 100,000 string porų):

1. Kolizijos (be ChatGPT)

| string ilgis | 10  | 100 | 500 | 1000 |
| ------------ | --- | --- | --- | ---- |
| kolizijos    | 0   | 0   | 0   | 0    |

2. Kolizijos (su ChatGPT)

| string ilgis | 10  | 100 | 500 | 1000 |
| ------------ | --- | --- | --- | ---- |
| kolizijos    | 0   | 0   | 0   | 0    |

Generuojant hash'us, neįvyko nei viena kolizija.

### Lavinos efektas

1. Kolizijos (be ChatGPT)

Sugeneravus 100,000 porų, kurios skiriasi tik vienu simboliu, buvo gauti tokie rezultatai:

Bit level differences:
Min: 42.968
Max: 100
Avg: 65.324
Hex level differences:
Min: 0
Max: 100
Avg: 28.914

2. Kolizijos (su ChatGPT)

- a.txt:
  Bit level differences:
  Min: 92
  Max: 163
  Avg: 128.004
  Hex level differences:
  Min: 50
  Max: 64
  Avg: 59.9988

  - b.txt:
    Bit level differences:
    Min: 93
    Max: 164
    Avg: 127.987
    Hex level differences:
    Min: 50
    Max: 64
    Avg: 60.0002

  - random2.txt:
    Bit level differences:
    Min: 92
    Max: 163
    Avg: 127.96
    Hex level differences:
    Min: 49
    Max: 64
    Avg: 59.9957

  - random2_mod.txt:
    Bit level differences:
    Min: 93
    Max: 164
    Avg: 127.993
    Hex level differences:
    Min: 50
    Max: 64
    Avg: 59.993

### Negrįžtamumo demonstracija

Taip pat tikrinama, ar prie teksto pridėjus "salt" hash'ai yra neatpažįstami:

1. Input = salt (be ChatGPT)

Input: password123
Salt: JhswNLCXNouzU8XR
Hash(input + salt):

Changed salt: Pkq6ExcSwE9Tc3sH
Hash(input + new salt):

2. Input = salt (su ChatGPT)

Input: password123
Salt: JhswNLCXNouzU8XR
Hash(input + salt): e9ad02959c3107392b032354d37906bf6c0563096e075f704039d4ce16862f8a

Changed salt: Pkq6ExcSwE9Tc3sH
Hash(input + new salt): 375041e630e752cc2a7bf6a144ec7a83f5b3c349cee8baccc912f570d5872abd
Hash: e9ad02959c3107392b032354d37906bf6c0563096e075f704039d4ce16862f8a

Input'as identiškas, o hash'ai kardinaliai skiriasi.

### Išvados

Atlikti eksperimentiniai tyrimai parodė, kad:
Be ChatGPT daryta funkcija panaši į tą, krui daryta su ChatGPT tuo, kad abi duoda tokio pat dydžio hash'us, kurie yra tokie pat tokiai pat įvesčiai.
Tačiau be ChatGPT daryta funckija rodo tokius trukumus:
Daug ilgesnis veikimo laikas, lavinos efektas parodė, kad kartais yra pasikartojančių hash'ų.
