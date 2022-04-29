#ifndef PLASKOWYZ_PROST_HH
#define PLASKOWYZ_PROST_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Prostopadloscian.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"

using namespace std;

/*!
 * \file Plaskowyz_prost.hh
 * Plik zawiera klasę Plaskowyz_prost
 */

class Plaskowyz_prost: public Krajobraz, public Prostopadloscian
{ 
  private:
    /*!
     * \brief klasa dziedzicząca z klas Krajobraz i Prostopadłościan, której pole reprezentuje skalę w jakiej ma on powstać
     */
  public:
    /*!
     * \brief Konstruktor
     * \param S - mówi o środku płaskowyża
     * \param O - mówi o orientacji płaskowyża
     * \param x - mówi o grubości płaskowyża
     * \param y - mówi o szerokości płaskowyża
     * \param z - mówi o wysokości płaskowyża
     * \param _rysownik - wskaźnik na element klasy Draw3DAPI
     * \param i = reprezentuje numer obrazka
     */
    Plaskowyz_prost(Wektor<3> S, Macierz<3> O, double x, double y, double z, drawNS::Draw3DAPI * _rysownik, int i): Prostopadloscian(S,O,x,y,z,_rysownik,-1, 'p') {this->wysokosc = 2*this->z;} 
    /*!
     * \brief funkcja sprawdzająca czy obiekt koliduje z płaskowyżem
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi o maksymalnym promieniu tego obiektu
     * \return zwraca 1 gdy następuje kolizja, 0 w przeciwnym wypadku
     */
    bool czy_nad(Wektor<3> S, double R) override;
    /*!
     * \brief funkcja sprawdzająca czy na płaskowyżu może wylądować obiekt o danych współrzędnych
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi o maksymalnym promieniu tego obiektu
     * \return zwraca zawsze 1
     */
    bool czy_ladowac(Wektor<3> S, double R) override;
    /*!
     * \brief funkcja zwracająca środek obiektu
     * \return wektor mówiący o środku obiektu
     */
    Wektor<3> z_srodek() override {return this->srodek;};
    /*!
     * \brief funkcja zmazująca płaskowyż w gnuplocie
     */
    void zmarz() override;
};
#endif
