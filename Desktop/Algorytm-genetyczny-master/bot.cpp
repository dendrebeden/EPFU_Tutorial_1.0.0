#include <iostream>
#include <fstream>
#include <iomanip>
#include "klatka.h"
#include "algorytm.h"
#include "bot.h"
#include "interfejs.h"


Bot::Bot()
{
    int idGenome = 0;
    hp = 50;
    headgenome = new genome;
    actgenome = headgenome;
    actgenome->x = rand()%64;
    actgenome->genomeID = idGenome;
    idGenome++;
   for (int i=0; i<99; i++)
   {
        actgenome->nextgenome = new genome;
        actgenome = actgenome->nextgenome;
        actgenome->x = rand()%64;
        actgenome->genomeID = idGenome;
        idGenome++;
        actgenome->nextgenome = NULL;
   }
}

Bot::~Bot()
{
    actgenome = headgenome;
    while (actgenome!=NULL)
    {
        genome *help;

        help = actgenome;
        actgenome = actgenome->nextgenome;

        delete help;
    }
}

int Bot::getGenome()
{

    return this->actgenome->x;
}

using namespace std;
