#ifndef WEKTOR_HH
#define WEKTOR_HH
#include "interface.hh"
#include "gnuplot.hh"
#include <vector>
#include <iostream>
#include <initializer_list>

using namespace std; 

/*!
 * \file Wektor.hh
 * Plik zawiera klasę Wektor
 */

template <int ROZMIAR>
class Wektor 
{
  private:
   /*!
     * \brief klasa zawierająca definicję wektora oraz aktualne statystyki ilości wszytskich elementów klasy
     */ 
    vector<double> xy;
    inline static uint ile_suma = 0;
    inline static uint ile_aktualnie = 0;
  public:
    /*!
     * \brief funkcja zwracająca ilość świadczącą o sumie wszystkich powstałych wektorów
     * \return zwraca wartość ile_suma
     */ 
    static uint get_suma() {return ile_suma;}
    /*!
     * \brief funkcja zwracająca ilość świadczącą o sumie wszystkich isteniejących wektorów
     * \return zwraca wartość ile_aktualnie
     */ 
    static uint get_aktualne() {return ile_aktualnie;}
    /*!
     * \brief Destruktor
     */ 
    ~Wektor<ROZMIAR>() {ile_aktualnie--;};
    /*!
     * \brief Konstruktor kopiujący
     * \param W - wektor, który ma zostać skopiowany
     */ 
    Wektor<ROZMIAR>(const Wektor<ROZMIAR> &W) : xy(W.xy) {ile_suma++; ile_aktualnie++;};
    /*!
     * \brief Konstruktor bezparamentryczny
     */ 
    Wektor<ROZMIAR> () {for (int i = 0; i < ROZMIAR; i++) {xy.push_back(0.0);} ile_suma++; ile_aktualnie++; } 
    /*!
     * \brief Konstruktor 
     * \param il - lista wartości mających znaleźć się wewnątrz wektora
     */ 
    Wektor<ROZMIAR> (std::initializer_list<double> il): xy(il) {ile_suma++; ile_aktualnie++;};
    /*!
     * \brief operator umożliwiający sumowanie wektorów
     * \param W - wektor mający zostać dodany
     * \return Wartość wektora po zsuwowaniu
     */  
    Wektor<ROZMIAR> operator + (const Wektor<ROZMIAR> & W2) const;
    /*!
     * \brief operator umożliwiający odejmowanie wektorów
     * \param W - wektor mający zostać odjęty
     * \return Wartość wektora po wykonaniu działania
     */  
    Wektor<ROZMIAR> operator - (const Wektor<ROZMIAR> & W2) const;
    /*!
     * \brief operator umożliwiający mnożenie wektora przez liczbę
     * \param d - liczba przez, którą wektor ma być wymnożony
     * \return Wartość wektora po wykonaniu działania
     */  
    Wektor<ROZMIAR> operator * (const double & d) const;
    /*!
     * \brief operator umożliwiający dzielenie wektora przez liczbę
     * \param d - liczba przez, którą wektor ma być podzielony
     * \return Wartość wektora po wykonaniu działania
     */  
    Wektor<ROZMIAR> operator / (const double & d) const;
    /*!
     * \brief operator zwracający wartości danego miejsca wektora
     * \param i - liczba informująca o mającym zostać zwróconym elemencie wektora
     * \return wartość danego miejsca wektora
     */  
    const double & operator [] (int i) const; 
    /*!
     * \brief operator umożliwiający mnożenie wektora przez wektor
     * \param W - wektor przez, który wektor ma być wymnożony
     * \return Wartość po wykonaniu działania
     */ 
    double operator * (const Wektor<ROZMIAR> & W2) const; 
    /*!
     * \brief operator umożliwiający zmianę wartości zadanego elementu wektora
     * \param i - liczba informująca o mającym zostać zmienione w wektorze
     */  
    double & operator [] (int i); 
    /*!
     * \brief operator zwracający wartośść modułu wektora
     * \return wartość modułu wektora
     */  
    double dlugosc() const; 
};

/*!
 * \brief funkcja pozwalająca uzytkownikowi wpisać wartośc wektora
 * \param strm - odpowiada za to, aby został on wpisany w opowiednim miejscu
 * \param W - wektor, którego zawartość ma być wpisana
 * \return ciąg dalszy strm
 */ 
template <int ROZMIAR>
std::istream& operator >> (std::istream &strm, Wektor<ROZMIAR> &W);

/*!
 * \brief funkcja wypisująca zawartość wektora
 * \param strm - odpowiada za to, aby został on wypisany w opowiednim miejscu
 * \param W - wektor, który ma być wyświetlony
 * \return ciąg dalszy strm
 */ 
template <int ROZMIAR>
std::ostream& operator << (std::ostream &strm, const Wektor<ROZMIAR> &W);

/*!
 * \brief funkcja konwertująca wektor na Poind3D potrzebny do obsługi API
 * \param W - wektor, który ma być przekonwertowany
 * \return Point3D
 */ 
drawNS::Point3D konwertuj(Wektor<3> W);

#endif
