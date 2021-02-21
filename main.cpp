#include<iostream>
#include<stdlib.h>
#include<unordered_map>
#include<vector>
#include<typeinfo>
#include<cmath>
#include<cstring>
using namespace std;

class Produs{

public:
    Produs(){};
    Produs(const Produs &p){};
    virtual ~Produs(){};
    virtual float calcul_pret()const =0 ;
    virtual void citire(istream &in) = 0;
    virtual void afisare(ostream &out) const=0;
    friend istream &operator>>(istream &in, Produs &p);
    friend ostream &operator<<(ostream &out, const Produs &p);

};
istream &operator>>(istream &in, Produs &p){
    p.citire(in);
    return in;
}

ostream &operator<<(ostream &out, const Produs &p){
    p.afisare(out);
    return out;
}

///------------------------------------------------------------------------------------------

class Ingredient{
private:
    string denumire;
    int cantitate;
    int pret_unitar;
public:
    Ingredient();
    Ingredient(string denumire, int cantitate, int pret_unitar);
    Ingredient(const Ingredient &ing);
    virtual ~Ingredient();
    string getdenumire() const;
    int getcantitate() const;
    int getpretunitar() const;
    void setdenumire(string denumire);
    void setcantitate(int cantitate);
    void setpretunitar(int pret_unitar);
    Ingredient& operator=(const Ingredient &ing);
    void citire(istream &in);
    friend istream &operator>>(istream &in, Ingredient &ing);
    void afisare(ostream &out) const;
    friend ostream &operator<<(ostream &out,const Ingredient &ing);
};

Ingredient:: Ingredient(){
    this->denumire="";
    this->cantitate=0;
    this->pret_unitar=0;
}

Ingredient:: Ingredient(string denumire, int cantitate, int pret_unitar){
    this->denumire=denumire;
    this->cantitate=cantitate;
    this->pret_unitar=pret_unitar;
}

Ingredient:: Ingredient(const Ingredient &ing){
    this->denumire=ing.denumire;
    this->cantitate=ing.cantitate;
    this->pret_unitar=ing.pret_unitar;
}

Ingredient:: ~Ingredient(){
    this->denumire="";
    this->cantitate=0;
    this->pret_unitar=0;
}

string Ingredient::getdenumire() const{
    return this->denumire;
}

int Ingredient::getcantitate() const{
    return this->cantitate;
}

int Ingredient::getpretunitar() const{
    return this->pret_unitar;
}

void Ingredient::setdenumire(string denumire){
    this->denumire=denumire;
}

void Ingredient::setcantitate(int cantitate){
    this->cantitate=cantitate;
}

void Ingredient::setpretunitar(int pret_unitar){
    this->pret_unitar=pret_unitar;
}
Ingredient& Ingredient:: operator=(const Ingredient &ing){
    if(this==&ing)
        return *this;
    denumire=ing.denumire;
    cantitate=ing.cantitate;
    pret_unitar=ing.pret_unitar;
    return *this;
}

void Ingredient::citire(istream &in){
    cout<<"Introduceti denumirea ingredientului: ";
    in.get();
    getline(in,denumire);
    cout<<"Introduceti cantitatea ingredientului: ";
    in>>cantitate;
    cout<<"Introduceti pretul unitar al ingredientului: ";
    in>>pret_unitar;
}
istream &operator>>(istream &in, Ingredient &ing){
    ing.citire(in);
    return in;
}
void Ingredient::afisare(ostream &out) const{
    out<<"Denumirea ingredientului: "<<denumire;
    out<<"\nCantitatea ingredientului: "<<cantitate;
    out<<"\nPretul unitar al ingredientului: "<<pret_unitar;
}

ostream &operator<<(ostream &out,const Ingredient &ing){
    ing.afisare(out);
    return out;
}

///------------------------------------------------------------------------------------------

class Pizza: public Produs{
protected:
    int nr_ingrediente;
    static const int manopera;
    Ingredient *vect_ingred;
public:
    Pizza();
    Pizza(int nr_ingrediente, Ingredient *ing);
    Pizza(const Pizza &pz);
    virtual ~Pizza();
    Pizza& operator=(const Pizza &pz);
    int getnr_ingrediente() const {return this->nr_ingrediente;}
    Ingredient* getvect_ingred() const {return this->vect_ingred;}
    void setvect(int nr_ingrediente,Ingredient* vect_ingred);
    void citire(istream &in);
    void afisare(ostream &out) const;
    friend istream &operator>>(istream &in, Pizza &pz);
    friend ostream &operator<<(ostream &out, const Pizza &pz);
    float calcul_pret() const;
};

