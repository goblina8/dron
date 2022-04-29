#include "Prostopadloscian.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "gnuplot.hh"
#include "Uklad.hh"
#include "interface.hh"
#include <iostream>
#include <cmath>

using namespace std;

  void Prostopadloscian:: zmazuj()
    {
      (this->rysownik)->erase_shape(this->i);
    }
    
  void Prostopadloscian:: rysuj()
    { 
      (this->rysownik)->erase_shape(this->i);
      drawNS::Point3D P1(0,0,0), P2(0,0,0), P3(0,0,0), P4(0,0,0), P5(0,0,0), P6(0,0,0), P7(0,0,0), P8(0,0,0);
      P1=konwertuj((*this)[1]);
      P2=konwertuj((*this)[2]);
      P3=konwertuj((*this)[3]);
      P4=konwertuj((*this)[4]);
      P5=konwertuj((*this)[5]);
      P6=konwertuj((*this)[6]);
      P7=konwertuj((*this)[7]);
      P8=konwertuj((*this)[8]);
      std::vector<drawNS::Point3D> dane;
      dane.push_back(P1);
      dane.push_back(P2);
      dane.push_back(P3);
      dane.push_back(P4);
      dane.push_back(P1);
      dane.push_back(P5);
      dane.push_back(P6);
      dane.push_back(P2);
      dane.push_back(P6);
      dane.push_back(P7);
      dane.push_back(P3);
      dane.push_back(P7);
      dane.push_back(P8);
      dane.push_back(P4);
      dane.push_back(P8);
      dane.push_back(P5);  
      if (this->co == 'd')
        {
          (this->i) = (this->rysownik)->draw_polygonal_chain(dane, "blue");
        }
      else
       {
         (this->i) = (this->rysownik)->draw_polygonal_chain(dane, "red");
       }
    }
    
  Prostopadloscian Prostopadloscian:: rotacja(double kat, char os) const 
    {
      Macierz<3> M(kat, os);
      Prostopadloscian P(this->srodek, M*this->orient, this->x, this->y, this->z, this->rysownik, this->i, this->co);
      return P;
    }
    
  Prostopadloscian Prostopadloscian:: translacja(Wektor<3> W) const
    {
      Prostopadloscian P(this->srodek, this->orient, this->x, this->y, this->z, this->rysownik, this->i, this->co);
      return P;
    }
  Prostopadloscian::Prostopadloscian(Wektor<3> S, Macierz<3> O, double x, double y, double z, drawNS::Draw3DAPI * _rysownik, int i, char co): Uklad(S,O)
    {
      this->x = x;
      this->y = y;
      this->z = z;
      this->rysownik = _rysownik;
      this->i = i;
      Wektor<3> poprawka{0,0,z};
      this->srodek = this->srodek+poprawka;
      this->co = co;
    }
    
  std::ostream& operator << (std::ostream &strm, const Prostopadloscian &P)
    { 
      strm << "p1 = " << P[1] << endl;
      strm << "p2 = " << P[2] << endl;
      strm << "p3 = " << P[3] << endl;
      strm << "p4 = " << P[4] << endl;
      strm << "p5 = " << P[5] << endl;
      strm << "p6 = " << P[6] << endl;
      strm << "p7 = " << P[7] << endl;
      strm << "p8 = " << P[8] << endl;
      return strm;
    }
    
  const Wektor<3> & Prostopadloscian:: operator [] (int i) const //get
    {
      Wektor<3> W1{-this->x,-this->y,this->z}; 
      Wektor<3> W2{-this->x,this->y,this->z};
      Wektor<3> W3{this->x,this->y,this->z};
      Wektor<3> W4{this->x,-this->y,this->z};
      Wektor<3> W5{-this->x,-this->y,-this->z};
      Wektor<3> W6{-this->x,this->y,-this->z};
      Wektor<3> W7{this->x,this->y,-this->z};
      Wektor<3> W8{this->x,-this->y,-this->z};
      static Wektor<3> p1,p2,p3,p4,p5,p6,p7,p8;
      p1=((this->orient)*W1+((this->srodek)));
      p2=((this->orient)*W2+((this->srodek)));
      p3=((this->orient)*W3+((this->srodek)));
      p4=((this->orient)*W4+((this->srodek)));
      p5=((this->orient)*W5+((this->srodek)));
      p6=((this->orient)*W6+((this->srodek)));
      p7=((this->orient)*W7+((this->srodek)));
      p8=((this->orient)*W8+((this->srodek)));   
     
      switch (i)
        {
          case 1:
            {
              return p1;
              break;
            }
          case 2:
            {
              return p2;
              break;
            }
          case 3:
            {
              return p3;
              break;
            }
          case 4:
            {
              return p4;
              break;
            }
          case 5:
            {
              return p5;
              break;
            }
          case 6:
            {
              return p6;
              break;
            }
          case 7:
            {
              return p7;
              break;
            }
          case 8:
            {
              return p8;
              break;
            }
          case 0:
            { 
              return this->srodek;
              break;
            }
          default:  
            {
              throw std::logic_error("Błąd indeksu");
              break;
            }
         }
    }
    
  const Macierz<3> & Prostopadloscian:: operator () (int i) const //get
    {
      switch (i)
        {
          case 0:
            { 
              return this->orient;
              break;
            }
          default:  
            {
              throw std::logic_error("Błąd indeksu");
              break;
            }
        }
    }
   
  Macierz<3> & Prostopadloscian:: operator () (int i) //set
    {
      if ((i == 0))
        {
          return (*this).orient;
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
     }
    
