
Data Compression

Am implementat programul folosind o matrice de pixeli, fiecare pixel cu R-red
G-green si B-blue si un arbore cuaternar, cat si un vector in care stochez 
parcurgerea pe niveluri a arborelului.

Am initializat struct "pixel" cu Blue Green si Red in care stocam valorile 
culorilor.

Am initializat struct care retine mean, is_leaf, care e 1 daca nodul este frunza
si 0 daca nu, avg_R/G/B care retine valorile culorilor si nw/ne/se/sw_child care
retine adresa patratului de lungime n_prev/2.

Am initializat funtia "mean_calc" care calculeaza mean ul pentru un patrat dupa
instructiunile date.

Am initializat functia "buildTree" care primeste ca argument radacina arborelui
si matricea atasata, si construieste arborele cuaternar.

Am initializat functia "randuri" care calculeaza cate nivele are arborele 
cuaternar trecand prin fiecare nod pana cand ajunge la frunza cea mai departata
de radacina.

Am initializat functia "countBlock" care numara cate patrate sunt in arborele
cuaternar, trecand prin fiecare nod si numarandu-l.

Am initializat functia "maxLenght" care calculeaza lungimea laturii celui mai
mare patrat din arbore.

Am initializat functia "freeTree" care curata elementele arborelui 

Am initializat functiile "PrintVector" si "goDeeper" care printeaza elementele 
din arborele cuatermar, luati pe nivele de la stanga la dreapta

In functia main am declarat variabilele necesare cat am si initializat fisierul
de intrare. Am citit din fisierul numarul de pixeli ai pozei, apoi am introdus
in matrice valorile date. Cu ajutorul functiilor de mai sus am creeat arborele
cuaternar asociat pozei. In functie de cerinta introdusa am facut urmatoarele:

Pentru c1 am calculat numărul de niveluri din arborele cuaternar, numărul de 
blocuri din imagine pentru care scorul similarităt, ii pixelilor este mai mic 
sau egal decât factorul furnizat cat si dimensiunea laturii pătratului pentru 
cea mai mare zonă din imagine care a rămas nedivizată.

Pentru c2 am realizat compresia imaginei folosind algoritmul de compresie descris
si am introdus intr un fisier dat ca parametru imaginea compresata.

In final am eliberat toata memoria alocata.