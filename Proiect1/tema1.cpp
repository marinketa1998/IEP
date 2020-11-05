#include <iostream>

using namespace std; //omputer needs to know where to check

class Points{
   public:
	int x;
	int y;
};

class Point{
	public:
	Points p; //cateodata sunt initializate,cateodata nu ->trebuie tot timpul manual
};

class Persoana {
	public:
	int ani;
	string nume;
	Persoana(int years,string name){ /*trebuie puse in constructor in ordinea in care sunt declarate(pentru ca asa se initializeaza,cu toate ca 
					ele se asigneaza(initializeaza) in ordinea in care sunt declarate) */
		ani = years; //asignare
		nume = name; //la built-in type e aceeasi chestie
	}
};

class Masina{
	public:
	Persoana owner;
	int anFabricatie;
	string marca;
	string model;
				//constructorul trebuie sa initilizeze totul intr-un obiect
				//initializarea se face pana nu se intra in constructor
	Masina(const Persoana& p,const int& an, const string& m,const string& mod)  //“a reference to a string object whose contents will not be changed.”
		:owner(p), /*copy constructor,mai repede merge cu initializare decat cu asignare si este recomandat asa ;
				este mai eficient decat apelarea a default constr. si apoi folosirea a operatorului copy assignment	*/
		anFabricatie(an), //se poate si cu asignare,dar pentru consistenta am folosit asa
		marca(m), //copy constructed
		model(mod)
	{}
};

class Demo{
	public:
	int k = 2;
};

class Copy{
	public:
	int k = 1;
	
	Copy()
	{};
	private:
	Copy(const Copy&); // declarations only
	Copy& operator=(const Copy&);
};

class Uncopyable {
	protected: // allow construction
	Uncopyable() {} // and destruction of
	~Uncopyable() {} // derived objects...
	private:
	Uncopyable(const Uncopyable&); // ...but prevent copying
	Uncopyable& operator=(const Uncopyable&);
};

class Uncopy {
	public:
	int k = 1;
};

int main(){

	cout << "Points.x="<<Points().x<<endl; //printeaza 0 ceea ce inseamna ca e initializat automat
	cout << "Points.Point.x=" << Point().p.x<<endl; //si in acest caz se printeza 0
	 /*initializarea automata nu este garantata,iar citirea unei variabile neintilizate poate provoca o comportare nedefinita a programului*/
	 
	 int manual = 7;
	 cout << "Manual init:"<<manual<<endl; //initializare manuala(alternativa este citirea de la tastatura)
	 
	 Persoana p(22,"marin");
	 cout <<"Persoana are "<<p.ani <<" ani si se numeste "<< p.nume <<endl;
	 Masina m(p,2012,"bmw","x3");
	 cout <<"Owner:"<< m.owner.nume << "\nan fabricatie:" <<m.anFabricatie<< "\nmarca:" << m.marca <<"\nmodel:"<<m.model<<endl;
	 
	// Masina m;  ->eroare pt ca are deja un constructor definit
	 Demo d; //apeleaza default constructor
	 cout << "Default contruct.=" << d.k << endl; //2
	 Demo d2(d);
	 cout << "Contr2=" << d2.k << endl; //2
	 d2.k = 3;
	 cout << "Constr2edit=" << d2.k << endl; //3
	 cout << "Constr1si2edit=" << d.k <<" "<<d2.k<< endl; // 2 3
	 d2 = d; //copy each non-static data member of the source object over to the target object.
	 cout << "Constr1si2copyassignement=" << d.k <<" "<<d2.k<< endl; //2 2
	 
	 
	 //declarat private fara implemenare
	 Copy c1;
	 cout << "c1.k=" << c1.k << endl;
	 //Copy c2(c1); ->eroare
	 Copy c2;
	 //c2=c1; ->eroare
	 
	 //cu ajutorul lui uncopyable
	 Uncopy u1;
	  cout << "u1.k=" << u1.k << endl;
	 //UnCopy u2(u1); ->eroare
	 Uncopy u2;
	 //c2=c1; ->eroare
	 

	return 0;
}
