# Hash Generatorius

Ši programa realizuoja paprastą hash funkciją C++ kalba.
Funkcija paima įvestį, ją apdoroja blokais ir paverčia į pastovaus ilgio hash'ą.

Toliau pateikiamas pseudo-kodas, aprašantis pagrindinius hash'o skaičiavimo etapus.

---

## Pseudo-kodas

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


Norint įvertinti kodo efektyvumą, buvo atliekami eksperimentai.

## Eksperimentai

