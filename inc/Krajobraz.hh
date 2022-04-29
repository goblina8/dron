#ifndef KRAJOBRAZ_HH
#define KRAJOBRAZ_HH
#include <iostream>
#include <vector>
#include <math.h>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"

using namespace std;

/*!
 * \file Krajobraz.hh
 * Plik zawiera klasę Krajobraz 
 */

class Krajobraz 
{
  protected:
    /*!
     * \brief klasa, której pola rezprezentują paramentry wielkości obiektu krajobrazu
     */
    double promien_min;
    double promien_max;
    double wysokosc;
  public:
    /*!
     * \brief virtualna bezparametryczna funkcja zwracająca środek obiektu
     * \return zwraca wartość środka obiektu
     */
    virtual Wektor<3> z_srodek() = 0; 
    /*!
     * \brief virtualna funkcja zmazująca obrazek w gnuplocie
     */
    virtual void zmarz() = 0;  
    /*!
     * \brief virtualna funkcja sprawdzająca czy nad obiektem znajduje się jakiś element
     * \param S - informuje o środku obiektu, dla którego dokonujemy sprawdzenia
     * \param R - informuje o maksymalnym promieniu obiektu, dla którego dokonujemy sprawdzenia
     * \return jeśli pod obiektem znajduje się obiekt zwraca 1, w przeciwnym wypadku zwraca 0
     */
    virtual bool czy_nad(Wektor<3> S, double R) = 0; 
    /*!
     * \brief funkcja sprawdzająca czy lądowanie jest możliwe
     * \param S - informuje o środku obiektu, dla którego dokonujemy sprawdzenia
     * \param R - informuje o maksymalnym promieniu obiektu, dla którego dokonujemy sprawdzenia
     * \return jeśli lądowanie jest możliwe zwraca 1, w przeciwnym wypadku zwraca 0
     */
    virtual bool czy_ladowac(Wektor<3> S, double R) = 0; 
    /*!
     * \brief funkcja zwracająca minimalny promień obiektu
     * \return zwraca wartość parametru promien_min
     */
    double promienmin() {return this->promien_min;}
    /*!
     * \brief funkcja zwracająca maksymalny promień obiektu
     * \return zwraca wartość parametru promien_max
     */
    double promienmax() {return this->promien_max;}
    /*!
     * \brief funkcja zwracająca wysokość obiektu
     * \return zwraca wartość parametru wysokosc
     */
    double h() {return this->wysokosc;}
};

#endif
