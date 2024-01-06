/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include "Field.h"

class Unit{
    
    protected:
    int x, y;
    int coins, hp;
    Field *F;
    
    public:
    
    Unit (Field *fi, int x0, int y0){
        this->F= fi;
        x=x0;
        y=y0;
        coins=0;
        hp=3;
    }
    
    virtual void move (char key) = 0;
    
    bool IsAlive()
    {
        if(hp>0){
            return true;
        }else{
            return false;
        }
    }
    
    int Get_x()
    {
        return this->x;
    }
    
    int Get_y()
    {
        return this->y;
    }
    
    int GetCoins()
    {
        return this->coins;
    }
};

class Tracer: public Unit{
    public:
    Tracer(Field *f, int x0, int y0): Unit(f, x0, y0){}
   
    void move(char key)
    {
        if(key != 'e'){
            int x1=x, y1=y;
            switch(key){
                case 'a': 
                y1--;
                break;
            
                case 'w':
                x1--;
                break;
            
                case 'd':
                y1++;
                break;
            
                case 'x':
                x1++;
                break;
            }
        
            if( F->Is_Legalmove (x1, y1)){
                x=x1;
                y=y1;
                if(F->CollectCoin(x, y)){
                    coins++;
                }else if(F->StepOnTrap(x,y)){
                    hp--;
                }
            }
        }
   }
   
};

class Jumper: public Unit {
    
    public:
    Jumper(Field *f, int x0, int y0): Unit(f, x0, y0){}
   
    void move(char key)
    {
        if(key != 'e'){
            int x1=x, y1=y;
            switch(key){
                case 'a': 
                y1-=2;
                break;
            
                case 'w':
                x1-=2;
                break;
            
                case 'd':
                y1+=2;
                break;
            
                case 'x':
                x1+=2;
                break;
            }
        
            if( F->Is_Legalmove (x1, y1)){
                x=x1;
                y=y1;
                if(F->CollectCoin(x, y)){
                    coins++;
                }else if(F->StepOnTrap(x, y)){
                    hp--;
                }
            }
        }
   }
};
   
class Crosser: public Unit {
    
    public:
    Crosser(Field *f, int x0, int y0): Unit(f, x0, y0){}
   
    void move(char key)
    {
        if(key != 'e'){
            int x1=x, y1=y;
            switch(key){
                case 'a': 
                x1--;
                y1--;
                break;
            
                case 'w':
                x1--;
                y1++;
                break;
            
                case 'd':
                x1++;
                y1++;
                break;
            
                case 'x':
                x1++;
                y1--;
                break;
            }
        
            if( F->Is_Legalmove (x1, y1)){
                x=x1;
                y=y1;
                if(F->CollectCoin(x, y)){
                    coins++;
                }else if(F->StepOnTrap(x, y)){
                    hp--;
                }
            }
        }
   }
};

