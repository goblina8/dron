#ifndef POWIERZCHNIA_HH
#define POWIERZCHNIA_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Rysowanie.hh"

using namespace std;

/*!
 * \file Powierchnia.hh
 * Plik zawiera klasę Powierzchnia
 */

class Powierzchnia: public Rysowanie
{
  private:
    /*!
     * \brief klasa dziedzicząca z klasy Rysowanie, której pole reprezentuje wysokość, na której płaszczyzna ma się znaleźć
     */
    double h;
  public:
     /*!
     * \brief Konstruktor
     * \param _h - informuje o wysokości na jakiej płaszczyna ma się znaleźć
     * \param _rysownik - wskaźnik na obiekt dlasy Draw3DAPI
     */
    Powierzchnia (double _h, drawNS::Draw3DAPI * _rysownik) {rysownik = _rysownik; h = _h; i = -1;}
    /*!
     * \brief funkcja rysująca płaszczyznę
     */
    void rysuj() override;
    /*!
     * \brief bezparametryczny konstruktor
     */
    Powierzchnia() {};
};

#endif
