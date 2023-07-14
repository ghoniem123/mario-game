#include <iostream>
#include <string>
#include <conio.h>
#include<stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define UP 56
#define DOWN 53
#define LEFT 52
#define RIGHT 54

#define START 49
#define Random 50

#define Cast 120
#define Cast1 88

#define mario1 109
#define mario2 77

#define luigi1 108
#define luigi2 76


using namespace std;
class Cell{
private :
    char type;
    int x;
    int y;
public :
    Cell(char t, int x, int y);

    Cell();

    int getX();
    int getY();
    char getType();
    void setX(int x);
    void setY(int y);
    void setType(char type);
    virtual ~Cell(){};
};


Cell::Cell(char t, int x, int y){
    this->type=t;
    this->x=x;
    this->y=y;
    };
Cell::Cell(){
     this->type='.';
     this->x=0;
     this->y=0;
    };
// CELL CONSTRUCTOR

inline int Cell::getX(){return this->x;}
inline int Cell::getY(){return this->y;}
inline char Cell::getType(){return this->type;}
inline void Cell::setX(int x){ this->x=x;}
inline void Cell::setY(int y){ this->y=y;}
inline void Cell::setType(char t){this->type=t;}

//CELL FUNCTION

class Map{
private :
int rows=10;
int columns=10;
Cell*** board;

public :
    Map();

    ~Map();

    Cell*** GetMap();
    void print_Map();
    void randomize_Map();
    void clear_Map();

};

// MAP CLASS

class Champion : public Cell{
private :

    int health;
    int score;
    int gems_collected;
    int remaing_ability_moves;
public :
     Champion();
      void print_champ_info();

      int getHealth();
      int getScore();
      int getGems();
      int getRemainigMoves();
      virtual string getChampType(){return "";}

      void setHealth(int h);
      void setScore(int s);
      void setGems(int g);
      void SetRemainingMoves(int r);
      virtual void useAbility(Map* m){cout<<"ability x is called"<<endl;}
      virtual ~Champion(){};
};

class Mario : public Champion{
public :
    void useAbility(Map* m);
    string getChampType(){return "Mario";}
};


class Luigi: public Champion{
public :

    void useAbility(Map* m);
    string getChampType(){return "Luigi";}
};

Champion::Champion():Cell('c',0,0){
      this->health=100;
      this->score=0;
      this->gems_collected=0;
      this->remaing_ability_moves=2;
      cout<<"Constructor Champion() is called"<<endl;
     };

class Obstacle :public Cell{
private :
    int dmg_amount;

public :
    Obstacle();

    int getDmgAmount();

    virtual void execute (Champion* c){};

    virtual ~Obstacle(){};
};

class Bomb :public Obstacle{
public :
    void execute(Champion* c);

};

class Theif:public Obstacle{
public :
    void execute(Champion* c);

};

Obstacle::Obstacle():Cell('o',0,0){
    this->dmg_amount=(int)(((rand()%10)+2)/2);
    }

class Gem : public Cell{
private :
    int amount;

public :
    Gem ();

    int GetAmount();
    virtual void execute(Champion* c){};
    virtual ~Gem(){};

};

class Potion:public Gem{
    public :
void execute(Champion* c);
};

class Coin:public Gem{
    public :
void execute(Champion* c);
};

Gem::Gem ():Cell('g',0,0){
    this->amount=((int)(((rand()%10)+1)/2))+5;
    }

Map::Map(){
     board=new Cell**[rows];

     for (int i=0;i<10;i++)
            board[i]=new Cell*[columns];


     cout<<"Constructor Map() is called"<<endl;

};

//ALL CONSTRUCTORS

Map::~Map(){

    for (int i=0;i<10;i++){
      for (int j=0;j<10;j++){
       delete[] board[i][j];
      }
      delete[] board[i];
    }

      delete []board;

    }

// MAP DESTRUCTOR

inline int Champion::getHealth(){return this->health;}
inline int Champion::getScore(){return this->score;}
inline int Champion::getGems(){return this->gems_collected;}
inline int Champion::getRemainigMoves(){return this->remaing_ability_moves;}
inline void Champion::setHealth(int h){
    if (h>100)
        this->health=100;
    else if (h<0)
        this->health=0;
    else
     this->health=h;}
