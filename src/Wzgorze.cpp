#include <iostream>
#include <vector>
#include <stdlib.h>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"
#include "Wzgorze.hh"

  Wzgorze::Wzgorze(Wektor<3> _srodek, double _skala, drawNS::Draw3DAPI * rysownik) //set 
    {
      this->srodek = _srodek;
      this->skala = _skala;
      this->rysownik = rysownik;
      this->i = -1;
    }
    
  void Wzgorze:: zmarz()
    {
      (this->rysownik)->erase_shape(this->i);
    }
    
  void Wzgorze:: rysuj()
    {
      double max = 0;
      double odleglosc;
      int wierzcholki = rand() % 5 + 3;
      int ramie;
      Wektor<2> N;
      Wektor<2> Z;
      (this->rysownik)->erase_shape(this->i);
      std::vector<drawNS::Point3D> dane;
      drawNS::Point3D P(0,0,0); //kolejny punkt
      drawNS::Point3D K(0,0,0); //pierwszy/ostatni punkt
      drawNS::Point3D S(0,0,0); //wierzcholek
      Wektor<3> W{4*skala,0,0}, H{0, 0, this->skala*7}, V;
      V = this->srodek;
      Macierz<3> M(360/wierzcholki);
      S = konwertuj(this->srodek + H); //wierzcholek
      N[0] = H[0];
      N[1] = H[2];
      Z[0] = this->srodek[0];
      Z[1] = this->srodek[2]; 
      this->wysokosc = skala*7;
      Z[0] = this->srodek[0];
      Z[1] = this->srodek[1]; 
        for (int j = 1; j < wierzcholki+1; j++)
        {
          ramie = rand() % 6 + 1;
          W[0] = this->skala*ramie;
          for (int a = 0; a < j; a++)
            {
              W = (M * W);
            }
          N[0] = W[0] + this->srodek[0];
          N[1] = W[1] + this->srodek[1];
          odleglosc = promien(N,Z);
          if (max < odleglosc)
            {
              max = odleglosc;
            } 
          if (j==1)
            {
              Wektor<3> Koniec = W;
              K=konwertuj(Koniec+this->srodek);
            }
          P=konwertuj(W+this->srodek);
          dane.push_back(P);
          dane.push_back(S);
          dane.push_back(P);
          if (j==wierzcholki)
            {
              dane.push_back(K);
              dane.push_back(S);
            }       
        }
      this->i = this->rysownik->draw_polygonal_chain(dane, "black");
      this->promien_max = max;
     }
       
     bool Wzgorze:: czy_nad(Wektor<3> S, double R)
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
       
     bool Wzgorze:: czy_ladowac(Wektor<3> S, double R)
       {
         return 0;
       }
    
     double promien(Wektor<2> W, Wektor<2> V)
       {
          return sqrt(((W[0] - V[0])*(W[0] - V[0])) + ((W[1] - V[1])*(W[1] - V[1])));
       }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
