/******FIGURES***********/

#include "graphics.h"
#include <math.h>
#include <conio.h>
#include <iostream>

using namespace std;

class TPoint {
    
    protected:
    int x; 
    int y; 
    int color;
    
	public:
	
	TPoint (int a, int b, int c)
	{
	    x=a;
	    y=b;
	    color=c;
	    setcolor(c);
	}
	
	virtual void draw () = 0;
	
	virtual ~TPoint ()
	{
		cout<<"A point is being destroyed..."<<endl;
	}
	
	virtual void move (int a, int b)
	{
		x=a;
		y=b;
	}
	
	virtual void rotate (double alpha) = 0;
	
	virtual void hide () = 0;
};

class TCircle: public TPoint {
	
	protected:
    	int rad; 
    
    public:
    	
    	TCircle(int a1, int b1, int r, int c) : TPoint (a1, b1, c) 
    	{
    		rad = r;
		}
		
		~TCircle()
		{
			cout<<"A circle is being destroyed..."<<endl;
		}
	
    	void draw ()
		{
	    	setcolor (color);
	    	circle (x, y, rad);
		}
	
		void move (int a, int b)
		{
	    	x = a;
	    	y = b;
	    	this->draw();
		}
	
		virtual void rotate (double alpha){}
	
		void hide ()
		{
			cleardevice();
		}
};

class TLine: public TPoint {
    
    protected:
    int x2; 
    int y2;
    
	public: 	
	
	TLine (int a1, int b1, int a2, int b2, int c) : TPoint (a1, b1, c) 
	{
	    x2 = a2; 
	    y2 = b2;
	}
	
	~ TLine ()
	{
	    cout<<"A line is being destroyed..."<<endl;
	}
	
	void draw ()
	{
	    setcolor (color);
	    line (x, y, x2, y2);
	}
	
	void move (int a, int b)
	{
	    x2 = x2 + a - x;
	    y2 = y2 + b - y;
	    x = a;
	    y = b;
	    this->draw();
	}
	
	virtual void rotate (double alpha)
	{
		double al  = double ( alpha * M_PI /180.0 ) ;
		
	    int oldx2 = x2;
	    x2 = round ( (oldx2 - x) * cos(al) - (y2 - y) * sin(al) + x);
	    y2 = round ( (oldx2 - x) * sin(al) + (y2 - y) * cos(al) + y);
	    this->draw ();
	}
	
	void hide ()
	{
		cleardevice();
	}

};

class TSquare: public TLine {
    
    public:
	
	TSquare (int a1, int b1, int a2, int b2, int c) : TLine (a1, b1, a2 , b2, c) {}
	
	~ TSquare ()
    {
    	cout<<"A square is being destroyed..."<<endl;
	}
	
	void draw()
	{
	   double cx = (x + x2) /2;
	   double cy = (y + y2) /2;
	   
	   int P[8] = {	x, 
					y, 
					round ( (x - cx) * cos(M_PI/2) + (y - cy) * sin(M_PI/2) + cx ),
					round ( - (x - cx) * sin(M_PI/2) + (y - cy) * cos(M_PI/2) + cy ),
					x2, 
					y2, 
					round ( (x2 - cx) * cos(M_PI/2) + (y2 - cy) * sin(M_PI/2) + cx ),
					round ( - (x2 - cx) * sin(M_PI/2) + (y2 - cy) * cos(M_PI/2) + cy ),
		};
		
		setcolor(color);
	    for(int i=0; i<8; i+=2){
	    	line (P[i], P[i+1], P[(i+2)%8], P[(i+3)%8]);
		}
		
	}
	
	void move (int a, int b)
	{
	    x2 = x2 + a - x;
	    y2 = y2 + b - y;
	    x = a;
	    y = b;
	    this->draw();
	}
	
	void rotate (double alpha)
	{
	   	double al = double ( (alpha * M_PI) /180.0 ) ;
	   	
	    double cx = (x + x2) /2;
	    double cy = (y + y2) /2;
	    
	    int oldx = x;
	    x = round ( (oldx - cx) * cos(al) + (y - cy) * sin(al) + cx );
	    y = round ( - (oldx - cx) * sin(al) + (y - cy) * cos(al) + cy );
	    
	    x2 = round (2*cx - x);
	    y2 = round (2*cy - y);
	    
	    this-> draw();
	}
	
	void hide ()
	{
		cleardevice();
	}
	
};


class TRhomb: public virtual TSquare {
    
    protected:
    double theta; 
    
