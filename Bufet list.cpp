/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
using namespace std;

struct tovar{
    string name;
    float price;
    int amount;
    tovar* next;  
};
    void addfirst (tovar* &bufet, string nm, float pr, int am)
    {
    tovar* Newtov= new tovar;
    Newtov->name= nm;
    Newtov->price= pr;
    Newtov->amount= am;
    Newtov->next= bufet;  //put it before the first element of bufet
    bufet=Newtov;  //define it as the beginning of bufet
    }
    
    void addlast (tovar* bufet, string nm, float pr, int am)
    {
        tovar* Newtov= new tovar;
        Newtov->name= nm;
        Newtov->price= pr;
        Newtov->amount= am;
        tovar* tmp=bufet;
        if(bufet==NULL){
            bufet= Newtov;
        }else{
            while(tmp->next!= NULL){
                tmp=tmp->next;
            }
            tmp->next= Newtov;
        }
    }
    
    int addafter (tovar* bufet, string nm, float pr, int am, string nmafter)
    {
        tovar* Newtov = new tovar;
        Newtov->name= nm;
        Newtov->price= pr;
        Newtov->amount= am; 
        if(bufet==NULL){
             return 1;
        }else{
            tovar* tmp=bufet;
            while((tmp->name!=nmafter) and (tmp!= NULL)){
                tmp=tmp->next;
            }
            if(tmp==NULL){
                return 1;      
                //if we still want to add it to the list
                //cout<<"Tovar "<<nmafter<<" doesn't belong to this list! So let's add it to the end"<<endl;
                //tmp->next= Newtov;
            }else{
                Newtov->next=tmp->next;
                tmp->next=Newtov;
                return 0;
            }
        }
    }

    
    int addbefore (tovar* &bufet, string nm, float pr, int am, string nmbefore)
    {
        tovar* Newtov= new tovar;
        Newtov->name= nm;
        Newtov->price= pr;
        Newtov->amount= am;
        if(bufet==NULL){
            return 1;
        }else if(bufet->name==nmbefore){
            Newtov->next=bufet;
            bufet=Newtov;
            return 0;
        }else{
            tovar* prev=bufet;
            tovar* tmp=bufet->next;
            while((tmp->name!=nmbefore) and (tmp!=NULL)){
                prev=tmp;
                tmp=tmp->next;
            }
    
            if(tmp==NULL){
                return 1;
            }
            Newtov->next=prev->next;
            prev->next=Newtov;
            return 0;
        }
    }
    
    void printlist (tovar* bufet)
    {
        tovar* tmp=bufet;
        if(bufet==NULL){
            cout<<"This list is empty!"<<endl;
        }else{
            while(tmp!=NULL){
                cout<< tmp->name <<"  "<< tmp->price <<"$   "<< tmp->amount <<endl; //print tovar from the beginning to the end
                tmp=tmp->next;
            }
        }
    }
    
    int findtovar (tovar* bufet, string nm)
    {
        if(bufet==NULL){
            cout<<"This list is empty! So..."<<endl;
            return 1;
        }else{
            tovar* tmp= bufet;
            while((tmp->name!=nm) and (tmp->next!=NULL)){
                tmp=tmp->next;
            }
            if(tmp->name!=nm){
                cout<<"Tovar @"<<nm<<" doesn't belong to this list!"<<endl;
                return 1;
            }else{
                cout<<"Tovar @"<<nm<<" is found!"<<endl;
                return 0;
            }
        }
    }
    
    int deltovar (tovar* &bufet, string nm)
    {
        tovar* tmp= new tovar;
        int Value= findtovar (bufet, nm);
        if( Value== 0){
                if(bufet->name==nm){
                tmp=bufet;
                bufet=bufet->next;
                delete tmp;
                cout<<"Tovar @"<<nm<<" is now deleted!"<<endl;
                return 0;
            }else{
                tovar* prev= bufet;
                tmp= bufet->next;
                while(tmp->name!=nm){
                    prev=tmp;
                    tmp=tmp->next;
                }
                prev->next= tmp->next;
                delete tmp;
                cout<<"Tovar @"<<nm<<" is now deleted!"<<endl;
                return 0;
            }
        }else{
            return 1;
        }        
    }



int main()
{
    tovar* bufet= NULL;
    tovar* tmp= new tovar;
    tmp->name= "cake";
    tmp->price= 60.2;
    tmp->amount= 25;
    tmp->next= NULL;
    bufet=tmp;       //Initialize_bufet_list_with_tovar_cake
    
// Add_tovar_apple juice_to_the_beginning
    addfirst (bufet, "apple juice", 45.65, 30);
// Add_tovar_fried chicken_to_the_end   
    addlast (bufet, "fried chicken", 128.5, 50);
//test
    printlist (bufet);
    cout<<endl;
//Add_tovar_sugar_before_tovar_apple juice    
    addbefore (bufet, "sugar", 89, 250, "apple juice");
//Add_tovar_rice_before_tovar_fried chicken
    addbefore (bufet, "rice", 160, 200, "fried chicken");
//test
    printlist(bufet);
    cout<<endl;
    
//Add_tovar_bread_after_tovar_apple juice 
    addafter (bufet, "bread", 56, 84, "apple juice");
//Add_tovar_banana_after_tovar_fried chicken
    addafter (bufet, "banana", 67, 84, "fried chicken");  
//test
    printlist(bufet);
    cout<<endl;

//Check_if_tovar_water_belongs_to_bufet_list
    findtovar (bufet, "water");
//Check_if_tovar_fried chicken_belongs_to_bufet_list
    findtovar (bufet, "fried chicken");
    cout<<endl;
    
//delete_tovar_cake_from_bufet list (of course if it belongs to bufet list )
    deltovar (bufet, "cake");
//test
    printlist(bufet);
    cout<<endl;
    
//delete_tovar_cake_from_bufet list (of course if it belongs to bufet list )    
    deltovar (bufet, "water");
//test
    printlist(bufet);
    cout<<endl;
    
// Add_tovar_water_to_the_beginning
    addfirst (bufet, "water", 50, 70); 
// Add_tovar_vodka_to_the_end   
    addlast (bufet, "vodka", 350, 20); 
    cout<<"Tovar @water is added to the beginning of bufet list and tovar @vodka to the end!!!"<<endl;
//test
    printlist(bufet);

    return 0;
}