int const Pizza::manopera=10;

Pizza:: Pizza(){
    this->nr_ingrediente=0;
    this->vect_ingred=NULL;
}

Pizza::Pizza(int nr_ingrediente, Ingredient *ing){
     this->nr_ingrediente=nr_ingrediente;
     try
        {
            this->vect_ingred=new Ingredient[this->nr_ingrediente];
        }
     catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<this->nr_ingrediente; i++)
        this->vect_ingred[i]=ing[i];

}

Pizza::Pizza(const Pizza &pz){
     this->nr_ingrediente=pz.nr_ingrediente;
     try
        {
            this->vect_ingred=new Ingredient[this->nr_ingrediente];
        }
     catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<this->nr_ingrediente; i++)
        this->vect_ingred[i]=pz.vect_ingred[i];
}

Pizza::~Pizza(){
    this->nr_ingrediente=0;
    delete [] this->vect_ingred;
}

Pizza& Pizza::operator=(const Pizza &pz){
    if(this == &pz)
        return *this;
    nr_ingrediente=pz.nr_ingrediente;
    try
        {
            vect_ingred=new Ingredient[nr_ingrediente];
        }
     catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<nr_ingrediente; i++)
        vect_ingred[i]=pz.vect_ingred[i];
    return *this;
}

void Pizza::setvect(int nr_ingrediente,Ingredient* vect_ingred){
    this->nr_ingrediente=nr_ingrediente;
    try
        {
            this->vect_ingred=new Ingredient[this->nr_ingrediente];
        }
     catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<this->nr_ingrediente; i++)
        this->vect_ingred[i]=vect_ingred[i];
}

void Pizza:: citire(istream &in){
    cout<<"Introduceti numarul de ingrediente pentru pizza: ";
    in>>nr_ingrediente;
     try
        {
            vect_ingred=new Ingredient[nr_ingrediente];
        }
     catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    cout<<"Introduceti urmatoarele caracteristici ale ingredientelor: \n";
    for(int i=0;i<nr_ingrediente;i++)
        {
            cout<<"\nCaracteristici pentru ingredientul "<<i+1<<": \n";
            vect_ingred[i].citire(in);
        }
 }

istream &operator>>(istream &in, Pizza &pz){
    pz.citire(in);
    return in;
}

void Pizza:: afisare(ostream &out) const{
    out<<"Afisarea numarului de ingrediente: "<<nr_ingrediente;
    out<<"\nAfisarea manoperei alese de producator: "<<manopera;
    out<<"\nAfisarea celor "<<nr_ingrediente<<" ingrediente: \n";
    for(int i=0;i<nr_ingrediente;i++)
        {
            out<<"\nIngredientul "<<i+1<<"\n";
            vect_ingred[i].afisare(out);
            out<<"\n";
        }
}

ostream &operator<<(ostream &out, const Pizza &pz){
    pz.afisare(out);
    return out;
}

float Pizza:: calcul_pret() const{
    float pret=0;
    for(int i=0;i<nr_ingrediente;i++)
        pret+=vect_ingred[i].getcantitate()*vect_ingred[i].getpretunitar();
    pret+=manopera;
    return pret;
}

///------------------------------------------------------------------------------------------

class Comanda_Online: public Pizza{
private:
    int drum_de_parcurs;
public:
    Comanda_Online();
    Comanda_Online(int nr_ingrediente, Ingredient* vect_ingred, int drum_de_parcurs);
    Comanda_Online(const Comanda_Online &po);
    virtual ~Comanda_Online();
    Comanda_Online& operator=(const Comanda_Online &po);
    int getdrum_de_parcurs() const { return this->drum_de_parcurs;}
    void setdrum_de_parcurs(int drum_de_parcurs){ this->drum_de_parcurs=drum_de_parcurs;}
    void citire(istream &in);
    void afisare(ostream &out) const;
    friend istream& operator>>(istream &in, Comanda_Online &po);
    friend ostream& operator<<(ostream &out, const Comanda_Online &po);
    float calcul_pret() const;
};

