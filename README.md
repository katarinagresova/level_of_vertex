# level_of_vertex

Paralelní implementace výpočtu úrovně vrcholu s využitím Open MPI.

Vstupem je řetěz, který reprezentuje hodnoty uzlů binárního stromu zapsaného v poli. Znaky v řetězci indexujeme od 1 a uvažujme uzel, která má svou hodnotu na indexu i. Pak levý potomek tohoto uzlu má hodnotu na indexu 2*i a hodnota jeho pravého potomka se bude nacházet na indexu (2*i)+1.

Na výstupu jsou uzly ve stejném pořadí jako na vstupu, ale zapsané ve formátu "hodnota:úroveň" a oddelená je znakem "," (bez jakýchkoliv bílých znaků).

Příklad vstupu: ABCDEFG
Příklad výstupu: A:0,B:1,C:1,D:2,E:2,F:2,G:2

Spuštení: bash test.sh <vstupní_řetěz>
