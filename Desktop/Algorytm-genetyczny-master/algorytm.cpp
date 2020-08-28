#include <iostream>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include "klatka.h"
#include "algorytm.h"
#include "bot.h"
#include "interfejs.h"

Bot *head,  *act, *tail;
int w=25, k=25, bots, poisonNumber = 150, foodNumber =150, poisons, foods, X, Y, t, t1, t2, pokolenie, itarations=1;
double roundTime = 100000;
Klatka **klatka;

using namespace std;
//FUNKCJE KONSOLOW (POMOCNICZE)
///////////////////////////////////////////
//wyswietla liste klatek
void showBotsList(Bot *act)
{
    act = head;

    while (act!=tail)
    {
        cout << "ID" << act->id << "   " << act->hp << " <---zdrowie "<< act->x << "x " << act->y << "y  " << endl;
        act = act->next;
    }
    act = tail;
    cout << "ID" << act->id << "  "<< act->x << "x " << act->y << "y  "<< endl;

}

//wyswietla liste genomu dla kazdego osobnika
void showGenome( Bot *act )
{
    int number=0;
    act = head;
    while(act!=tail)
    {


        cout << endl <<  endl << act->id << " <-----  id of bot" << endl << endl;
        cout << act->headgenome->x << "  PIEWRSZY GENOM " << endl;
        act->actgenome = act->headgenome;
        while(act->actgenome!=NULL)
        {    number++;
            cout << act->actgenome->x << "    ";
            if(act->actgenome->genomeID%8==0) cout << endl;
            act->actgenome = act->actgenome->nextgenome;
        }
        cout << number << "<----- ilosc genomow" <<  endl;
        number = 0;
        act->actgenome = act->headgenome;
        act = act->next;
    }


    act = tail;
    act->actgenome = act->headgenome;

    cout << act->id << " <-----  id of bot" << endl << endl;
    cout << act->headgenome->x << "  PIEWRSZY GENOM " << endl;
    while(act->actgenome!=NULL)
    {
        cout << act->actgenome->x <<  "    ";
        number++;
        if((act->actgenome->genomeID)%8==0) cout << endl;
        act->actgenome = act->actgenome->nextgenome;
    }
    cout << number << "<----- ilosc genomow" <<  endl;
    number = 0;
    act->actgenome = act->headgenome;
    cout << endl << endl;
}

//wyswietla w ktorych klatkach jest jedzenia i jad
void showKlatkaState()
{
    for (int i=0; i<w; i++)
    {
        for (int j=0; j<k; j++)
        {
            if(klatka[i][j].food==true) cout << " F ";
            else if(klatka[i][j].poison==true) cout << " P ";
            else if(klatka[i][j].bot==true) cout << " X ";
            else cout << "   ";
        }
        cout << endl;
    }
}
///////////////////////////////////////////

//tworzy liste 2 kierunkowa osobnikow
void setBotsList()
{

    int id = 1;
    head = new Bot;
    act = head;
    act->id = id;
    id++;
    head->next = NULL;
    for (int i = 0; i < bots-1; i++)
    {

        act->next = new  Bot;
        act->next->last = act;
        act = act->next;
        act->id = id;
        id++;
        act->next = NULL;

    }

    tail = act;
    tail->next = head;
    head->last = tail;

    ifstream fileRead ("genome.txt");
    if(fileRead.good())
    {
        string help;
        act = head;
        while(act!=tail)
        {

            act->actgenome = act->headgenome;
            while(act->actgenome!=NULL)
            {
                getline(fileRead, help);
                act->actgenome->x = atoi(help.c_str());
                act->actgenome = act->actgenome->nextgenome;
            }
            act->actgenome = act->headgenome;
            act = act->next;
        }
        act = tail;

        act->actgenome = act->headgenome;
        while(act->actgenome!=NULL)
        {
            getline(fileRead, help);
            act->actgenome->x = atoi(help.c_str());
            act->actgenome = act->actgenome->nextgenome;
        }
    }
    fileRead.close();
}


//usuwa liste 2 kierunkowa osobnikow
void deleteBotsList()
{

    act = head;
    while(act->next!=head)
    {
        act = act->next;
        delete act->last;
    }
    delete tail;
}

//tworzy tablice dynamiczna **klatka
void setKlatkaTab()
{
    int id=1;
    klatka = new Klatka *[w];
    for (int i=0; i<w; i++)
    {
        *(klatka+i) = new Klatka [k];
        for (int j=0; j<k; j++)
        {
            klatka[i][j].id=id;
            id++;
            klatka[i][j].x = j;
            klatka[i][j].y = i;
        }
    }
}

