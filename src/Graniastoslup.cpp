#include <iostream>
#include <vector>
#include "interface.hh"
#include "gnuplot.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Uklad.hh"
#include "Graniastoslup.hh"

using namespace std;

void Graniastoslup:: zmazuj()
    {
      (this->rysownik)->erase_shape(this->i);
    }
    
 void Graniastoslup:: rysuj()
    {
      (this->rysownik)->erase_shape(this->i);
      drawNS::Point3D P1(0,0,0), P2(0,0,0), P3(0,0,0), P4(0,0,0), P5(0,0,0), P6(0,0,0), P7(0,0,0), P8(0,0,0), P9(0,0,0), P10(0,0,0), P11(0,0,0), P12(0,0,0);
      P1=konwertuj((*this)[1]);
      P2=konwertuj((*this)[2]);
      P3=konwertuj((*this)[3]);
      P4=konwertuj((*this)[4]);
      P5=konwertuj((*this)[5]);
      P6=konwertuj((*this)[6]);
      P7=konwertuj((*this)[7]);
      P8=konwertuj((*this)[8]);
      P9=konwertuj((*this)[9]);
      P10=konwertuj((*this)[10]);
      P11=konwertuj((*this)[11]);
      P12=konwertuj((*this)[12]);
      std::vector<drawNS::Point3D> dane;
      dane.push_back(P1);
      dane.push_back(P2);
      dane.push_back(P3);
      dane.push_back(P4);
      dane.push_back(P5);
      dane.push_back(P6);
      dane.push_back(P1);
      dane.push_back(P7);
      dane.push_back(P8);
      dane.push_back(P2);
      dane.push_back(P8);
      dane.push_back(P9);
      dane.push_back(P3);
      dane.push_back(P9);
      dane.push_back(P10);
      dane.push_back(P4);
      dane.push_back(P10);
      dane.push_back(P11);  
      dane.push_back(P5); 
      dane.push_back(P11); 
      dane.push_back(P12);
      dane.push_back(P6);
      dane.push_back(P12);
      dane.push_back(P7);    
      this->i = this->rysownik->draw_polygonal_chain(dane, "blue");
     }
 
  Graniastoslup Graniastoslup:: rotacja(double kat, char os) const 
    {
      Macierz<3> M(kat, os);
      Graniastoslup G(this->srodek, M*this->orient, this->R, this->h, this->rysownik, this->i);
      return G;
    }
    
  Graniastoslup Graniastoslup:: translacja(Wektor<3> W) const
    {
      Graniastoslup G(this->srodek+W, this->orient, this->R, this->h, this->rysownik, this->i);
      return G;
    }
  
  Graniastoslup::Graniastoslup(Wektor<3> S, Macierz<3> O, double R, double h, drawNS::Draw3DAPI * rysownik, int i): Uklad(S,O), Rysowanie(rysownik)//set 
    {
      this->srodek = S;
      this->orient = O;
      this->R = R;
      this->h = h;
      this->rysownik = rysownik;
      this->i = i;
    }
    
  std::ostream& operator << (std::ostream &strm, const Graniastoslup &G)
    { 
      strm << "p1 = " << G[1] << endl;
      strm << "p2 = " << G[2] << endl;
      strm << "p3 = " << G[3] << endl;
      strm << "p4 = " << G[4] << endl;
      strm << "p5 = " << G[5] << endl;
      strm << "p6 = " << G[6] << endl;
      strm << "p7 = " << G[7] << endl;
      strm << "p8 = " << G[8] << endl;
      strm << "p9 = " << G[9] << endl;
      strm << "p10 = " << G[10] << endl;
      strm << "p11 = " << G[11] << endl;
      strm << "p12 = " << G[12] << endl;
      return strm;
    }
    
  const Wektor<3> & Graniastoslup:: operator [] (int i) const //get
    {
      static Wektor<3> p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12;
      Macierz<3> M(60);
      Wektor<3> W1{0,this->R,this->h},W2,W3,W4,W5,W6,W7{0,this->R,-this->h},W8,W9,W10,W11,W12;
      W2 = M*W1;
      W3 = M*W2;
      W4 = M*W3;
      W5 = M*W4;
      W6 = M*W5;
      W8 = M*W7;
      W9 = M*W8;
      W10 = M*W9;
      W11 = M*W10;
      W12 = M*W11;
      p1 = ((this->orient)*W1+((this->srodek)));
      p2 = ((this->orient)*W2+((this->srodek)));
      p3 = ((this->orient)*W3+((this->srodek)));
      p4 = ((this->orient)*W4+((this->srodek)));
      p5 = ((this->orient)*W5+((this->srodek)));
      p6 = ((this->orient)*W6+((this->srodek)));
      p7 = ((this->orient)*W7+((this->srodek)));
      p8 = ((this->orient)*W8+((this->srodek)));
      p9 = ((this->orient)*W9+((this->srodek)));
      p10 = ((this->orient)*W10+((this->srodek)));
      p11 = ((this->orient)*W11+((this->srodek)));
      p12 = ((this->orient)*W12+((this->srodek)));
      switch (i)
        {
          case 0: 
            {
              return this->srodek;
              break;
            }
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
          case 9:
            {
              return p9;
              break;
            }
          case 10:
            {
              return p10;
              break;
            }
          case 11:
            {
              return p11;
              break;
            }
          case 12:
            {
              return p12;
              break;
            }
          default:  
            {
              throw std::logic_error("Błąd indeksu1");
              break;
            }
         }
    }
    
  
  const Macierz<3> & Graniastoslup:: operator () (int i) const //get
    {
      if (i == 0)
        {
          return this->orient;
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
     }
  
  Macierz<3> & Graniastoslup:: operator () (int i) //set
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
 
  Wektor<3> & Graniastoslup:: operator / (int i) //set
    {
      if ((i == 0))
        {
          return (*this).srodek;
        }
      else
        {
          throw std::logic_error("Błąd indeksu1");
        }
     }
        