Comanda_Online::Comanda_Online(): Pizza(){
    this->drum_de_parcurs=0;
}

Comanda_Online::Comanda_Online(int nr_ingrediente, Ingredient* vect_ingred, int drum_de_parcurs):Pizza(nr_ingrediente,vect_ingred){
    this->drum_de_parcurs=drum_de_parcurs;
}

Comanda_Online::Comanda_Online(const Comanda_Online &po): Pizza(po){
     this->drum_de_parcurs=po.drum_de_parcurs;
}

Comanda_Online::~Comanda_Online(){

}

Comanda_Online& Comanda_Online::operator=(const Comanda_Online &po){
    if(this == &po)
        return *this;
    nr_ingrediente=po.nr_ingrediente;
    try
        {
            vect_ingred=new Ingredient[nr_ingrediente];
        }
    catch(bad_alloc &x)
        {
            cout << "Alocare Nereusita" << endl;
            exit(EXIT_FAILURE);
        }
    for(int i=0; i<nr_ingrediente; i++)
        vect_ingred[i]=po.vect_ingred[i];
    drum_de_parcurs=po.drum_de_parcurs;
    return *this;
}

void Comanda_Online::citire(istream &in){
    Pizza::citire(in);
    cout<<"Introduceti drumul parcurs de angajat pana la domiciliul clientului: ";
    in>>drum_de_parcurs;
}

void Comanda_Online::afisare(ostream &out) const{
    Pizza::afisare(out);
    out<<"Afisarea drumului parcurs de angajat: "<<drum_de_parcurs;

}

istream& operator>>(istream &in, Comanda_Online &po){
    po.citire(in);
    return in;
}

ostream& operator<<(ostream &out, const Comanda_Online &po){
    po.afisare(out);
    return out;
}

float Comanda_Online:: calcul_pret() const{
    double pret;
    int km=0;
    pret = Pizza::calcul_pret();
    while(km<=drum_de_parcurs)
        {
            if(km!=0 && km%10==0)
                   pret+=0.05*pret;
            km++;
        }
    return ceil(pret * 100.0) / 100.0;
}

///------------------------------------------------------------------------------------------

template<class TipPizza> class Meniu;
template<class TipPizza> istream& operator >>(istream &in, Meniu<TipPizza>&);
template<class TipPizza> ostream& operator <<(ostream &out, const Meniu<TipPizza>&);

template<class TipPizza>
class Meniu{
private:
   unordered_map<int,vector<Ingredient>> m;
   static int index;
public:
    Meniu();
    Meniu(unordered_map<int ,vector<Ingredient>> m);
    Meniu(const Meniu &men);
    ~Meniu();
    unordered_map<int,vector<Ingredient>> getm() const{return this->m;}
    int getindex() const{return this->index;}
    void operator+=(const TipPizza &p);
    Meniu<TipPizza>& operator=(const Meniu<TipPizza>&men);
    friend istream& operator >> <TipPizza>(istream &in, Meniu<TipPizza>&);
    friend ostream& operator << <TipPizza>(ostream &out, const Meniu<TipPizza>&);
};

template <class TipPizza> int Meniu<TipPizza>::index=0;

template <class TipPizza>
Meniu<TipPizza>::Meniu(){

}

template <class TipPizza>
Meniu<TipPizza>::Meniu(unordered_map<int,vector<Ingredient>> m)
{
    this->m=m;
}

template <class TipPizza>
Meniu<TipPizza>::Meniu(const Meniu &men){
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    for (i = men.m.begin(); i != men.m.end(); ++i )
        this->m.insert(*i);
}

template <class TipPizza>
Meniu<TipPizza>::~Meniu()
{
    this->m.clear();
    index=0;
}

template<class TipPizza>
void Meniu<TipPizza>::operator +=(const TipPizza &p){
    int id_pizza;
    cout<<"Da-ti id-ul pizzei: ";
    cin>>id_pizza;
    vector<Ingredient> v;
    Ingredient* vect = p.getvect_ingred();
    for(int j=0;j<p.getnr_ingrediente();j++)
            v.push_back(vect[j]);
    m.insert(make_pair(id_pizza,v));
    index++;
}

template<class TipPizza>
Meniu<TipPizza>& Meniu<TipPizza>::operator=(const Meniu<TipPizza>& men){
    if (this == &men)
        return *this;
    m.clear();
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    for (i = men.m.begin(); i != men.m.end(); ++i)
       this->m.insert(*i);
    return *this;
}

