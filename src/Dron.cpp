#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Uklad.hh"
#include "Macierz.hh"
#include "Graniastoslup.hh"
#include "Prostopadloscian.hh"
#include "Dron.hh"
#include <cmath>

#define PI 3.14159265

using namespace std;

 
   void Dron:: zmarz() 
    {
      (this->korpus).zmazuj();
      (this->G1).zmazuj();
      (this->G2).zmazuj();
      (this->G3).zmazuj();
      (this->G4).zmazuj();  
    }

  void Dron:: rysuj() 
    {
      (this->korpus).rysuj();
      (this->G1).rysuj();
      (this->G2).rysuj();
      (this->G3).rysuj();
      (this->G4).rysuj();  
    }
    
  void Dron:: wirniki()
    {
      this->G1 = this->G1.rotacja(-15,'Z');
      this->G2 = this->G2.rotacja(15,'Z');
      this->G3 = this->G3.rotacja(15,'Z');
      this->G4 = this->G4.rotacja(-15,'Z');
    }
   
  void Dron:: gora(double wysokosc)
    {
      Wektor<3> W{0,0,wysokosc},V;
      this->srodek = this->srodek+W;
      this->korpus.translacja_v(W);
      this->G1 = this->G1.translacja(W);
      this->G2 = this->G2.translacja(W);
      this->G3 = this->G3.translacja(W);
      this->G4 = this->G4.translacja(W);
    }
    
  void Dron:: dol(double wysokosc)
    {
      Wektor<3> W{0,0,-wysokosc};
      this->korpus.translacja_v(W);
      this->G1 = this->G1.translacja(W);
      this->G2 = this->G2.translacja(W);
      this->G3 = this->G3.translacja(W);
      this->G4 = this->G4.translacja(W);
      this->srodek = this->srodek+W;
    }
    
  void Dron:: prosto(double kat, double odleglosc)
    { 
      double y = sin(kat*PI/180)*odleglosc;
      double x = cos(kat*PI/180)*odleglosc;
      Wektor<3> W{x,y,0}; 	
      this->korpus.translacja_v(W);
      this->G1 = this->G1.translacja(W);
      this->G2 = this->G2.translacja(W);
      this->G3 = this->G3.translacja(W);
      this->G4 = this->G4.translacja(W);
      this->srodek = this->srodek+W;
    }
    
  void Dron:: obrot(double kat) // wlasny uklad wspolrzednych 
    {
      Macierz<3> M(kat,'Z');
      this->orient = M*(this->orient);
      this->korpus.rotacja_v(M);
      this->G1.set_srodek(this->korpus[1]);
      this->G2.set_srodek(this->korpus[2]);
      this->G3.set_srodek(this->korpus[3]);
      this->G4.set_srodek(this->korpus[4]); 
    }

  Dron::Dron(Wektor<3> S, Macierz<3> O, double skala, drawNS::Draw3DAPI * rysownik): Uklad(S,O) //set 
    {
      double x = 5;
      double y = 5;
      double z = 1.5;
      double h = 1;
      double R = 4;
      int i = -1;
      Wektor<3> poprawka{0,0,skala*z};
      Wektor<3> W1{skala*x,skala*y,skala*(h+z)};
      Wektor<3> W2{skala*x,skala*(-y),skala*(h+z)};
      Wektor<3> W3{skala*(-x),skala*(-y),skala*(h+z)};
      Wektor<3> W4{skala*(-x),skala*y,skala*(h+z)};
      this->rysownik = rysownik;
      Prostopadloscian P(S, O, skala*x, skala*y, skala*z, this->rysownik, i, 'd');
      Graniastoslup G1(S+W1,O, skala*R, skala*h, this->rysownik, i);
      Graniastoslup G2(S+W2,O, skala*R, skala*h, this->rysownik, i);
      Graniastoslup G3(S+W3,O, skala*R, skala*h, this->rysownik, i);
      Graniastoslup G4(S+W4,O, skala*R, skala*h, this->rysownik, i);
      this->korpus = P;
      this->G1 = G1;
      this->G2 = G2;
      this->G3 = G3;
      this->G4 = G4;
      this->skala = skala;
      this->srodek = S+poprawka;
      this->orient = O;
      Wektor<2> N{(this->srodek[0]+W1[0]+(skala*R)),(this->srodek[1]+W1[1]+(skala*R))};
      this->promien_max = sqrt(((N[0] - this->srodek[0])*(N[0] - this->srodek[0])) + ((N[1] - this->srodek[1])*(N[1] - this->srodek[1])));
      this->wysokosc = skala*2*z + skala*h*2; 
    }
    
     bool Dron:: czy_nad(Wektor<3> S, double R)
       {  
         double h = this->promienmax() + R;
         Wektor<2> X, Y;
         X[0] = S[0];
         X[1] = S[1];
         Y[0] = (this->srodek)[0];
         Y[1] = (this->srodek)[1];
         Wektor<2> W = X - Y;
         double d = W.dlugosc();
         if (d < h)
           {
             return 1;
           }
         else 
           {
             return 0;
           }
       }
       
     bool Dron:: czy_ladowac(Wektor<3> S, double R)
       {
         return 0;
       }
