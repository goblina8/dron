#ifndef MACIERZ_HH
#define MACIERZ_HH
#include <iostream>
#include <vector>
#include "interface.hh"
#include "Wektor.hh"

using namespace std;

/*!
 * \file Macierz.hh
 * Plik zawiera klasę Macierz
 */

template <int ROZMIAR>  
class Macierz
{
  private:
    /*!
     * \brief klasa zawierająca definicję macierzy
     */ 
    vector<Wektor<ROZMIAR>> wiersze;
  public:
    /*!
     * \brief Konstruktor bezparametryczny
     */ 
    Macierz<ROZMIAR>(){Wektor<ROZMIAR> W; for (int i = 0; i < ROZMIAR; i++) {wiersze.push_back(W);};};
    /*!
     * \brief Konstruktor
     * \param kat- mówi o jakim kącie ma stworzyc się macierz 
     * \param os - mówi względem osi ma poiwstać macierz (X,Y,Z)
     */ 
    explicit Macierz<ROZMIAR>(double kat, char os); 
    /*!
     * \brief Konstruktor
     * \param kat- mówi o jakim kącie ma stworzyc się macierz (tylko 2D)
     */ 
    explicit Macierz<ROZMIAR>(double kat); 
    /*!
     * \brief funkcja obliczająca wyznacznik macierzy (2D i 3D)
     * \return zwraca wartość wyznacznika 
     */ 
    double wyznacznik() const;
    /*!
     * \brief operator obsługujący mnożenie macierzy razy wektor
     * \param W - wektor o jaki macierz ma być wymnożona
     * \return zwraca macierz po przemnożeniu (wektor)
     */ 
    Wektor<ROZMIAR> operator * (const Wektor<ROZMIAR> & W) const;
    /*!
     * \brief operator obsługujący mnożenie macierzy razy macierz
     * \param M - macierz o jaką macierz ma być wymnożona
     * \return zwraca macierz po przemnożeniu
     */ 
    Macierz operator * (const Macierz<ROZMIAR> & M2) const; 
    /*!
     * \brief operator obsługujący wypisanie wartości zawartości wiersza macierzy
     * \param i - informuje o tym, który wiersz ma być wypisany
     * \return zwraca wektor zawierający dany wiersz
     */ 
    const Wektor<ROZMIAR> & operator [] (int i) const; 
    /*!
     * \brief operator obsługujący zmianę wartości zawartości wiersza macierzy
     * \param i - informuje o tym, który wiersz ma być zmieniony
     */ 
    Wektor<ROZMIAR> operator [] (int i); 
};

/*!
 * \brief funkcja wypisująca zawartość macierzy
 * \param strm - odpowiada za to, aby został on wypisany w opowiednim miejscu
 * \param M - macierz, która ma być wyświetlona
 * \return ciąg dalszy strm
 */ 
template <int ROZMIAR>
std::ostream& operator << (std::ostream &strm, const Macierz<ROZMIAR> &M);

#endif
