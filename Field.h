/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Field{
    
    char ** field;
    int w,h;
    
    public:
    
    Field(int w, int h){
        this->w=w;
        this->h=h;
        field = new char* [w];
        for (int i=0; i<w; i++){
            field[i] = new char [h];
        }
    }
    
    void Fulfill()
    {
        for(int i=0; i<w; i++){
            for(int j=0; j<h; j++){
                int rng=rand()%100;
                if (rng < 50){
                    field[i][j]='_';
                }else if (rng < 70){
                    field[i][j]='0';
                }else if (rng < 85){
                    field[i][j]='$';
                }else if (rng < 100){
                    field[i][j]='*';
                }
            }
        }
    }
    
    void Output (int x, int y)
    {
        for(int i=0; i<w; i++){
            for(int j=0; j<h; j++){
                if(i==x && j==y){
                    cout<<"Y ";
                }else{
                    cout<<field[i][j]<<"  ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    bool Is_Legalmove (int x, int y)
    {
        if(x<0 or x>=w or y<0 or y>=h){
            cout<<"Вне пределов!"<<endl;
            return false;
        }else if(field[x][y] == '0'){
            cout<<"Препятствие!"<<endl;
            return false;
        }else{
            return true;
        }
    }
    
    bool CollectCoin (int x, int y)
    {
        bool fl= field[x][y]=='$';
        if (fl){
            cout<<"Копейки собраны!"<<endl;
            field[x][y]= '_';
        }
        return fl;
    }
    
    bool StepOnTrap (int x, int y)
    {
        bool ft= field[x][y]=='*';
        if (ft){
            cout<<"Одна жизнь потеряна!"<<endl;
            field[x][y]= '_';
        }
        return ft;
    }
};

