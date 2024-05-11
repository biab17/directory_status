#include"grafneorientat.h"

int main()
{
    Nod_t noduri[4];
    noduri[0].cheie = 1;
    noduri[1].cheie = 2;
    noduri[2].cheie = 3;
    noduri[3].cheie = 4;

    Graf_t graf;
    initializare(&graf);

    insereazaNod(&graf, noduri[0]);
    insereazaNod(&graf, noduri[1]);
    insereazaNod(&graf, noduri[2]);
    insereazaNod(&graf, noduri[3]);

    Arc_t arce[3];
    arce[0].nod1 = noduri[0];
    arce[0].nod2 = noduri[1];
    arce[1].nod1 = noduri[1];
    arce[1].nod2 = noduri[3];
    arce[2].nod1 = noduri[0];
    arce[2].nod2 = noduri[3];

    insereazaArc(&graf, arce[0]);
    insereazaArc(&graf, arce[1]);
    insereazaArc(&graf, arce[2]);

    afiseazaGraf(&graf);

    suprimaArc(&graf, arce[1]);

    afiseazaGraf(&graf);

    insereazaArc(&graf, arce[1]);

    suprimaNod(&graf, noduri[3].cheie);

    afiseazaGraf(&graf);

    return 0;
}
