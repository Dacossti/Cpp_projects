/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include "Unit.h"

int main()
{
    srand(time(0));
    
    Field F (10,5);
    F.Fulfill();
    
    int choice;
    cout<<"How do you wanna play (1st - 2nd or 3rd)?"<<endl;
    cin>>choice;
    
    Unit* you;
    if(choice==1){
        you= new Tracer(&F, 0, 0);
    }else if(choice==2){
        you= new Jumper(&F, 0, 0);
    }else if(choice==3){
        you= new Crosser(&F, 0, 0);
    }
    
    char key=' ';
    int score=0;
    while(you->IsAlive() and key!='e'){
        cin>> key;
        you->move(key);
        score+=5;
        F.Output(you->Get_x(), you->Get_y());
    }
    
    if(not you->IsAlive() ){
        cout<<"Game Over!"<<endl;
        cout<<"Score : "<<score<<endl;
        cout<<"Coins :"<<you->GetCoins()<<endl;
    }
    
    if(key=='e'){
        cout<<"Score : "<<score<<endl;
        cout<<"Coins :"<<you->GetCoins()<<endl;
        cout<<"Goodbye!"<<endl;
    }
    
    return 0;
}
