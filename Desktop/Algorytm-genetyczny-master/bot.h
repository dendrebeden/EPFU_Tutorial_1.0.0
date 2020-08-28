#ifndef BOT_H
#define BOT_H
#include "klatka.h"
#include <fstream>
#include <iomanip>
class Bot
{
    Bot *next, *last;

    struct genome
    {
        int x, genomeID;
        genome *nextgenome;
        friend void showGenome();
    };
    genome *headgenome, *actgenome;

    Bot();
    ~Bot();
    int hp, id, x, y;
public:
int getGenome();
friend class Klatka;
friend bool cycle();
friend void setBotsList ();
friend void deleteBotsList ();
friend void showBotsList (Bot *act);
friend void showGenome(Bot *act);
friend void getStart();
friend void action();
friend int check();
friend void pointer(int step);
friend void move();
friend void setBot();
friend void setFood();
friend void setPoison();
friend void catchEatHeal();
friend void direct();
friend void atack();
friend void cross();
};


#endif // BOT_H
