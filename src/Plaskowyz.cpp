#include <iostream>
#include <vector>
#include <cmath>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"
#include "Plaskowyz.hh"
#include "Wzgorze.hh"

  Plaskowyz::Plaskowyz(Wektor<3> _srodek, double _skala, drawNS::Draw3DAPI * _rysownik) //set 
    {
      this->srodek = _srodek;
      this->skala = _skala;
      this->rysownik = _rysownik;
      this->i = -1;
    }
    
   void Plaskowyz:: zmarz()
    {
      (this->rysownik)->erase_shape(this->i);
    }
    
  void Plaskowyz:: rysuj()
    {
      int wierzcholki = rand() % 8 + 3;
      double max = 0;
      double min = 100;
      double odleglosc;
      int ramie;
      Wektor<2> N;
      Wektor<2> Z;
      Wektor<3> Sok;
      Wektor<3> Pop;
      Wektor<3> Kon;
      (this->rysownik)->erase_shape(this->i);
      std::vector<drawNS::Point3D> dane;
      drawNS::Point3D P(0,0,0); //kolejny punkt
      drawNS::Point3D K(0,0,0); //pierwszy/ostatni punkt
      drawNS::Point3D S(0,0,0); //punkt gorny
      drawNS::Point3D T(0,0,0); //kolejny punkt gorny
      drawNS::Point3D Pp(0,0,0); //poprzedni
      Wektor<3> W{this->skala*5, 0, 0}, H{0, 0, this->skala*3};
      N[0] = H[0];
      N[1] = H[2];
      Z[0] = this->srodek[0];
      Z[1] = this->srodek[2]; 
      this->wysokosc = promien(N,Z);
      Macierz<3> M(360/wierzcholki);
      Z[0] = this->srodek[0];
      Z[1] = this->srodek[1]; 
        for (int j = 1; j < wierzcholki+1; j++)
        {
          ramie = rand() % 6 + 1;
          if (j > 1)
            {
              Pop = W + H + this->srodek;
              Pp=konwertuj(Pop);
            }
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
          if (min > odleglosc)
            {
              min = odleglosc;
            }  
          Sok = W + H + this->srodek;
          S = konwertuj(Sok); //wierzcholek
          if (j==1)
            {
              Kon = W+this->srodek;
              K=konwertuj(Kon);
            }
          P=konwertuj(W+this->srodek);
          dane.push_back(P);
          dane.push_back(S);
          if (j > 1)
            {
              dane.push_back(Pp);
              dane.push_back(S);
            }
          dane.push_back(P);
          if (j==wierzcholki)
            {
              dane.push_back(K);
              Pp = konwertuj(Kon+H);
              dane.push_back(Pp);
              dane.push_back(S);
            }       
        }      
      this->promien_max = max;
      this->promien_min = min;
      this->wysokosc = this->skala*3;
      this->i = this->rysownik->draw_polygonal_chain(dane, "green");
     }
     
     bool Plaskowyz:: czy_nad(Wektor<3> S, double R)
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
       
     bool Plaskowyz:: czy_ladowac(Wektor<3> S, double R)
       {
         double h = abs(this->promienmin() - R);
         Wektor<2> X, Y;  //X to dron, Y to plaskowyz
         X[0] = S[0];
         X[1] = S[1];
         Y[0] = (this->srodek)[0];
         Y[1] = (this->srodek)[1];
         Wektor<2> W = X - Y;
         double d = W.dlugosc();
         if ((h >= d )  && (R <= this->promienmin()))
           {
             return 1;
           }
         else 
           {
             return 0;
           }
       }
