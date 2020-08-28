#ifndef KLATKA_H
#define KLATKA_H

#include "bot.h"

class Klatka
 {
    private: bool food, poison, bot;
    int x, y, id;

    public:
    friend  bool cycle();
    friend void setKlatkaTab ();
    friend void deleteKlatkaTab();
    friend void showKlatkaTab();
    friend void getStart();
    friend void showKlatkaState();
    friend int check();
    friend void move();
    friend void action();
    friend void setBot();
    friend void setFood();
    friend void setPoison();
    friend void catchEatHeal();
    friend void direct();
    friend void atack();
    friend void cross();
};


#endif // KLATKA_H
