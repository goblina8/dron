#ifndef PLASKOWYZ_HH
#define PLASKOWYZ_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Krajobraz.hh"
#include "Rysowanie.hh"

using namespace std;

/*!
 * \file Plaskowyz.hh
 * Plik zawiera klasę Plaskowyz
 */
 
class Plaskowyz: public Rysowanie, public Krajobraz
{
  private:
    /*!
     * \brief klasa dziedzicząca z klas Rysowanie oraz Krajobraz, której pola reprezentują środek i skalę wielkości płaskowyża
     */ 
    Wektor<3> srodek;
    double skala;
  public:
    /*!
     * \brief Konstruktor
     * \param _srodek - mówi o środku tego obiektu 
     * \param _skala - mówi o skali w jakiej obiekt ma powstać
     * \param _rysownik - wskaźnik na obiekt klasy Draw3DAPI
     */ 
    Plaskowyz(Wektor<3> _srodek, double _skala, drawNS::Draw3DAPI * _rysownik);
    /*!
     * \brief funkcja sprawdzająca czy następuje kolizja płaskowyża z obiektem o zadanych wartościach
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi maksymalnym promieniu tego obiektu
     * \return zwraca 1 jeśli kolizja następuje, oraz 0 gdy nie następuje
     */
    bool czy_nad(Wektor<3> S, double R) override;
    /*!
     * \brief funkcja sprawdzająca czy możliwe jest lądowanie na płaskowu obiektem o zadanych wartościach
     * \param S - mówi o środku tego obiektu 
     * \param R - mówi maksymalnym promieniu tego obiektu
     * \return zwraca 1 jeśli lądowanie jest możliwe, oraz 0 gdy nie jest
     */
    bool czy_ladowac(Wektor<3> S, double R) override; 
    /*!
     * \brief funkcja rysująca płaskowyż w gnuplocie
     */
    void rysuj() override; 
    /*!
     * \brief funkcja zmaznująca płaskowyż w gnuplocie
     */
    void zmarz() override;
    /*!
     * \brief funkcja zwracająca środek płaskowyża
     * \return zwraca wektor reprezentujący wartośc środka płaskowyża
     */
    Wektor<3> z_srodek() override {return this->srodek;};
};

#endif