//usuwa tablice dynamiczna **klatka
void deleteKlatkaTab()
{

    for (int i=0; i<w; i++)
    {
        for (int j=0;  j<k; j++)
        {
            klatka[i][j].bot = false;
            klatka[i][j].food = false;
            klatka[i][j].poison = false;
        }
        delete []klatka[i];
    }
    delete   []klatka ;
}

//losuje klatki dla jadu
void setPoison()
{
    int  x, y;
    while (poisons!=poisonNumber)
    {
        x = rand()%k;
        y = rand()%w;
        while(klatka[y][x].food||klatka[y][x].poison||klatka[y][x].bot)
        {
            x = rand()%k;
            y = rand()%w;
        }
        klatka[y][x].poison = true;
        poisons++;
    }
}

//losuje klatki dla jedzenie
void setFood()
{
    int x, y;
    while (foods!=foodNumber)
    {
        x = rand()%k;
        y = rand()%w;
        while(klatka[y][x].food||klatka[y][x].poison||klatka[y][x].bot)
        {
            x = rand()%k;
            y = rand()%w;
        }
        klatka[y][x].food = true;
        foods++;
    }
}

//losuje klatki dla botow
void setBot()
{
    int x, y;

    //losowanie wspolrzednych dla obiektow listy bots
    act = head;
    while (act->next!=head)
    {
        x = rand()%k;
        y = rand()%w;
        while(klatka[y][x].food||klatka[y][x].poison||klatka[y][x].bot)
        {
            x = rand()%k;
            y = rand()%w;
        }
        klatka[y][x].bot = true;
        act->x = x;
        act->y = y;
        act = act->next;
    }

    //losowanie dla ogona listy bots
    act = tail;
    x = rand()%k;
    y = rand()%w;
    while(klatka[y][x].food||klatka[y][x].poison||klatka[y][x].bot)
    {
        x = rand()%k;
        y = rand()%w;
    }
    klatka[y][x].bot = true;
    act->x = x;
    act->y = y;
}

//losuje klatki dla botow
void getStart()
{

    setKlatkaTab();
    setBotsList();
    showGenome(act);

    //oczyszcza wszystkie klatki
    for (int i=0; i<w; i++)
    {
        for (int j=0; j<k; j++)
        {
            klatka[i][j].food = false;
            klatka[i][j].bot = false;
            klatka[i][j].poison = false;
        }
    }

    setFood();
    setPoison();
    setBot();

    cout << poisons << " <------ ilosc klatek z jadem   " << foods << " <----- ilosc klatek z jedzeniem    " << bots << " <----------ilosc botow" << endl;

    action();

    cross();

    cout << "--------------------------------- tu sie konczy ---------------------------------" << endl;
    showBotsList(act);
    showGenome( act );
    cout << "--------------------------------- tu sie konczy ---------------------------------" << endl;
    poisons = 0;
    foods = 0;

    deleteBotsList();

    deleteKlatkaTab();
}

//uruchamia symulacje
void action()
{
    int helpbots, botsCounter;
    helpbots = bots;
    act = head;
    while(bots>(helpbots/10))
    {
        botsCounter = bots;
        cout << endl << endl;
        showKlatkaState();
        usleep(roundTime);
        system("clear");
        cout << endl << endl;
        ////////////////////////////////////////////////////////////////////////////////////
        /////BOT COS ROBI
        ///
        for (int i = 0; i < botsCounter; i++)  {

            //cout << act->getGenome() << "  genom!!!  " << act->id << " ID BOTA" << endl;

            if(act->hp<=0)  {
                Bot *helpbot;
                int x, y;
                x = act->x;
                y = act->y;

                helpbot = act ;
                klatka[y][x].bot = false;

                act->next->last = act->last;
                act->last->next = act->next;

                act = act->last;
                delete helpbot;
                bots--;

            }

            else  {

                if (act->getGenome()<8)  {
                    cout << "move" << endl;
                    move();
                    pointer(check());
                }
                else if (7<act->getGenome()&&act->getGenome()<16) {
                    cout << "catchEatHeal" << endl;
                    catchEatHeal();
                    pointer(check());
                }
                else if(15<act->getGenome()&&act->getGenome()<24) {
                    cout << "look" << endl;
                    pointer(check());
                }
                else if(23<act->getGenome()&&act->getGenome()<32) {
                    cout << "atack" << endl;
                    atack();
                    pointer(check());
                }
                else  {
                    cout << "moveGenomPointer" << endl;
                    pointer(act->getGenome() - check());
                }

                act->hp--;
            }
            cout << " ------------------------------------   " << endl;

            ////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////
            act = act->next;
            tail = act->last;
            head = act;

            if (bots <= 10) break;
        }
        setFood();
        setPoison();
    }
    showBotsList(act);
    cout << poisons << " <------ ilosc klatek z jadem   " << foods << " <----- ilosc klatek z jedzeniem    " << bots << " <----------ilosc botow" << endl;

    cout << " ------------------------------------   " << endl;
}

