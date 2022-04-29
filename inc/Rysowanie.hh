#ifndef RYSOWANIE_HH
#define RYSOWANIE_HH
#include <iostream>
#include <vector>
#include "interface.hh"

using namespace std;

/*!
 * \file Rysowanie.hh
 * Plik zawiera klasę Rysowanie
 */
 
class Rysowanie
{
  protected:
    /*!
     * \brief klasa, której pola reprezentują wartości potrzebne do wykonania rysunku w gnuplocie
     */
    int i;
    drawNS::Draw3DAPI * rysownik;
  public:
     /*!
     * \brief virtualna funkcja odpowiadająca za wykonanie rysunku
     */
    virtual void rysuj() = 0;
    /*!
     * \brief Konstruktor
     * \param _rysownik - - wskaźnik na obiekt dlasy Draw3DAPI
     */
    Rysowanie(drawNS::Draw3DAPI * _rysownik) {rysownik = _rysownik; i = -1;}
    /*!
     * \brief bezparametryczny konstruktor
     */
    Rysowanie() {} 
}; 

  #endif
