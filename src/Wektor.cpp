#include "Wektor.hh"
#include "interface.hh"
#include "gnuplot.hh"
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
  
  template <int ROZMIAR>
  Wektor<ROZMIAR> Wektor<ROZMIAR>::  operator + (const Wektor<ROZMIAR> & W2) const
    {
      Wektor<ROZMIAR> Result;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          Result.xy[i] = this->xy[i] + W2.xy[i]; 
        }
      return Result;
    }
  
  template <int ROZMIAR>
  Wektor<ROZMIAR> Wektor<ROZMIAR>:: operator - (const Wektor<ROZMIAR> & W2) const
    {
     Wektor<ROZMIAR> Result;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          Result.xy[i] = this->xy[i] - W2.xy[i]; 
        }
      return Result;
    }
  
  template <int ROZMIAR>
  double Wektor<ROZMIAR>:: operator * (const Wektor<ROZMIAR> & W2) const
    {
      double Result = 0;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          Result = Result + (this->xy[i] * W2.xy[i]); 
        }
      return Result;
    }
  
  template <int ROZMIAR>
  Wektor<ROZMIAR> Wektor<ROZMIAR>:: operator * (const double & d) const
    {
      Wektor<ROZMIAR> Result;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          Result.xy[i] = this->xy[i] * d; 
        } 
      return Result;
    }
  
  template <int ROZMIAR>
  Wektor<ROZMIAR> Wektor<ROZMIAR>:: operator / (const double & d) const
    {
      Wektor<ROZMIAR> Result;
      for (int i = 0; i < ROZMIAR; i++)
        { 
          Result.xy[i] = this->xy[i] / d; 
        }
      return Result;
    }
  
  template <int ROZMIAR>
  const double & Wektor<ROZMIAR>:: operator [] (int i) const //get
    { 
      if ((i >= 0) || (i < ROZMIAR))
        {
          return this->xy[i];
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
     }
  
  template <int ROZMIAR>
  double & Wektor<ROZMIAR>:: operator [] (int i) //set 
    {
      if ((i >= 0) || (i < ROZMIAR))
        {
          return (*this).xy[i];
        }
      else
        {
          throw std::logic_error("Błąd indeksu");
        }
     }
  
  template <int ROZMIAR>
  std::ostream& operator << (std::ostream &strm, const Wektor<ROZMIAR> &W) 
    {
      strm << '['; 
      for (int i = 0; i < ROZMIAR - 1; i++)
        {
          strm << W[i] << ','; 
        }
      strm << W[ROZMIAR-1]; 
      strm << ']';
      return strm;
    }
  
  template <int ROZMIAR>
  std::istream& operator >> (std::istream &strm, Wektor<ROZMIAR> &W)  
    {
      char z;
      double a;
      strm >> z; 
      if (z != '[')
        {
          strm.setstate(std::ios::failbit);
        }
      for (int i = 0; i < ROZMIAR-1; i++)
        {
          strm >> a;
          W[i] = a;
          strm >> z; 
          if (z != ',')
            {
              strm.setstate(std::ios::failbit);
            }
        }
      strm >> a;
      W[ROZMIAR-1] = a;
      strm >> z;
      if (z != ']')
        {
          strm.setstate(std::ios::failbit);
        }
      return strm;
    }
  
 template <int ROZMIAR>
 double Wektor<ROZMIAR>:: dlugosc() const
   {
     double Result = 0;
     for (int i = 0; i < ROZMIAR; i++)
       {
         Result = Result + this->xy[i] * this->xy[i];
       }
     return sqrt(Result);
   }
   
 //template<>
 drawNS::Point3D konwertuj (Wektor<3> W) 
   {
     return drawNS::Point3D(W[0], W[1], W[2]);
   } 

template class Wektor<2>;
template class Wektor<3>;
template class Wektor<6>;
template std::ostream& operator << (std::ostream &strm, const Wektor<2> &W);
template std::istream& operator >> (std::istream &strm, Wektor<2> &W);
template std::ostream& operator << (std::ostream &strm, const Wektor<3> &W);
template std::istream& operator >> (std::istream &strm, Wektor<3> &W);
template std::ostream& operator << (std::ostream &strm, const Wektor<6> &W);
template std::istream& operator >> (std::istream &strm, Wektor<6> &W);
