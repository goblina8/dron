#ifndef UKLAD_HH
#define UKLAD_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"
#include "Macierz.hh"

using namespace std;

/*!
 * \file Uklad.hh
 * Plik zawiera klasę Uklad 
 */

class Uklad
{
  protected:
    /*!
     * \brief klasa, której pola rezprezentują orientację w przestrzeni
     */
    Wektor<3> srodek;
    Macierz<3> orient;
  public:
    /*!
     * \brief Konstruktor bezparametryczny
     */
    Uklad() = default;
    /*!
     * \brief Konstruktor 
     * \param S - mówi o środku obiektu który tworzymy
     * \param O - mówi o jego orientacji w przestrzeni
     */
    Uklad(Wektor<3> S, Macierz<3> O) {srodek = S; orient = O;} 
    /*!
     * \brief funkcja dokonująca rotacji obiektu
     * \param nowa - informuje o tym, w jaki sposób rotacja ma być przeprowadzona
     */
    void rotacja_v(Macierz<3> nowa) {orient = orient * nowa;}
    /*!
     * \brief funkcja przesuwająca środek o zadany wektor
     * \param W - wektor o jaki obiekt ma być przesunięty
     */
    void translacja_v(Wektor<3> W) {srodek = srodek+W;}
      /*!
       * \brief funkcja zwracająca wartość środka układu
       * \return zwraca wartość parametru srodek
       */
    Wektor<3> get_srodek(){return srodek;}
      /*!
       * \brief funkcja zwracająca oreintację układu
       * \return zwraca wartość parametru orient
       */
    Macierz<3> get_orient(){return orient;}
       /*!
       * \brief funkcja zmieniająca środek układu
       * \param W - mówi o nowym środku obiektu
       */
    void set_srodek(Wektor<3> W){srodek = W;}
      /*!
       * \brief funkcja zmieniająca orientację obiektu
       * \param S - mówi o nowej orientacji obiektu
       */
    void set_polozenie(Macierz<3> M){orient = M;}
};

#endif