    public:
    
    TRhomb (int a1, int b1, int a2, int b2, double ang, int c) : TSquare (a1, b1, a2, b2, c)
    {
        theta = ang;
    }
    
    ~ TRhomb ()
    {
    	cout<<"A rhombus is being destroyed..."<<endl;
	}
	
    void draw ()
    {
    	double the = double ( (theta * M_PI ) / 180.0 ) ;
    	
	    int P[8] = {x,
					y,
					x2, 
					y2,
					round ( (x - x2) * cos(M_PI + the) + (y - y2) * sin(M_PI + the) + x2 ),
					round ( - (x - x2) * sin(M_PI + the) + (y - y2) * cos(M_PI + the) + y2 ),
					round ( (x2 - x) * cos(the) + (y2 - y) * sin(the) + x ),
					round ( - (x2 - x) * sin(the) + (y2 - y) * cos(the) + y ),
		};
		
		setcolor(color);
	    for(int i=0; i<8; i+=2){
	    	line (P[i], P[i+1], P[(i+2)%8], P[(i+3)%8]);
		}
		     
    }
    
    void move (int a, int b)
	{
	    x2 = x2 + a - x;
	    y2 = y2 + b - y;
	    x = a;
	    y = b;
	    this->draw();
	}
	
	void rotate (double alpha)
	{
		
		double the = double ( (theta * M_PI ) /180.0 );
        double al  = double ( (alpha * M_PI ) /180.0 ) ;

	    const double cx = (x2 + round ( (x2 - x) * cos(the) + (y2 - y) * sin(the) + x ) ) /2;
	    const double cy = (y2 + round ( - (x2 - x) * sin(the) + (y2 - y) * cos(the) + y ) ) /2;
	    
	    int oldx = x;
	    x = round ( (oldx - cx) * cos(al) + (y - cy) * sin(al) + cx );
	    y = round ( - (oldx - cx) * sin(al) + (y - cy) * cos(al) + cy );
	    
	    int oldx2 = x2;
	    x2 = round ( (oldx2 - cx) * cos(al) + (y2 - cy) * (sin(al)) + cx );
	    y2 = round ( - (oldx2 - cx) * sin(al) + (y2 - cy) * cos(al) + cy );
	        
	    this->draw ();
	}
	
	void hide ()
	{
		cleardevice();
	}
	
};

class TRect: public virtual TSquare { 
    
    protected:
    double beta;
    
    public:
    
    TRect (int a1, int b1, int a2, int b2, double ang, int c) : TSquare(a1, b1, a2, b2, c)
    {
        beta = ang;
    }
    
    ~ TRect ()
    {
    	cout<<"A rectangle is being destroyed..."<<endl;
	}
	
    void draw()
    {
    	double cx = (x + x2) /2;
	   	double cy = (y + y2) /2;
	    
	    double bet = double ( (beta * M_PI ) /180.0 );
	    
	   	int P[8] = {x, 
					y, 
					round ( (x - cx) * cos(bet) + (y - cy) * sin(bet) + cx ),
					round ( - (x - cx) * sin(bet) + (y - cy) * cos(bet) + cy ),
					x2, 
					y2, 
					round ( (x2 - cx) * cos(bet) + (y2 - cy) * sin(bet) + cx ),
					round ( - (x2 - cx) * sin(bet) + (y2 - cy) * cos(bet) + cy ),
		};
		
		setcolor(color);
	    for(int i=0; i<8; i+=2){
	    	line (P[i], P[i+1], P[(i+2)%8], P[(i+3)%8]);
		}
    }
    
    void move (int a, int b)
	{
	    x2 = x2 + a - x;
	    y2 = y2 + b - y;
	    x = a;
	    y = b;
	    this->draw();
	}
	
	void rotate (double alpha)
	{
		
		double al = double ( (alpha * M_PI) /180.0 ) ;
		
	    const double cx = (x + x2) /2;
	    const double cy = (y + y2) /2;
	
	    int oldx = x;
	    x = round ( (oldx - cx) * cos(al) + (y - cy) * sin(al) + cx );
	    y = round ( - (oldx - cx) * sin(al) + (y - cy) * cos(al) + cy );
	    
	    x2 = round (2*cx - x);
	    y2 = round (2*cy - y);
	    
	    this-> draw();
	}
	
	void hide ()
	{
		cleardevice();
	}
	
};

class TParallel: public TRhomb, public TRect  {
		
	public: 
	
