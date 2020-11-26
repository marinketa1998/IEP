#include <iostream>

using namespace std; 

class Bitmap {
 private:
 int b = 2;
};

class Widget {
private:
Bitmap *pb;
public:
int p;
int r;
	Widget(const int& p,const int& r)
		:p(p),r(r)	
	{
	Bitmap o = Bitmap();
	pb = &o;
	};
	Widget& operator+(const Widget& rhs) {
		this->p = this->p + rhs.p;
	return *this; //Have assignment operators return a reference to *this.
	}
	
	/*Widget& operator=(int rhs) {
		this->p = rhs;
	return *this;
	}
	*/
	////
	/*
	Widget& operator=(const Widget& rhs){
	if (this == &rhs) return *this; //if  = do nothing   -> comparing addresses of source and target
	Bitmap *pOrig = pb;                               
	pb = new Bitmap(*rhs.pb);  //careful statement ordering,
	delete pOrig;
	return *this;
	}
	*/
	
	//copy-and-swap.
	Widget& operator=(Widget rhs) // rhs is a copy of the object
	{ 
 		swap(rhs); //tot timpul este pe cel din stanga

	return *this;
	}
	
	void swap(Widget& rhs){
		pb = rhs.pb;
		p = rhs.p;
		r = rhs.r;
	}
};	

	void logCall(const string& funcName); // make a log entry
		
	class Date { 
	int p = 2;
	 };	
	
	 class Customer {
	
	private:
	string name;
	Date lastTransaction = Date();
	public:
	Customer(const Customer& rhs)
	: name(rhs.name) // copy rhs’s data
	{
	logCall("Customer copy constructor");
	}
	
	Customer& operator=(const Customer& rhs)
	{
	logCall("Customer copy assignment operator");
	name = rhs.name; // copy rhs’s data
	return *this; // see Item 10
	}
};

	class PriorityCustomer: public Customer { // a derived class
	public:

	private:
	int priority;
	
	PriorityCustomer(const PriorityCustomer& rhs)
	: Customer(rhs),
	priority(rhs.priority)
	{
	logCall("PriorityCustomer copy constructor");
	}
	
	PriorityCustomer&
	operator=(const PriorityCustomer& rhs)
	{
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs);
	priority = rhs.priority;
	return *this;
	}
};

int main(){

	//cout << "Points.x=";
	//cout << "Points.Point.x="; 
	Widget w1 = Widget(4,4);
	Widget w2 = Widget(2,2);
	
	Widget w3 = w1+w2;
	cout << "w3.p="<< w3.p << " w3.r=" << w3.r<<endl; 
	
	w1 = w1;
	
	return 0;
}
