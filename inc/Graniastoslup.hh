#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

#include <iostream>
#include <vector>
#include "interface.hh"
#include "gnuplot.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Uklad.hh"
#include "Rysowanie.hh"

using namespace std;

/*!
 * \file Graniastoslup.hh
 * Plik zawiera klasę Graniastoslup oraz funkcję wyświetlającą jego wierzchołki 
 */

class Graniastoslup: public Uklad, public Rysowanie
{
  private:
     /*!
      * \brief klasa, której pola rezprezentują paramentry budowy sześciokąta formenego
      */
     double R; 
     double h; 
  public:
    /*!
     * \brief bezparametryczny konstruktor
     */
    Graniastoslup() {};
    /*!
     * \brief funkcja dokonująca rotacji graniastosłupa
     * \param kat - informuje o tym, o jaki kąt ma nastąpić rotacja
     * \param os - informuje względem jakiej osi (X,Y,Z) ma nastąpić obrót
     * \return funkcja zwraca graniastosłup po obrocie
     */
    Graniastoslup rotacja(double kat, char os) const; 
    /*!
     * \brief funkcja przesuwająca graniastosłup o zadany wektor
     * \param W - wektor o jaki ma się przesunąć dany graniastosłup
     * \return funkcja zwraca graniastosłup po przesunięciu
     */
    Graniastoslup translacja(Wektor<3> W) const;
    /*!
     * \brief Konstruktor
     * \param S - informuje o środku graniastosłupa
     * \param O - informuje o orientacji graniastosłupa
     * \param R - informuje o długości od jego środka do wierchołka
     * \param h - informuje o połowie jego wysokości 
     * \param rysownik - wskaźnik na element klasy Draw3API
     * \param i - przechowuje informację o numerze obrazka (by można było go rysować, zmieniać i zmazywać)
     */
    Graniastoslup(Wektor<3> S, Macierz<3> O, double R, double h, drawNS::Draw3DAPI * rysownik, int i); 
    /*!
     * \brief funkcja zwracająca kolejny wierzchołek graniastosłupa (1-6 górna podstawa, 7-12 dolna podstawa)
     * \param i - informuje o numerze wierzchołka, który ma być zwrócony
     * \return funkcja zwraca wektor informujący o współrzędnych zadanego wierchołka
     */
    const Wektor<3> & operator [] (int i) const;
    /*!
     * \brief funkcja rysująca graniastosłup w gnuplocie
     */
    void rysuj() override; 
    /*!
     * \brief funkcja zwracająca macierz obrotu graniastosłupa
     * \param i - informuje o numerze indeksu który ma być zwrócony (0 by dostać macierz obrotu)
     * \return zwraca macierz obrotu
     */
    const Macierz<3> & operator () (int i) const; //get macierz
    /*!
     * \brief funkcja ustawiająca wartość macierzy obrotu
     * \param i - informuje o numerze indeksu, w który ma być ustawiona macierz
     */
    Macierz<3> & operator () (int i); //set macierz
    /*!
     * \brief funkcja ustawiająca wartość środka graniastosłupa
     * \param i - informuje o numerze indeksu, w który ma być ustawiony środek
     */
    Wektor<3> & operator / (int i); //set wektor
    /*!
     * \brief funkcja zmazująca graniastosłup w gnuplocie
     */
    void zmazuj();
};


/*!
 * \brief funkcja wypisująca wszystkie wierzchołki graniastosłupa
 * \param strm - odpowiada za wypisanie w odpowiednim miejscu
 * \param G - graniastosłup, którego wierzchołki mają zostać wyświetlone 
 */
std::ostream& operator << (std::ostream &strm, const Graniastoslup &G);

#endif