	TParallel ( int a1, int b1, int a2, int b2, double al, double bet, int c)
	: 	TSquare (a1, b1, a2, b2, c), 
		TRhomb (a1, b1, a2, b2, al, c),
		TRect (a1, b1, a2, b2, bet, c)
	{}
	
	~ TParallel ()
	{
		cout<<"A parallelogram is being destroyed..."<<endl;
	}
	
	void draw()
	{
		double cx = (x + x2) /2;
	   	double cy = (y + y2) /2;
	    
	    double thet = double ( (theta * M_PI ) /180.0 );
	    double bet = double ( (beta * M_PI ) /180.0 );
	    
	    int P[8] = {x, 
					y, 
					round ( (x - cx) * cos(thet) + (y - cy) * sin(thet) + cx ),
					round ( - (x - cx) * sin(thet) + (y - cy) * cos(thet) + cy ),
					x2,
					y2,
					round ( (x2 - cx) * cos(bet) + (y2 - cy) * sin(bet) + cx ),
					round ( - (x2 - cx) * sin(bet) + (y2 - cy) * cos(bet) + cy ),
		};
		
		setcolor(color);
	    for(int i=0; i<8; i+=2){
	    	line (P[i], P[i+1], P[(i+2)%8], P[(i+3)%8]);
		}
	}
	
	void move (int a, int b)
	{
	    x2 = x2 + a - x;
	    y2 = y2 + b - y;
	    x = a;
	    y = b;
	    this->draw();
	}
	
	void rotate (double alpha);
	
	void hide ()
	{
		cleardevice();
	}
};
	
	
	

int main ()
{
	cout<<"Hello! Enjoy it..."<<endl;
	cout<<endl;
	
	
    initwindow(1380, 740);
	setactivepage(0);
    
    TCircle C (200, 200, 100, 14);
    TCircle* pc= &C;
    cleardevice();
    pc->draw();
    swapbuffers();
    delay(2000);
    
    TLine L1 (50, 50, 150, 250, 9);
    TLine* pl= &L1;
    cleardevice();
    pl->draw();
    swapbuffers();
    delay(2000);
    
    TSquare Sq1 (100, 150, 260, 300, 12);
	TSquare* ps= &Sq1;
    cleardevice();
    ps->draw();
    swapbuffers();
    delay(3000);
    
    TRect R1 (100, 150, 260, 300, 120, 13);
    TRect* pr= &R1;
    cleardevice();
    pr->draw();
    swapbuffers();
    delay(3000);
    
    TRhomb Rh (100, 150, 260, 300, 80, 14);
	TRhomb* prh = &Rh;
	cleardevice();
    prh->draw();
    swapbuffers();
    delay(3000);
    
    
    for(int i=20; i<=40; i++){
    	cleardevice();
    	pl->move(10*i, 8*i);
    	swapbuffers();
    	delay(1000);
	}
    
    for(int i=1; i<=30; i++){
    	cleardevice();
    	pl->rotate(80);
    	swapbuffers();
    	delay(1000);
	}
	
	for(int i=20; i<=40; i++){
    	cleardevice();
    	ps->move(10*i, 10*i);
    	swapbuffers();
    	delay(1000);
	}
	
	for(int i=1; i<=30; i++){
    	cleardevice();
		ps->rotate(80);
    	swapbuffers();
    	delay(1000);
	}
	
	for(int i=20; i<=40; i++){
    	cleardevice();
    	pr->move(10*i, 10*i);
    	swapbuffers();
    	delay(1000);
	}
	
    for(int i=1; i<=60; i++){
    	cleardevice();
		pr->rotate(80);
    	swapbuffers();
    	delay(500);
	}
    
    for(int i=20; i<=40; i++){
    	cleardevice();
    	prh->move(5*i, 5*i);
    	swapbuffers();
    	delay(1000);
	}
	
	for(int i=1; i<=30; i++){
		cleardevice();
    	prh->rotate(80);
    	swapbuffers();
    	delay(1000);
	}
		
    cleardevice();
    TPoint* pt = &Rh;
    pt->draw();
    delay(1000);
	getch();
    closegraph();
    
//    TParallel* Prl = new TParallel (100, 150, 260, 300, 80, 120, 14);
//	TRhomb* pprh = Prl;
//	TRect* ppr = Prl;
//	cleardevice();
//    pprh->draw();
//    ppr->draw();
//    swapbuffers();
//    delay(3000);
    
    cout<<endl<<endl<<endl<<"GOODBYE! See you soon..."<<endl;
    return 0;
}
