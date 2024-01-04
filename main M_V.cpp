/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;

class Vect {
    private :
    
    int dim;
    double *V;
    
    public :
    
    static int count;
    int num;
    
    Vect (int d){
        this->dim=d;
        this->V= new double [d];
        for (int i=0; i<d ; i++) 
        {
            this->V[i]=0;
        }
        count++;
        this->num=count;
        cout<<"Конструктор Vect (int d) создал нулевый Vect["<<this->num<<"] размера "<<d<<endl;
        this->print();
        return;
    }
    
    Vect(int d, double *X)
    {
        this->dim= d;
        this->V= new double [d];
        for(int i=0; i<d; i++) 
        {
            this->V[i]=X[i];
        }
        count++;
        num=count;
        cout<<"Конструктор Vect (int d, double* X) создал Vect["<<this->num<<"] размера "<<d<<endl;
        this->print();
        return;
    }

    
    Vect (Vect &X)
    {
        this->dim=X.dim;
        this->V= new double [this->dim];
        for (int i=0; i<this->dim ; i++) 
        {
            this->V[i]=X.V[i];
        }
        count++;
        num=count;
        cout<<"Конструктор копирования Vect (Vect& X) создал вектор номера ["<<num<<"] совпадающий с вектором номера ["<<X.num<<"] : "<<endl;
        this->print();
        return;
    }
    
    Vect ()
    {
        this->dim=0;
        this->V= nullptr;
        return;
    }
    
    ~ Vect (){
        delete [] this->V ;
        this->dim=0;
        cout<<"Вектор номера ["<<num<<"] был уничтожен!"<<endl;
    }
    
    void set (int d, double *X)
    {
        cout<<"Координаты вектора номера ["<<num<<"] были переопределены!"<<endl;
        this->dim= d;
        for(int i=0; i<d; i++){
            this->V[i]=X[i];
        }
        this->print();
    }
    
    void print ()
    {
        cout<<"( ";
        for(int i=0; i<(this->dim); i++) 
        {
            cout<<this->V[i]<<" ";
        }
        cout<<")"<<endl;
    }
    
    Vect& operator= (const Vect& R){
       if(&R != this)
       {
            delete [] this->V;
            this->dim = R.dim;
            V= new double [this->dim];
            for(int i=0; i<(this->dim); i++){
                this->V[i] = R.V[i];
            }
       }
       
       cout<<"Оператор присваивания копирует данные из вектора номера ["<<R.num<<"] в вектор номера ["<<this->num<<"]..."<<endl;
       this->print();
       return *this;
    }
    
    Vect operator+ (Vect&);
    
    friend Vect operator- (Vect L, Vect R)
    {
        Vect diff (L);
        for(int i=0; i<diff.dim; i++) 
        {
            diff.V[i]-= R.V[i];
        }
        cout<<"Вычитание вектора номера ["<<R.num<<"] из вектора номера ["<<L.num<<"] равно: "<<endl;
        diff.print();
        return diff;
    }
    
    Vect operator- ()
    {
        Vect neg (this->dim);
        for(int i=0; i<neg.dim; i++){
            neg.V[i]=- (this->V[i]);
        }
        cout<<"Вектор, противоположный к вектору номера ["<<this->num<<"], равен: "<<endl;
        neg.print();
        return neg;
    }
    
    double operator* (Vect &R)
    {
        int d=R.dim;
        double s=0;
        for(int i=0; i<d; i++) 
        {
            s+=((this->V[i]) * (R.V[i]));
        }
        cout<<"Скалярное произведение вектора номера ["<<this->num<<"] на вектор номера ["<<R.num<<"] равно: "<<s<<endl;
        return s;
    }
    
    double operator[] (int i){
        if( (i>=0) and (i<dim) ){
            cout<<"Элемент вектора номера ["<<num<<"] с индексом["<<i<<"] равен: "<<V[i]<<endl;
            return V[i];
        }else{
            cout<<"Элемент вектора номера ["<<num<<"] с таким индексом не существует!"<<endl;
            return 1;
        }
    }
    
    friend Vect& operator* (Vect , double);
    
    friend class Matrix;
    
};

    int Vect::count = 0;
    
    Vect Vect::operator+ (Vect& R)
    {
        Vect sum(R);
        for(int i=0; i<R.dim; i++) 
        {
            sum.V[i]+= this->V[i];
        }
        cout<<"Сумма вектора номера ["<<this->num<<"] и вектора номера ["<<R.num<<"]  равна: "<<endl;
        sum.print();
        return sum;
    }
    
    Vect& operator* ( Vect R, double k)
    {
        Vect tmp= R;
        for(int i=0; i<tmp.dim; i++) 
        {
            tmp.V[i]*= k;
        }
        cout<<"Произведение вектора номера ["<<R.num<<"] на число "<<k<<" равно: "<<endl;
        tmp.print();
        return tmp;
    }
    
class Matrix{
    private:
        
    int dim;
    double *M;
        
    public:
        
    static int count;
    int num;
        
    Matrix (int d)
    {
        this->dim=d;
        this->M= new double [d*d];
        for(int i=0; i<(d*d) ; i++){
            this->M[i]=0;
        }
        count++;
        num=count;
        this->print();
    }
        
    Matrix (int d, double* Mat)
    {
        this->dim=d;
        this->M= new double [d*d];
        for(int i=0; i<(d*d) ; i++){
                this->M[i]=Mat[i];
        }
        count++;
        num=count;
        this->print();
    }
        
    Matrix (Matrix& Mat)
    {
        this->dim=Mat.dim;
        this->M= new double [dim*dim];
        for(int i=0; i<(dim*dim) ; i++){
            this->M[i]=Mat.M[i];
        }
        count++;
        num=count;
        this->print();
    }
        
