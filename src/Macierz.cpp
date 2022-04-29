#include "Macierz.hh"
#include "Wektor.hh"
#include "interface.hh"
#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.14159265

using namespace std;
    
  template <int ROZMIAR>  
  Macierz<ROZMIAR>:: Macierz(double kat, char os)
    {
      switch (ROZMIAR)
        {
          case 2: // wybrana os nie ma znaczenia
            {  
              Wektor<ROZMIAR> W1 {cos(kat*PI/180), -sin(kat*PI/180)};
              wiersze.push_back(W1);
              Wektor<ROZMIAR> W2 {sin(kat*PI/180),cos(kat*PI/180)};
              wiersze.push_back(W2);
              break;
            }
          case 3:
            {
              if (os == 'X')
                {
                   Wektor<ROZMIAR> W1 {1, 0, 0};
                   wiersze.push_back(W1);
                   Wektor<ROZMIAR> W2 {0, cos(kat*PI/180), -sin(kat*PI/180)};
                   wiersze.push_back(W2); 
                   Wektor<ROZMIAR> W3 {0, sin(kat*PI/180), cos(kat*PI/180)};
                   wiersze.push_back(W3); 
                 }
              else if (os == 'Y')
                 {
                   Wektor<ROZMIAR> W1 {cos(kat*PI/180), 0, sin(kat*PI/180)};
                   wiersze.push_back(W1);
                   Wektor<ROZMIAR> W2 {0, 1, 0};
                   wiersze.push_back(W2); 
                   Wektor<ROZMIAR> W3 {-sin(kat*PI/180), 0, cos(kat*PI/180)};
                   wiersze.push_back(W3); 
                 }  
               else if (os == 'Z')
                 {
                   Wektor<ROZMIAR> W1 {cos(kat*PI/180), -sin(kat*PI/180), 0};
                   wiersze.push_back(W1);
                   Wektor<ROZMIAR> W2 {sin(kat*PI/180), cos(kat*PI/180), 0};
                   wiersze.push_back(W2); 
                   Wektor<ROZMIAR> W3 {0, 0, 1};
                   wiersze.push_back(W3); 
                 }
               else
                 {
                   throw std::logic_error("Blednie podana os obrotu");
                 }
               break;
            }
          default:
            {
              throw std::logic_error("Program nie tworzy macierzy hiperobrotow");
            }
       }
    } 
  
  template <int ROZMIAR>  
  Macierz<ROZMIAR>:: Macierz(double kat)
    {
      switch (ROZMIAR)
        {
          case 2: 
            {  
              Wektor<ROZMIAR> W1 {cos(kat*PI/180), -sin(kat*PI/180)};
              wiersze.push_back(W1);
              Wektor<ROZMIAR> W2 {sin(kat*PI/180),cos(kat*PI/180)};
              wiersze.push_back(W2);
              break;
            }
          case 3:
            {
              Wektor<ROZMIAR> W1 {cos(kat*PI/180), -sin(kat*PI/180), 0};
              wiersze.push_back(W1);
              Wektor<ROZMIAR> W2 {sin(kat*PI/180), cos(kat*PI/180), 0};
              wiersze.push_back(W2); 
              Wektor<ROZMIAR> W3 {0, 0, 1};
              wiersze.push_back(W3); 
              break;
            }
          default:
            {
              throw std::logic_error("Program nie tworzy macierzy hiperobrotow");
            }
       }
    } 
  
  template <int ROZMIAR>  
  const Wektor<ROZMIAR> & Macierz<ROZMIAR>:: operator [] (int i) const //get
    {
      if ((i >= 0) || (i < ROZMIAR))
        {
          return this->wiersze[i];
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
    }
    
  template <int ROZMIAR>  
  Wektor<ROZMIAR> Macierz<ROZMIAR>:: operator [] (int i)  //set
    {
      if ((i >= 0) || (i < ROZMIAR))
        {
          return (*this).wiersze[i];
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
    }

  template <int ROZMIAR>  
  Wektor<ROZMIAR> Macierz<ROZMIAR>:: operator * (const Wektor<ROZMIAR> & W) const
    {
      Wektor<ROZMIAR> Result;
      double wynik = 0;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          for (int j = 0; j < ROZMIAR; j++)
            {
              wynik = wynik + this->wiersze[i][j] * W[j];  
            }  
          Result[i] = wynik;
          wynik = 0;
        } 
      return Result; 
    }
     
  template <int ROZMIAR>  
  Macierz<ROZMIAR> Macierz<ROZMIAR>:: operator * (const Macierz<ROZMIAR> & M2) const
    {
      Macierz<ROZMIAR> Result;
      double wynik = 0;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          for (int j = 0; j < ROZMIAR; j++)
            {
              for (int k = 0; k < ROZMIAR; k++)
                {
                  wynik = wynik + this->wiersze[i][k] * M2[k][j];     
                }    
            Result.wiersze[i][j] = wynik;
            wynik = 0;
            }  
        } 
      return Result; 
    }
  
  template <int ROZMIAR>  
  double Macierz<ROZMIAR>:: wyznacznik() const 
    {
      switch (ROZMIAR)
        {
          case 2:
            {
              return (((*this)[0][0] * (*this)[1][1] ) - ((*this)[0][1] * (*this)[1][0]));
            }
          case 3:
            {
              return (((*this)[0][0] * (*this)[1][1] * (*this)[2][2]) 
              + ((*this)[0][1] * (*this)[1][2] * (*this)[2][0]) 
              + ((*this)[0][2] * (*this)[1][0] * (*this)[2][1]) 
              - ((*this)[2][0] * (*this)[1][1] * (*this)[0][2]) 
              - ((*this)[2][1] * (*this)[1][2] * (*this)[0][0]) 
              - ((*this)[2][2] * (*this)[1][0] * (*this)[0][1]));
            }
          default:
            { 
               throw std::logic_error("Wyznacznik liczony tylko dla macierzy 2x2 i 3x3");
            }
        }
    }
    
  template <int ROZMIAR>  
  std::ostream& operator << (std::ostream &strm, const Macierz<ROZMIAR> &M)
    {
      strm << '[' << '[';
      for (int i = 0; i < ROZMIAR; i++)
        {
          for (int j = 0; j < ROZMIAR; j++)
            {
              if (j == 0)
                {
                  strm << '['; 
                  strm << M[i][j] << ','; 
                }
              else if (j == ROZMIAR-1)
                {
                  strm << M[i][j]; 
                }
              else
                { 
                  strm << M[i][j] << ','; 
                }
            } 
            if (i == ROZMIAR-1)
              {
                strm << "]";
              }
            else
              {
                strm << "]" << ",";
              }
        }
      strm << "]";
      return strm;
    }
    
template class Macierz<2>;
template class Macierz<3>;
template class Macierz<6>;
template std::ostream& operator << (std::ostream &strm, const Macierz<2> &M);
template std::ostream& operator << (std::ostream &strm, const Macierz<3> &M);
template std::ostream& operator << (std::ostream &strm, const Macierz<6> &M);
