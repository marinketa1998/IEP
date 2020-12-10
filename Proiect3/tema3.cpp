class Investment { ... };  //clasa de baza a ierarhiei de investitii


//Resource Acquisition Is Initialization--acquires a resource and initialize a resource-managing object in the same statement
void f()
{	// auto_ptr este smart pointer-inseamna ca destructorul automat sterge ceea ce pointeaza
	std::auto_ptr<Investment> pInv(createInvestment()); // functia de care creeaza obicetul
		...
		copiere()						// folosim plnv pentru ce avem nevoie
								//plnv este sters automat de catre destructorul auto_ptr-ului
}

//auto_ptr sterge totul la ce pointeaza dupa ce obiectul este sters-> de aceea trebuie ca un obiect sa fie pointat de catre un singur 
//auto_ptr taltfel poate duce la o comportare nedefinita(va sterge acelasi obiect de mai multe ori)

//aceasta functie arata ca un obiect poate fi pointat doar de catre un auto_ptr
//pointerul copiat ramane null,iar cel care copiaza arata catre obictul respectiv
void copiere(){

	std::auto_ptr<Investment>  pInv1(createInvestment()); // pInv1 arata catre obiectul returnat de create investment
 	std::auto_ptr<Investment> pInv2(pInv1); // pInv2 acum arata catre obiectul creat sus; pInv1 este null
	pInv1 = pInv2; //pInv1 arata catre obiect;pInv2 este null
}//acesta nu se foloseste pentru containere pentru ce ele au nevoie de o copiere "normala"


//Alternativa pentru auto_ptr este RCSP
//RCSP=reference-counting smart pointer -> smart pointer care urmareste cate obiecte arata catre o anumita resursa si automat sterge
//resursa ca niciun obiect nu arate catre ea (este similar cu garbage collection)

void f()//functia f recrisa pentru a demonstra cum functioneaza shared_ptr
{

	std::tr1::shared_ptr<Investment> pInv1(createInvestment()); //pInv1 arata catre obiectul returnat de createInvestment()
	std::tr1::shared_ptr<Investment> pInv2(pInv1); //si pInv1 si pInv2 arata catre acelasi obiect
	pInv1 = pInv2; //nu se schimba nimic
}//la iesirea din functie ambele sunt distruse,iar obiectul catre care pointeaza este sters

//aceasta nu se aplica pentru vectori alocati dinamic(pentru ca un vector sau string pot oricand inlocui unul alocat dinamic)
//

//
//ITEM 14-trebuie sa ne gandim la comportarea copierii in cazul in care creeam o clasa sa manage-uie resursele
//folosim C API pentru manipularea obiectelor de tip Mutex oferind functiile de lock si unlocj

//avem mari multe tipuri de copiere : 
//1.Prohibit copying(interzicerea copierii) 
//2.Reference-count the underlying resource - retine obiectul pana cand ultimul pointer care arata spre el este sters
//3.Copy the undelying resource-copiaza si pointerul si obictul(vom avea doi pointeri si doua obiecte)
//4.Transfer ownership of the underlying resource - aceasta este realizat de auto_ptr(dupa ce e copiat,pointerul devine null)
class Lock: private Uncopyable { //prohibit copying
public:
	explicit Lock(Mutex *pm)
	: mutexPtr(pm)
	{ lock(mutexPtr); } // acquire resource
	~Lock() { unlock(mutexPtr); } // release resource
	private:
	Mutex *mutexPtr;
};

class Lock { //reference-count ->nu dorim sa stergem ci sa dam unlock(folosim shared_ptr cu functionalitatea de deleter-
		//nu sterge cand nu mai pointeaza niciunul,ci il deschide)
	public:
	explicit Lock(Mutex *pm) // init shared_ptr with the Mutex
	: mutexPtr(pm, unlock) // to point to and the unlock func as the deleter
	{ 
		lock(mutexPtr.get());
	}
	private:
	std::tr1::shared_ptr<Mutex> mutexPtr; // use shared_ptr
		//nu mai declara destructor!!,il foliseste pe cel din clasa Lock,care spune ca se unlock-uie mutexPtr
	}; // instead of raw pointer
int main() {
	Mutex m; // define the mutex you need to use
	...
	{ // create block to define critical section
	Lock ml(&m); // lock the mutex
	... // perform critical section operations
	} // automatically unlock mutex at end of block
}