template<class TipPizza> istream& operator >>(istream &in, Meniu<TipPizza>& men){
    if(typeid(TipPizza)==typeid(Pizza))
        cout<<"Introduceti datele pizzelor comandate in pizzerie: "<<endl;
    else
        cout<<"Introduceti datele pizzelor comandate: "<<endl;
    cout<<"Introduceti nr. de pizza: ";
    int nr;
    in>>nr;
    TipPizza p;
    for(int i=0;i<nr;i++)
      {
        cout<<"\nIntroduceti datele pizzei cu nr. "<<i+1<<": \n";
        in>>p;
        men+=p;
      }
    return in;
}

template<class TipPizza> ostream& operator <<(ostream &out, const Meniu<TipPizza>& men){
     if(typeid(TipPizza)==typeid(Pizza))
        out<<"\n\nSe afiseaza datele pizzelor comandate in pizzerie: \n";
    else
        out<<"\n\nSe afiseaza datele pizzelor comandate: \n";
    out<<"\nNumarul de produse vandute in total: "<<men.index;
    out<<"\nNumarul de pizze din meniul curent: "<<men.m.size();
    out<<"\nDatele pizzelor: "<<endl;
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    vector<Ingredient*>::iterator j;
    for (i = men.m.begin(); i != men.m.end(); ++i) {
        out <<"\nId-ul pizzei: "<<i->first<<endl;
        out<<"Ingredientele: "<<endl;
        for (Ingredient j : i->second)
            out<<j<<endl;
        out<<endl;
    }
    return out;

}

///------------------------------------------------------------------------------------------

template <> class Meniu<Comanda_Online>{
private:
    unordered_map<int,vector<Ingredient>> m;
    static int index;
    static int nrkm;
    static float val_veg;
public:
    Meniu();
    Meniu(unordered_map<int ,vector<Ingredient>> m);
    Meniu(const Meniu &men);
    ~Meniu();
    unordered_map<int,vector<Ingredient>> getm() const{return this->m;}
    int getindex() const{return this->index;}
    int getnrkm() const{return this->nrkm;}
    void operator+=(const Comanda_Online &p);
    Meniu<Comanda_Online>& operator=(const Meniu<Comanda_Online>&men);
    friend istream& operator >>(istream &in, Meniu<Comanda_Online>&);
    friend ostream& operator <<(ostream &out, const Meniu<Comanda_Online>&);
    float pizza_vegetariana();
};

int Meniu<Comanda_Online>::index=0;
int Meniu<Comanda_Online>::nrkm=0;
float Meniu<Comanda_Online>::val_veg=0;

Meniu<Comanda_Online>::Meniu(){

}

Meniu<Comanda_Online>::Meniu(unordered_map<int,vector<Ingredient>> m){
    this->m=m;
}

Meniu<Comanda_Online>::Meniu(const Meniu &men){
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    for (i = men.m.begin(); i != men.m.end(); ++i )
        this->m.insert(*i);
}

Meniu<Comanda_Online>::~Meniu(){
    this->m.clear();
    index=0;
    nrkm=0;
    val_veg=0;
}

void Meniu<Comanda_Online>::operator +=(const Comanda_Online &p){
    int id_pizza;
    bool ok=true;
    cout<<"Da-ti id-ul pizzei: ";
    cin>>id_pizza;
    vector<Ingredient> v;
    Ingredient* vect = p.getvect_ingred();
    for(int j=0;j<p.getnr_ingrediente();j++){
        v.push_back(vect[j]);
        if(vect[j].getdenumire()=="carne")
            ok=false;
    }
    m.insert(make_pair(id_pizza,v));
    index++;
    nrkm+=p.getdrum_de_parcurs();
    if(ok==true)
        val_veg+=p.calcul_pret();
}

Meniu<Comanda_Online>& Meniu<Comanda_Online>::operator=(const Meniu<Comanda_Online>& men){
    if (this == &men)
        return *this;
    m.clear();
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    for (i = men.m.begin(); i != men.m.end(); ++i)
       this->m.insert(*i);
    return *this;
}

