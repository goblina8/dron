#ifndef WZGORZE_HH
#define WZGORZE_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"

using namespace std;

/*!
 * \file Wzgorze.hh
 * Plik zawiera klasę Wzgorze
 */
 
class Wzgorze: public Rysowanie, public Krajobraz
{
  private:
    /*!
     * \brief klasa dziedzicząca z klas Krajobraz i Prostopadłościan, której pole reprezentuje skalę w jakiej ma on powstać
     */
    Wektor<3> srodek;
    double skala;
  public:
    /*!
     * \brief bezparametryczny konstruktor
     */
    Wzgorze() {};
    /*!
     * \brief Konstruktor
     * \param _srodek - mówi o środku tego obiektu 
     * \param _skala - mówi o skali w jakiej obiekt ma powstać
     * \param rysownik - wskaźnik na klasę Draw3DAPI
     * \return zwraca zawsze 1
     */
    Wzgorze(Wektor<3> _srodek, double _skala, drawNS::Draw3DAPI * rysownik);
    /*!
     * \brief funkcja sprawdzająca czy nad wzgórzem znajduje się obiekt o danych współrzędnych
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi o maksymalnym promieniu tego obiektu
     * \return zwraca 1, kiedy obiekt znajduje się nad wzgórzem, w przeciwnym wypadku zaś zwraca 0
     */ 
    bool czy_nad(Wektor<3> S, double R) override;
    /*!
     * \brief funkcja sprawdzająca czy na wzgórzu może lądować dany obiekt
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi o maksymalnym promieniu tego obiektu
     * \return zawsze zwraca 0
     */ 
    bool czy_ladowac(Wektor<3> S, double R) override;
    /*!
     * \brief funkcja rysująca wzgórze w gnuplocie
     */ 
    void rysuj() override; 
    /*!
     * \brief funkcja zmazująca wzgórze w gnuplocie
     */ 
    void zmarz() override;
    /*!
     * \brief funkcja zwracająca środek wzgórza
     * \return zwraca wektor reprezentujący środek wzgórza
     */ 
    Wektor<3> z_srodek() override {return this->srodek;};
};

#endif

/*!
 * \brief funkcja obliczająca odległość między 2 punktami na płaszczyźnie
 * \param W - mówi o pierwszym punkcie
 * \param V - mówi o drugim punkcie
 * \return zwraca wartość odległości między punktami
 */ 
double promien(Wektor<2> W, Wektor<2> V);
