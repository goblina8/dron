#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Prostopadloscian.hh"
#include "Plaskowyz_prost.hh"
#include "Prostopadloscian.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"
#include <cmath>

  void Plaskowyz_prost:: zmarz()
    {
      (this->rysownik)->erase_shape(this->i);
    } 
  
  bool Plaskowyz_prost:: czy_nad(Wektor<3> S, double R)
       {
         Wektor<2> X, Y;  //X to dron, Y to plaskowyz
         X[0] = S[0];
         X[1] = S[1];
         Y[0] = (this->srodek)[0];
         Y[1] = (this->srodek)[1];
         Wektor<2> W = X - Y;
         if ((abs(W[0]) <= this->x) && (abs(W[1]) <= this->y))
           {
             return 1;
           }
         else 
           {
             return 0;
           }
       }
       
     bool Plaskowyz_prost:: czy_ladowac(Wektor<3> S, double R)
       {
         return 1;
       }