inline void Champion::setScore(int s){ this->score=s;}
inline void Champion::setGems(int g){
    if (g>40)
        this->gems_collected=40;
    else if (g<0)
        this->gems_collected=0;
    else
     this->gems_collected=g;}
inline void Champion::SetRemainingMoves(int r){this->remaing_ability_moves=r;}
void Champion::print_champ_info(){
cout<<"you are "<<this->getChampType()<<endl;
cout<<"Champion current position is x = "<<this->getY()<<", y = "<<this->getX()<<endl;
cout<<"Champion current health is "<<this->getHealth()<<endl;
cout<<"Champion current score is "<<this->getScore()<<endl;
cout<<"Gems collected : "<<this->getGems()<<" / 40"<<endl;
cout<<"Remaining ability moves : "<<this->getRemainigMoves()<<endl;
}


// CHAMPION FUNCTIONS EXCEPT ABILITY

inline int Gem::GetAmount(){return this->amount;}

void Potion::execute(Champion* c){
cout<<"Potion executed with points = "<<this->GetAmount()<<endl;
Sleep(300);
c->setHealth(c->getHealth()+this->GetAmount());
Sleep(170);

}

void Coin::execute(Champion* c){
cout<<"Coin executed with points = "<<this->GetAmount()<<endl;
Sleep(300);
c->setGems(c->getGems()+this->GetAmount());
Sleep(170);

}

 // GEM FUNCTIONS

inline int Obstacle::getDmgAmount(){return this->dmg_amount;}

void Bomb::execute(Champion* c){
cout<<"bomb executed with dmg = "<<this->getDmgAmount()<<endl;
Sleep(300);
c->setHealth(c->getHealth()-this->getDmgAmount());
Sleep(170);
}

void Theif::execute(Champion* c){
cout<<"theif executed with dmg = "<<this->getDmgAmount()<<endl;
Sleep(300);
c->setGems(c->getGems()-this->getDmgAmount());
Sleep(170);
}

 // OBSTACLE FUNCTIONS

inline Cell*** Map::GetMap(){return this->board;}

void Map::clear_Map(){

for (int i=0;i<10;i++)
    for (int j=0;j<10;j++){
      //delete board[i][j];
      board[i][j]=new Cell();
    }
}

void Map:: randomize_Map(){
this->clear_Map();

this->board[0][0]=new Champion();
this->board[0][0]->setX(0);
this->board[0][0]->setY(0);
this->board[0][0]->setType('c');

int potionc=0;
int coinc=0;
int bombc=0;
int theifc=0;


while (potionc<20){
    int x=rand() % 10;
    int y=rand() % 10;
  if (this->board[x][y]->getType()=='.'){
       this->board[x][y]=new Potion();
       this->board[x][y]->setX(x);
       this->board[x][y]->setY(y);
       this->board[x][y]->setType('g');
       potionc++;
}
}
while (coinc<20){
    int x=rand() % 10;
    int y=rand() % 10;
  if (this->board[x][y]->getType()=='.'){
       this->board[x][y]=new Coin();
       this->board[x][y]->setX(x);
       this->board[x][y]->setY(y);
       this->board[x][y]->setType('g');
       coinc++;
}
}

while (bombc<10){
    int x=rand() % 10;
    int y=rand() % 10;
  if (this->board[x][y]->getType()=='.'){
       this->board[x][y]=new Bomb();
       this->board[x][y]->setX(x);
       this->board[x][y]->setY(y);
       this->board[x][y]->setType('o');
       bombc++;
}
}

while (theifc<10){
    int x=rand() % 10;
    int y=rand() % 10;
  if (this->board[x][y]->getType()=='.'){
       this->board[x][y]=new Theif();
       this->board[x][y]->setX(x);
       this->board[x][y]->setY(y);
       this->board[x][y]->setType('o');
       theifc++;
}
}

cout<<"randomize_Map() is called"<<endl;
}

void Map::print_Map(){
for (int i=9;i>=0;i--){
for (int j=0;j<10;j++){
    if (board[i][j]->getType()=='o')
         cout<<(char)254<<" ";

    else if (board[i][j]->getType()=='g')
        cout<<char(260)<<" ";

    else if (board[i][j]->getType()=='c')
        cout<<char(258)<<" ";

    else if (board[i][j]->getType()=='.')
         cout<<'.'<<" ";

}
cout<<endl;
}

cout<<"print_Map() is called"<<endl;
}


//MAP FUNCTIONS

