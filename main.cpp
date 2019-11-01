#include <iostream>
#include <cmath>
using namespace std;

class Numar_Complex{
    double re, im;
public:
    Numar_Complex();//initializare
    Numar_Complex(double, double);//initializare parametrizat
    Numar_Complex(const Numar_Complex &);//copiere
    ~Numar_Complex();
    void set_re(double);
    void set_im(double);
    double get_re();
    double get_im();
    void display();
    void modul();
    friend void modul(Numar_Complex); ///metoda in fct friend;
    Numar_Complex negativ();
    Numar_Complex inmultireScalar(double a);
    Numar_Complex radical();
    Numar_Complex operator +(const Numar_Complex &);
    Numar_Complex operator *(const Numar_Complex &);
    Numar_Complex operator /(const Numar_Complex &);
    Numar_Complex operator =(const Numar_Complex &);
    Numar_Complex operator --();
    Numar_Complex operator --(int a);
    friend ostream & operator <<(ostream &, Numar_Complex&);
    friend istream & operator >>(istream &, Numar_Complex&);
    friend void ecuatie (Numar_Complex, Numar_Complex, Numar_Complex);
};

class Manager{
    int n;
    Numar_Complex *z;
    public:
    //Manager();
    ~Manager();
    Numar_Complex & operator [](int);
    friend ostream & operator <<(ostream &, Manager&);
    friend istream & operator >>(istream &, Manager&);
    void citire();
    void afisare();
    void get_z();
};

/*Manager :: Manager()
{
    cout<<"Introduceti numarul de elemente: n=";
    cin>>n;
    z=new Numar_Complex[n];
}*/


istream & operator >>(istream &in, Manager& m)
{
    cout<<"Introduceti numarul de elemente: n=";
    in>>m.n;
    m.z=new Numar_Complex[m.n];
    for(int i=0;i<m.n;i++)
        in>>m.z[i];
    return in;
}

ostream & operator <<(ostream & out, Manager& m)
{
    out<<"Cele "<<m.n<<" numere complexe sunt:"<<endl;
    for(int i=0;i<m.n;i++)
    {
       out<<"Z"<<i+1<<"=";
       out<<m.z[i]<<endl;
    }
    return out;
}

Manager :: ~Manager()
{
    delete [] z;
}

/*void Manager :: afisare()
{
    cout<<"Cele "<<n<<" numere complexe sunt:"<<endl;
    for(int i=0;i<n;i++)
    {
       cout<<"Z"<<i+1<<"=";
       cout<<z[i]<<endl;
    }

}*/

Numar_Complex & Manager :: operator [](int poz)
{
    return z[poz];
}

Numar_Complex Numar_Complex :: negativ()
{

    re=-re;
    im=-im;
    return *this;
}

Numar_Complex Numar_Complex :: inmultireScalar(double a)
{
    Numar_Complex rez;
    rez.re=a*re;
    rez.im=a*im;
    return rez;
}

Numar_Complex  Numar_Complex :: radical()
{
    Numar_Complex rez;
    if(im>0){ //2xy=a, a>0 => x,y acelasi semn, atfel semn diferit
    rez.re=abs(sqrt((this->re+sqrt(this->re*this->re + this->im*this->im))/2));
    rez.im=abs(sqrt((-this->re+sqrt(this->re*this->re + this->im*this->im))/2));
    }
    else {
        rez.re=abs(sqrt((this->re+sqrt(this->re*this->re + this->im*this->im))/2));
        rez.im=(-1)*abs(sqrt((-this->re+sqrt(this->re*this->re + this->im*this->im))/2));
    }
    return rez;
}

void Numar_Complex :: modul()
{
    cout<<"|z|="<<sqrt(re*re+im*im)<<endl;
}

void modul(Numar_Complex z)
{
    cout<<"|z|="<<sqrt(z.re*z.re+z.im*z.im)<<endl;
}

void Numar_Complex :: set_re(double re)
{
    this->re=re;
}

void Numar_Complex :: set_im(double im)
{
    this->im=im;
}

double Numar_Complex :: get_re()
{
    return re;
}

double Numar_Complex :: get_im()
{
    return im;
}

void Numar_Complex :: display()
{
    if(im==0){
        cout<<"z="<<re<<endl;
        return;
    }
    if(re==0){
        if(im<0) cout<<"z=-i*"<<abs(im)<<endl;
            else cout<<"z=i*"<<im<<endl;
        return;
    }
    if(im<0) cout<<"z="<<re<<"-i*"<<abs(im)<<endl;
            else cout<<"z="<<re<<"+i*"<<im<<endl;
}

Numar_Complex :: Numar_Complex()
{
    re=0;
    im=0;
}

Numar_Complex :: Numar_Complex(double x, double y)
{
    re=x;
    im=y;
}

Numar_Complex :: Numar_Complex(const Numar_Complex &ob)
{
    re=ob.re;
    im=ob.im;
}

Numar_Complex Numar_Complex :: operator --()
{
    re--;
    im--;
    return *this;
}


Numar_Complex Numar_Complex :: operator --(int a)
{
    re--;
    im--;
    return *this;
}

