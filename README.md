# Implementare-Printf
Aceasta este interpretarea mea la cerinta data.
La inceput mi-am declarat librariile de care am nevoie in implementarea problemei.
La inceputul functiei iocla_printf mi-am declarat toate variabilele pe care le-am folosit pe parcursul programului
Ideea dupa care am rezolvat problema a fost urmatoarea:
Am luat fiecare caracter din "format" si am verificat sa vad ce imi cere. Mai intai am inceput cu "%" si variabilele
apoi am trecut la caracterele speciale. La variabile le-am verificat in functie de indicele lor(d, u, x, c, s).

La d verific mai intai daca "intreg" este negativ apoi convertesc int-ul in char si il afisez.

La u castez int-ul in unsigned apoi il convertesc in char.

La x initializez vectorul pt forma binara a numarului cu 0 apoi verific da numarul este negativ sau pozitiv.Daca este
negativ il convertesc din zecimal in binar pe 32 de biti, neg apoi forma binara, ii mai adaug un bit apoi o convertesc
la forma hexa zecimala.Daca numarul e pozitiv e mai simplu pur si simplu impart la 16 si pastrez restul si asa il trec
in hexazecimal.

La c doar pun in prima pozitie din vectorul de char caracterul primit si apoi il printez

La s copiez in vectorul de char string-ul apoi il afisez

Si apoi daca primesc un al doile "%" il printez direct

Urmatoare categorie de delimitatori pe care am considerat-o este "\" pe care in functie de ce fel de input primeam il
printam imediat.
Tot aici am bagat si spatiul care urmeaza acelasi principiu.

Dupa ce am terminat aceste cerinte speciale de peintat am considerat ca orice alt input poate sa fie printat asa cum
il primesc.

La final eliberez memoria alocata dinamic si inchid lista de argumente.
