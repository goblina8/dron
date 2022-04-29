#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include <vector>
#include "interface.hh"
#include "gnuplot.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Uklad.hh"
#include "Rysowanie.hh"

/*!
 * \file Prostopadloscian.hh
 * Plik zawiera klasę Prostopadloscian
 */

class Prostopadloscian: public Uklad, public Rysowanie
{
  protected:
    /*!
     * \brief klasa dziedzicząca z klas Uklad oraz Rysowanie, której pola reprezentują czego częścią jest prostopadłościan, oraz jego wymiary
     */ 
    double x;  //dlugosc 1/2 boku 1
    double y;  //dlugosc 1/2 boku 2
    double z;  //dlugosc 1/2 boku 3
    char co;
  public:
    /*!
     * \brief bezparametryczny konstruktor
     */ 
    Prostopadloscian() {};
    /*!
     * \brief funkcja wykonująca rotację prostopadłościanu
     * \param kat- mówi o jaki kąt ma nastąpic obrót 
     * \param os - mówi względem osi ma nastąpić obrót (X,Y,Z)
     * \return zwraca obrócony prostopadłościan
     */ 
    Prostopadloscian rotacja(double kat, char os) const; 
    /*!
     * \brief funkcja wykonująca translację prostopadłościanu o zadany wektor
     * \param W - mówi o jaki wektor ma się przesunąć prostopadłościan 
     * \return zwraca przesunięty prostopadłościan
     */ 
    Prostopadloscian translacja(Wektor<3> W) const;
    /*!
     * \brief Konstruktor
     * \param S - mówi środku prostopadłościanu
     * \param O - mówi o orientacji prostopadłościanu
     * \param x - mówi o długości prostopadłościanu
     * \param y - mówi o szerokości prostopadłościanu
     * \param z - mówi o wysokości prostopadłościanu
     * \param rysownik - wskaźnik na obiekt klasy Draw3DAPI
     * \param i - mówi o numeru obrazka
     * \param co - informuje o tym, czym jest prostopadłościan (d - częścią drona - wtedy rysuje się na niebiesko, czy nie - wtedy jest czerwony)
     */ 
    Prostopadloscian(Wektor<3> S, Macierz<3> O, double x, double y, double z, drawNS::Draw3DAPI * rysownik, int i, char co); 
    /*!
     * \brief funkcja zwracająca dany wierzchołek prostopadłościanu
     * \param i - mówi o tym, który wierzchołek zwrócić (1-4 górna podstawa, 5-8 dolna)
     * \return zwraca wektor symbolizujący zadany wierzchołek
     */
    const Wektor<3> & operator [] (int i) const; 
    /*!
     * \brief funkcja zwracająca środek prostopadłościanu
     * \param i - mówi o tym, aby zwrócić środek (0)
     * \return zwraca macierz obrotu
     */
    const Macierz<3> & operator () (int i) const; 
    /*!
     * \brief funkcja rysująca prostopadłościan w gnuplocie
     */
    void rysuj() override; 
    /*!
     * \brief funkcja zmazująca prostopadłościan w gnuplocie
     */
    void zmazuj();
    /*!
     * \brief funkcja zmieniająca orientację prostopadłościanu na zadany
     * \param i - mówi o tym aby ustawić macierz obrotu (0)
     */
    Macierz<3> & operator () (int i);  
};

std::ostream& operator << (std::ostream &strm, const Prostopadloscian &P);
/*!
 * \brief funkcja wypisująca wszytskie wierzchołki zadanaego prostopadłościanu
 * \param strm - świadczy o tym, by wypisał się w odpowiednim miejscu
 * \param P - informuje o tym, jaki prostopadłościan ma zostać wypisany
 * \return zwraca ciąg dalszy strm
 */

#endif