Numar_Complex Numar_Complex :: operator +(const Numar_Complex &ob)
{
    Numar_Complex rez;
    rez.re=re+ob.re;
    rez.im=im+ob.im;
    return rez;
}

Numar_Complex Numar_Complex :: operator *(const Numar_Complex &ob)
{
    Numar_Complex rez;

    rez.re=re*ob.re-im*ob.im;
    rez.im=re*ob.im+ob.re*im;
    return rez;
}

Numar_Complex Numar_Complex :: operator /(const Numar_Complex &ob)
{
    Numar_Complex rez;
    //cout<<re<<" "<<im<<" "<<ob.re<<" "<<ob.im<<endl;
    rez.re=(re*ob.re+im*ob.im)/(ob.re*ob.re+ob.im*ob.im);
    rez.im=(ob.re*im-re*ob.im)/(ob.re*ob.re+ob.im*ob.im);
    //cout<<"rez="<<rez.re<<"+i*"<<rez.im;
    return rez;
}

Numar_Complex Numar_Complex :: operator =(const Numar_Complex &ob)
{
    if (this==&ob)
        return *this;
    re=ob.re;
    im=ob.im;
    return *this;
}

ostream & operator <<(ostream & out, Numar_Complex &ob)
{
    if(ob.im==0){
        out<<ob.re;
        return out;
    }
    if(ob.re==0){
        if(ob.im<0) out<<"-i*"<<abs(ob.im);
            else out<<"i*"<<ob.im;
        return out;
    }
    if(ob.im<0) out<<ob.re<<"-i*"<<abs(ob.im);
            else out<<ob.re<<"+i*"<<ob.im;
    return out;
}

istream & operator >>(istream & in, Numar_Complex &ob)
{
    cout<<"Introduceti numarul complex z=a+bi:"<<endl<<"a=";
    in>>ob.re;
    cout<<"b=";
    in>>ob.im;
    cout<<endl;
    return in;

}

Numar_Complex :: ~Numar_Complex()
{
    re=0;
    im=0;
}

void ecuatie (Numar_Complex z1, Numar_Complex z2, Numar_Complex z3)
{
    cout<<"Ecuatia: (";
    cout<<z1;
    cout<<")*z^2 + (";
    cout<<z2;
    cout<<")*z + (";
    cout<<z3;
    cout<<") = 0"<<endl;
    Numar_Complex delta, z1z3, z2z2, rez1, rez2;
    z1z3=z1*z3;
    z2z2=z2*z2;
    z1z3=z1z3.inmultireScalar(-4);
    delta=z2z2+z1z3;
    delta=delta.radical();
    z2=z2.negativ();
    rez1=(z2+delta)/z1.inmultireScalar(2);
    delta=delta.negativ();
    rez2=(z2+delta)/z1.inmultireScalar(2);
    cout<<"Prima radacina a ecuatiei este: "; cout<<rez1<<endl;
    cout<<"A doua radacina a ecuatiei este: "; cout<<rez2<<endl;
}

int main()
{
    Numar_Complex b(2,3);
    cout<<b<<endl;
    Numar_Complex z, c, r, y;//
     /*//z.set_re(2);
    z.set_im(3);
    Numar_Complex y;
    y.set_re(1);
    y.set_im(1);//*/
    /*cin>>z;
    cout<<"Z=";
    cout<<z<<endl;
    cin>>y;
    cout<<"y=";
    cout<<y<<endl;
    Numar_Complex Copy(z);
    cout<<"Copierea lui z :"<<endl;
    cout<<"copy=";
    cout<<Copy<<endl;
    z.modul();
    double a;
    cout<<"Introduceti scalarul cu care doriti sa il inmultiti pe z: a=";
    cin>>a;
    z=z.inmultireScalar(a);
    cout<<"Inmultire cu scalar: ";
    cout<<z<<endl;
    r=z.radical();
    cout<<"Radical din z=";
    cout<<r<<endl;

    ///ADUNAREA
    c=z+y;
    cout<<"Rezultatul adunarii este: ";
    cout<<c<<endl;
    ///INMULTIREA
    cout<<"Rezultatul inmultirii este: ";
    c=z*y;
    cout<<c<<endl;
    ///IMPARTIREA
    cout<<"Rezultatul impartirii este: ";
    c=z/y;
    cout<<c<<endl;
    ///ECUATIA DE GRADUL II
    Numar_Complex z1, z2, z3;
    cout<<"Dati coeficientii ecuatiei:"<<endl;
    cout<<"z1:"<<endl;
    cin>>z1;
    cout<<"z2:"<<endl;
    cin>>z2;
    cout<<"z3:"<<endl;
    cin>>z3;
    ecuatie(z1,z2,z3);*/

    Manager m;
    cin>>m;
    cout<<m;
    cout<<"Introduceti indexul elementului dorit: i=";
    int i;
    //cin>>i;
    //cout<<"Elementul de pe pozitia "<<i<<" este: z="<<m[i-1]<<endl;
    //m[0]=m[1]=(m[2]+m[3]);
    cout<<m;
    cout<<"Modul de m[1]: ";
    modul(m[1]);
    m[1]--;
    cout<<"m[1]-- = "<<m[1]<<endl;
    --m[0];
    cout<<"--m[0] = "<<m[0]<<endl;

    return 0;
}