void checkCell(Champion* c, Map* mp2){
    int x=c->getX();
    int y=c->getY();
    Cell*** board=mp2->GetMap();
if ( board[x][y]->getType()=='.' ){
    delete   board[x][y];
    board[x][y]=c;
    board[x][y]->setX(x);
    board[x][y]->setY(y);
    board[x][y]->setType('c');

}
else if (board[x][y]->getType()=='g'){
    (static_cast<Gem*>(board[x][y]))->execute(c);
  delete   board[x][y];
    board[x][y]=c;
    board[x][y]->setX(x);
    board[x][y]->setY(y);
    board[x][y]->setType('c');
    c->setScore(c->getGems()*10);
}
else if (board[x][y]->getType()=='o'){
      (static_cast<Obstacle*>(board[x][y]))->execute(c);
        delete   board[x][y];
     board[x][y]=c;
    board[x][y]->setX(x);
    board[x][y]->setY(y);
    board[x][y]->setType('c');

}

}

bool check_if_possible(Champion* c){
if (c->getRemainigMoves()>0){
    c->SetRemainingMoves(c->getRemainigMoves()-1);
    return true;
}
else {
    cout<<"you have zero remaining ability moves"<<endl;
    return false;
}
}

void Mario::useAbility(Map* mp){
Cell*** mp2=mp->GetMap();

cout<<"to move press : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;

cout<<"press x to use the champion special ability "<<endl;

char cast=getch();

if (cast==Cast|| cast==Cast1){
cout<<"Mario Ability is called "<<endl;
if (check_if_possible(this)){
 cout<<"please enter the motion direction : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;

char direction=getch();
while (direction !=UP && direction!=DOWN && direction != RIGHT && direction != LEFT){
    cout<<"invalid cast direction"<<endl;
     cout<<"please enter the motion direction : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;
     direction=getch();
}
switch (direction){
case (UP):
    if (this->getX()==9 || this->getX()==8 ){

    }
    else {
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()+2);
        checkCell(this,mp);
        }
    break;
case (DOWN):
     if (this->getX()==0 || this->getX()==1){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()-2);
        checkCell(this,mp);
    }
    break;
case (LEFT):
     if (this->getY()==0 || this->getY()==1){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()-2);
        checkCell(this,mp);
    }
    break;
case (RIGHT):
     if (this->getY()==9 || this->getY()==8){

    }
    else{
         mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()+2);
        checkCell(this,mp);
    }
    break;
}
}
}
else {
    switch (cast){
case (UP):
    if (this->getX()==9){

    }
    else {
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()+1);
        checkCell(this,mp);
        }
    break;
case (DOWN):
     if (this->getX()==0){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()-1);
        checkCell(this,mp);
    }
    break;
case (LEFT):
     if (this->getY()==0){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()-1);
        checkCell(this,mp);
    }
    break;
case (RIGHT):
     if (this->getY()==9){

    }
    else{
         mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()+1);
        checkCell(this,mp);
    }
    break;
default : cout<<"Invalid motion direction"<<endl;
}

}
}

//MARIO FUNCTIONS

void removeMap(Champion* c,Map* m, char direction){
Cell*** mp=m->GetMap();

switch (direction){
case (UP):
    for (int i=(c->getX()+1);i<10;i++){
      if (mp[i][c->getY()]->getType()=='o'){
            delete   mp[i][c->getY()];
          mp[i][c->getY()]=new Cell();
      }
    }
    break;
case (DOWN):
      for (int i=(c->getX()-1);i>-1;i--){
      if (mp[i][c->getY()]->getType()=='o'){
             delete mp[i][c->getY()];
         mp[i][c->getY()]= new Cell();
      }
    }
    break;
case (LEFT):
     for (int i=(c->getY()-1);i>-1;i--){
      if (mp[c->getX()][i]->getType()=='o'){
            delete  mp[c->getX()][i];
         mp[c->getX()][i]=new Cell();
      }
    }
    break;
case (RIGHT):
      for (int i=(c->getY()+1);i<10;i++){
      if (mp[c->getX()][i]->getType()=='o'){
             delete  mp[c->getX()][i];
         mp[c->getX()][i]=new Cell();
      }
    }
    break;
default : cout<<"Invalid cast direction"<<endl;
}
}