    ~ Matrix ()
    {
            delete [] this->M;
            this->dim=0;
            cout<<"Матрица номера ["<<num<<"] была уничтожена!"<<endl;
    }
        
    Matrix& operator= (const Matrix& R)
    {
        if(&R != this){
            delete [] this->M;
            this->dim = R.dim;
            M= new double [dim*dim];
            for(int i=0; i<(dim*dim); i++){
                this->M[i] = R.M[i];
            }
        }
        cout<<"Оператор присваивания копирует данные из матрицы номера ["<<R.num<<"] в матрицу номера ["<<this->num<<"]..."<<endl;
        this->print();
        return *this;
    }
        
    Matrix operator- ()
    {
        Matrix neg (this->dim);
        for(int i=0; i<dim*dim; i++){
            neg.M[i]=- (this->M[i]);
        }
        cout<<"Матрица, противоположная к матрице номера ["<<this->num<<"], равен: "<<endl;
        neg.print();
        return neg;
    }
        
    friend Matrix operator- (Matrix L, Matrix R)
    {
        Matrix diff (L);
        for(int i=0; i<(diff.dim)*(diff.dim) ; i++) 
        {
            diff.M[i]-= R.M[i];
        }
        cout<<"Вычитание матрицы номера ["<<R.num<<"] из матрицы номера ["<<L.num<<"] равно: "<<endl;
        diff.print();
        return diff;
    }
    
    Matrix operator* (Matrix &R){
        
        //if(this->dim==R.dim){
            Matrix X (R.dim);
            
            int n=0, m=0;
            for(int l=0; l<dim; l++){
                for(int j=0, k=n; j<dim; k++, j++){
                    for(int i=(l*dim) , c=j ; i<((l+1)*dim) ; c+=dim, i++){
                        X.M[k] += (this->M[i] * R.M[c]);
                    }
                }
                m++;
                n=m*dim;
            }
            X.print();
            return X;
            
        //}else{
            
        //}
    
    }   
    
    Vect operator* (Vect &R){
        Vect X (R.dim);
        
        for(int l=0; l<dim; l++){
            for(int i=(l*dim) , j=0 ; i<((l+1)*dim) ; j++, i++){
                X.V[l] += ( (this->M[i]) * R.V[j] ) ;
            }
        }
            
        X.print();
        return X;
    }
    
    
    void print ()
    {
        cout<<"[ ";
        for(int i=0; i<(dim*dim); i++) 
        {
            cout<<this->M[i]<<" ";
        }
        cout<<"]"<<endl;
    }
    
    double operator[] (int i){
        if( (i>=0) and (i<(dim*dim)) ){
            cout<<"Элемент матрицы номера ["<<num<<"] с индексом["<<i<<"] равен: "<<M[i]<<endl;
            return M[i];
        }else{
            cout<<"Элемент матрицы номера ["<<num<<"] с таким индексом не существует!"<<endl;
            return 1;
        }
    }
    
    
    Matrix operator+ (Matrix&);
    
    friend Matrix& operator* (Matrix , double);
};
    int Matrix::count = 0;
    
    Matrix& operator* ( Matrix R, double k)
    {
        Matrix X= R;
        for(int i=0; i<((X.dim)*(X.dim)) ; i++) 
        {
            X.M[i]*= k;
        }
        cout<<"Произведение матрицы номера ["<<R.num<<"] на число "<<k<<" равно: "<<endl;
        X.print();
        return X;
    }
    
    Matrix Matrix::operator+ (Matrix& R)
    {
        Matrix sum (R);
        for(int i=0; i<((R.dim)*(R.dim)) ; i++) 
        {
            sum.M[i]+= this->M[i];
        }
        cout<<"Сумма матрицы номера ["<<this->num<<"] и матрицы номера ["<<R.num<<"]  равна: "<<endl;
        sum.print();
        return sum;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
int main () {
    
    int dv;
    double p1;
    
    cout<<"Enter the dimension of your vector X: "<<endl;
    cin>>dv;
    cout<<"Enter a factor to multiply your vector X: "<<endl;
    cin>>p1;
    
    double X [dv];
    for(int i=0; i<dv; i++) 
    {
    cout<<"Enter element X["<<i<<"] of your vector: "<<endl;
    cin>>X[i];
    }

    cout<<endl;
    
    Vect V1(dv);
    cout<<endl;
    
    Vect V2 (dv, X);
    cout<<endl;
    
    Vect V3 (V2);
    cout<<endl;
    
    Vect A=V3;
    cout<<endl;
    
    V3[2];
    cout<<endl;
    
    V3.print();
    cout<<endl;
    
    V1.set ( dv, X);
    V1 + V2 + V3 + A;
    cout<<endl;
    
    V1 - V2;
    cout<<endl;
    
    V2 * V2;
    cout<<endl;
    
    Vect V5(dv);
    V5=V3;
    V5*V2;
    cout<<endl;
    
    A*p1;
    cout<<endl;
    
    ////////////////////////////////////////////////////////////////////////////
    
    int dm;
    double p2;
    
    cout<<"Enter the dimension of your matrix M: "<<endl;
    cin>>dm;
    cout<<"Enter a factor to multiply your matrix M: "<<endl;
    cin>>p2;
    
    double M [dm*dm];
    for(int i=0; i<dm*dm; i++) 
    {
    cout<<"Enter element M["<<i<<"] of your matrix: "<<endl;
    cin>>M[i];
    }

    cout<<endl;
    
    Matrix M1 (dm);
    cout<<endl;
    
    Matrix M2 ( dm, M);
    cout<<endl;
    
    M2*M2;
    cout<<endl;
    
    M2*p2;
    
    M2*V2;

    
    
    return 0;
}