istream& operator >>(istream &in, Meniu<Comanda_Online>& men){
    int nr;
    Comanda_Online p;
    cout<<"Introduceti datele pizzelor comandate online: "<<endl;
    cout<<"\nNr. de pizza comandate online: ";
    in>>nr;
    for(int i=0;i<nr;i++)
    {
        cout<<"Introduceti datele pizzei cu nr. "<<i+1<<": \n";
        in>>p;
        men+=p;
    }
    return in;
}

ostream& operator <<(ostream &out, const Meniu<Comanda_Online>& men){
    out<<"\n\nAfisarea datelelor pizzelor comandate online: \n";
    out<<"\nNumarul de produse vandute in total prin livrari la domiciliu: "<<men.index;
    out<<"\nNumarul de km. parcursi in total pentru livrari la domiciliu: "<<men.nrkm;
    out<<"\nNumarul de pizze din meniul curent: "<<men.m.size();
    out<<"\nDatele pizzelor: "<<endl;
    unordered_map<int,vector<Ingredient>>::const_iterator i;
    vector<Ingredient*>::iterator j;
    for (i = men.m.begin(); i != men.m.end(); ++i) {
        out <<"\nId-ul pizzei: "<<i->first<<endl;
        out<<"Ingredientele: "<<endl;
        for (Ingredient j : i->second)
            out<<j<<endl;
        out<<endl;
    }
    return out;

}

float Meniu<Comanda_Online>::pizza_vegetariana(){
    return val_veg;
}

///------------------------------------------------------------------------------------------

int main()
{
    int opt,nr;
    Produs **v;
    while(true)
    {
        cout<<"Optiunile din meniu:\n";
        cout<<"Optiunea 0: Iesire din program.\n";
        cout<<"Optiunea 1: Citeste si afiseaza informatii despre produse.\n";
        cout<<"Optiunea 2: Citeste si afiseaza informatii despre Meniu --> template(Pizza).\n";
        cout<<"Optiunea 3: Citeste si afiseaza informatii despre Meniu --> template(Comanda_Online-specializare).\n";
        cout<<"Optiunea 4: Afiseaza valoarea incasata prin vinderea de pizza vegetariana dintr-un Meniu.\n";
        cout<<"\nAlegeti optiunea dorita: ";
        cin>>opt;
        cout<<endl;
        if(opt==0)
            {cout<<"S-a iesit din program.";
            break;
            }
        else
            if(opt==1)
            {
                int i=0;
                string aux;
                cout<<"Introduceti numarul de obiecte pe care vreti sa le cititi: ";
                cin>>nr;
                if(nr>0)
                {
                    v=new Produs*[nr];
                    while(i<nr)
                    {
                        cout<<"\nIntroduceti ce tip de produs vreti sa fie produsul "<<i+1<<": ";
                        cin>>aux;
                        try{
                            int gasit=0;
                            if(aux=="pizza"){
                                v[i]=new Pizza;
                                cin>>*v[i];
                                i++;
                                gasit=1;
                            }
                            else
                                if(aux=="comanda_online"){
                                    v[i]=new Comanda_Online;
                                    cin>>*v[i];
                                    i++;
                                    gasit=1;
                                    }
                            if(gasit==0)
                                cout<<"\nTipul de produs introdus nu exista. Produsele care exista sunt pizza si comanda_online\n ";
                        }
                        catch (bad_alloc &exceptie){
                            cout << "Allocation Failure\n";
                            exit(EXIT_FAILURE);
                        }
                    }
                    cout<<"\nAfisare produse:\n";
                    for(int i=0;i<nr;i++)
                    {
                        cout<<"\nAfisarea produsului cu numarul "<<i+1;
                        cout<<"\n"<<*v[i]<<endl;
                    }
                }
                else
                    cout<<"Numarul introdus nu este pozitiv. Incercati alt numar.";
            }
            else
                if(opt==2)
                {
                    Meniu<Pizza> p;
                    cin>>p;
                    cout<<p;
                }
                else
                    if(opt==3)
                    {
                        Meniu<Comanda_Online> co;
                        cin>>co;
                        cout<<co;
                    }
                    else
                         if(opt==4)
                        {
                            Meniu<Comanda_Online> co;
                            cin>>co;
                            cout<<"\nValoarea incasata din pizzele vegetariene: "<<co.pizza_vegetariana();
                        }
                    else
                        cout<<"Nu s-a selectat nicio optiune valida.Incercati 0,1,2,3 sau 4.";
        cout<<endl;
        system("pause");
        system("cls");
    }

    return 0;
}