void Luigi::useAbility(Map* mp){
Cell*** mp2=mp->GetMap();

cout<<"to move press : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;

cout<<"press x to use the champion special ability "<<endl;

char cast=getch();

if (cast==Cast || cast==Cast1){
cout<<"Luigi Ability is called "<<endl;
if (check_if_possible(this)){
 cout<<"please enter the cast direction : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;

char direction=getch();
while (direction !=UP && direction!=DOWN && direction != RIGHT && direction != LEFT){
    cout<<"invalid cast direction"<<endl;
     cout<<"please enter the motion direction : up -> 8, down -> 5, left -> 4, right ->6 "<<endl;
     direction=getch();
}
removeMap(this,mp,direction);
}
}
else {
    switch (cast){
case (UP):
    if (this->getX()==9){

    }
    else {
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()+1);
        checkCell(this,mp);
        }
    break;
case (DOWN):
     if (this->getX()==0){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setX(this->getX()-1);
        checkCell(this,mp);
    }
    break;
case (LEFT):
     if (this->getY()==0){

     }
    else{
        mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()-1);
        checkCell(this,mp);
    }
    break;
case (RIGHT):
     if (this->getY()==9){

    }
    else{
         mp2[this->getX()][this->getY()]=new Cell();
        this->setY(this->getY()+1);
        checkCell(this,mp);
    }
    break;
default : cout<<"Invalid motion direction"<<endl;
}

}
}

// LUIGI FUNCTIONS


void GameOver(Champion* c,Map* mp){
if (c->getGems() == 40 ){
    cout<<"Game over ! You Won :) "<<endl;
    delete mp;
    delete c;
    exit(0);
}
else if (c->getHealth()<=0){
    cout<<"Game over ! You Died :( "<<endl;
    delete mp;
    delete c;
    exit(0);
}
}

void start(Map* mp,Champion* c){
mp->randomize_Map();
mp->print_Map();

cout<<"------------------------------------------------------------------------"<<endl;
cout<<(char)254<<" : Obstacle"<<endl<<(char)260<<" : Gem"<<endl<<(char)258<<" : The champion"<<endl;
cout<<"RULES : "<<endl<<"      - To win you have to collect all the gems"<<endl<<"      - You lose if your health becomes zero"<<endl;
c->print_champ_info();

cout<<"Enter 1 to start the game "<<endl;
cout<<"Enter 2 to re-randomize the map "<<endl;

char key =getch();
int value =key;

while (value != START){

switch (key){

case (Random) :
    system("CLS");
    mp->randomize_Map();
    mp->print_Map();
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<(char)254<<" : Obstacle"<<endl<<(char)260<<" : Gem"<<endl<<(char)258<<" : The champion"<<endl;
    cout<<"RULES : "<<endl<<"      - To win you have to collect all the gems"<<endl<<"      - You lose if your health becomes zero"<<endl;
    c->print_champ_info();
    cout<<"Enter 1 to start the game "<<endl;
    cout<<"Enter 2 to re-randomize the map "<<endl;
    break;

default :
    cout<<"Invalid input"<<endl<<"Enter 1 to start the game "<<endl<<"Enter 2 to re-randomize the map "<<endl;

}

key=getch();
value=key;
}

}

void run(Map* mp, Champion* c){

      start(mp,c);

while (true){

        system("CLS");
        mp->print_Map();

        cout<<"------------------------------------------------------------------------"<<endl;

        cout<<(char)254<<" : Obstacle"<<endl<<(char)260<<" : Gem"<<endl<<(char)258<<" : The champion"<<endl;

        c->print_champ_info();
        GameOver(c,mp);
        c->useAbility(mp);
    }
}

int main()
{
    Champion* c;
   cout<<"Welcome to the game "<<endl;
   cout<<"please choose your champion "<<endl;
   cout<<"enter M to play with mario"<<endl<<"enter L to play with luigi"<<endl;
   char champtype=getch();

   while (champtype != mario1 && champtype != mario2 && champtype!=luigi1 && champtype!=luigi2 ){
   system("CLS");
   cout<<"Invalid champion choice"<<endl;
   cout<<"please choose your champion "<<endl;
   cout<<"enter M to play with mario"<<endl<<"enter L to play with luigi"<<endl;
   champtype=getch();
   }

   if (champtype==mario1 || champtype==mario2)
    c=new Mario();
   else if (champtype==luigi1 || champtype==luigi2)
    c=new Luigi();

   Map* world=new Map();

   run(world,c);

   return 0;
}