//sprawdza co bot spotyka po drodze (0 - nie ma takiego pola, 1 - bot, 2 - jedzenie, 3 -jad, 4 - nic)
int check()
{
    int x, y;
    x = act->x;
    y = act->y;
    switch ((8+act->getGenome())%8)
    {
    case 0:
    {
        //  cout << " CASE 0  "<< endl;

        if(act->y==0)
        {
            return 0;
            break;
        }
        else if(klatka[y-1][x].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y-1][x].food)
        {
            return 2;
            break;
        }
        else if(klatka[y-1][x].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 1:
    {
        //     cout << " CASE1 "<< endl;

        if(act->y==0||act->x==(k-1))
        {
            return 0;
            break;
        }
        else if(klatka[y-1][x+1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y-1][x+1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y-1][x+1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 2:
    {
        //   cout << " CASE2 "<< endl;

        if(act->x==(k-1))
        {
            return 0;
            break;
        }
        else if(klatka[y][x+1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y][x+1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y][x+1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 3:
    {
        //   cout << " CASE3 "<< endl;

        if(act->y==(w-1)||act->x==(k-1))
        {
            return 0;
            break;
        }
        else if(klatka[y+1][x+1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y+1][x+1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y+1][x+1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 4:
    {
        // cout << " CASE4 "<< endl;

        if(y==(w-1))
        {
            return 0;
            break;
        }
        else if(klatka[y+1][x].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y+1][x].food)
        {
            return 2;
            break;
        }
        else if(klatka[y+1][x].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 5:
    {
        // cout << " CASE5 "<< endl;

        if(act->x==0||act->y==(w-1))
        {
            return 0;
            break;
        }
        else if(klatka[y+1][x-1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y+1][x-1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y+1][x-1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 6:
    {
        //cout << " CASE6 "<< endl;

        if(act->x==0)
        {
            return 0;
            break;
        }
        else if(klatka[y][x-1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y][x-1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y][x-1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    case 7:
    {
        //    cout << " CASE7 "<< endl;

        if(act->x==0||act->y==0)
        {
            return 0;
            break;
        }
        else if(klatka[y-1][x-1].bot)
        {
            return 1;
            break;
        }
        else if(klatka[y-1][x-1].food)
        {
            return 2;
            break;
        }
        else if(klatka[y-1][x-1].poison)
        {
            return 3;
            break;
        }
        else
            return 4;
        break;
    }
    }
    return 0;
}

//przesuwanie sie wskaznika genoma (1 - bot, 2- jedzenie, 3 - jad, 4 - nic)
void pointer(int step)
{
    if(step==0) step++;
    for(int i=0; i<step; i++)
    {
        act->actgenome = act->actgenome->nextgenome;
        if(act->actgenome==NULL) act->actgenome = act->headgenome;
    }
}

//funkcja zmiany polozenia bota
void move()
{
    //cout << " move " << endl;
    //cout << check() << endl;

    direct();

    int x, y;
    x = act->x;
    y = act->y;
    if(check()==2)
    {
        if(act->hp<=80)
            act->hp = act->hp + 20;
        else act->hp = 100;

        klatka[Y][X].food = false;
        klatka[y][x].bot = false;
        klatka[Y][X].bot = true;

        act->x = X;
        act->y = Y;
        foods--;
    }

    else if(check()==3)
    {
        act->hp = act->hp - 20;
        klatka[Y][X].poison = false;
        poisons--;
    }

    else if(check()==4)
    {
        int x, y;
        x = act->x;
        y = act->y;
        klatka[y][x].bot = false;
        klatka[Y][X].poison = false;
        klatka[Y][X].bot = true;
        act->x = X;
        act->y = Y;
    }
}

//wyznacza kierunek w ktory patzry bot(X i Y - wspolrzedne klatki, na ktora patrzy bot)
void direct()
{

    int x, y;
    x = act->x;
    y = act->y;
    switch(act->getGenome()%8)
    {
    case 0:
    {
        X = x;
        Y = y-1;
        break;
    }
    case 1:
    {
        X = x+1;
        Y = y-1;
        break;
    }
    case 2:
    {
        X = x+1;
        Y = y;
        break;
    }
    case 3:
    {
        X = x+1;
        Y = y+1;
        break;
    }
    case 4:
    {
        X = x;
        Y = y+1;
        break;
    }
    case 5:
    {
        X = x-1;
        Y = y+1;
        break;
    }
    case 6:
    {
        X = x-1;
        Y = y;
        break;
    }
    case 7:
    {
        X = x-1;
        Y = y-1;
    }
    }
}

//zamienia jad na jedzenie, zjada jedzenie, leczy bota (wylaczylem)
void catchEatHeal()
{
    //  cout << " catchEatHeal()  " << endl;
    //cout << check() << endl;

    direct();

    int x, y;
    x = act->x;
    y = act->y;
    ///ta opcja zostala usunieta poniewaz osobniki po pewnym pokoleniu
    /// zaczynaja rekurencyjnie sie leczyc i program leci w kolko
    /*  if(check()==1)
        {
            Bot *helpact;
            helpact = head;

            while((helpact->x!=X)&&(helpact->y!=Y))
            {
                helpact = helpact->next;
            }

            if(helpact->hp<=90)
            helpact->hp = helpact->hp + 10;
            else helpact->hp = 100;
        }
        else*/
    if(check()==2)
    {
        if(act->hp<=80)
            act->hp = act->hp + 20;
        else act->hp = 100;

        klatka[Y][X].food = false;
        foods--;
    }
    else if(check()==3)
    {
        if(act->hp<=90)
            act->hp = act->hp + 10;
        else act->hp = 100;

        klatka[Y][X].poison = false;
        poisons--;
    }
}

//atakuje bota lub niszczy jad albo jedzenie
void atack()
{
    // cout << " atack()  " << endl;
    //  cout << check() << endl;

    direct();
    if(check()==1)
    {
        Bot *helpact;
        helpact = head;

        while((helpact->x!=X)&&(helpact->y!=Y))
        {
            helpact = helpact->next;
        }

        if(helpact->hp>=10) {
            if(act->hp<=90)  act->hp = act->hp +10;
            else act->hp = 100;

            helpact->hp = helpact->hp - 10;
        }
        else
        {
            helpact->hp = 0;
            if(act->hp<=90)  act->hp = act->hp +10;
            else act->hp = 100;
        }
    }
    else if(check()==2)
    {
        klatka[Y][X].food = false;
        foods--;
    }
    else if(check()==3)
    {
        klatka[Y][X].poison = false;
        poisons--;
    }
}

//krzyzowanie sie i mutacja botow
void cross()
{

    int amount, amountGenomes=0, mutationChance=0;
    Bot *parent1, *parent2;

    act = head;
    act->actgenome = act->headgenome;

    // wyznacza ilosc genomow
    while(act->actgenome!=NULL)
    {
        amountGenomes ++;
        act->actgenome = act->actgenome->nextgenome;
    }

    //otwiera plik do zapisu
    ofstream file ("genome.txt");
    for(int i=0; i<bots/2; i++)
    {

        parent1 = act;
        parent2 = act->next;

        //zapisuje dzieci
        //////////////////////////////////////////////////////
        for(int j = 0 ; j < 18 ; j++)
        {

            parent1->actgenome = parent1->headgenome;
            parent2->actgenome = parent2->headgenome;

            amount = rand()%(amountGenomes-1) + 1;

            //czesc genomu od 1 rodzica
            for( int k = 0 ; k < amount ; k++)
            {

                file << parent1->actgenome->x << endl;

                parent1->actgenome = parent1->actgenome->nextgenome;
                parent2->actgenome = parent2->actgenome->nextgenome;
            }

            //czesc genomu od 2 rodzica
            while( parent2->actgenome != NULL )
            {

                file << parent2->actgenome->x << endl;

                parent2->actgenome = parent2->actgenome->nextgenome;
            }


            //////////////////////////////////////////////////////
        }

        //zapisuje rodzicow
        //////////////////////////////////////////////////////
        parent1->actgenome = parent1->headgenome;
        parent2->actgenome = parent2->headgenome;

        while( parent1->actgenome != NULL )
        {

            mutationChance = rand()%amountGenomes;
            if (mutationChance == 0)
            {
                file << rand()%64 << endl;
            }

            else
            {
                file << parent1->actgenome->x << endl;
            }

            parent1->actgenome = parent1->actgenome->nextgenome;
        }

        while( parent2->actgenome != NULL )
        {

            mutationChance = rand()%amountGenomes;
            if (mutationChance == 0)
            {
                file << rand()%64 << endl;
            }

            else
            {
                file << parent2->actgenome->x << endl;
            }

            parent2->actgenome = parent2->actgenome->nextgenome;
        }
        //////////////////////////////////////////////////////
        act = act->next->next; //przeskakuje na nastepna pare botow

    }
    file.close();
}

bool cycle ()
{

    for(int i = 0; i<itarations; i++)
    {
        t1 = clock();
        bots= 100;
        getStart();
        pokolenie++;
        t2 = clock();

        t = t2 - t1;

        cout << t << " <--- czas zycia pokolenia    " << endl;
        cout << pokolenie << "  <--- numer pokolenia     " << endl;

        ofstream file ("timeOfLife.txt", ios::app);
        file << t << endl;
        file.close();

    }

    cout << " podaj ilosc iteracji ----->  ";
    cin >> itarations;
    if (itarations) return true;
    else return false;
}


