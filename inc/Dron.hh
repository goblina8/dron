#ifndef DRON_HH
#define DRON_HH
#include <iostream>
#include "interface.hh"
#include "Wektor.hh"
#include "Uklad.hh"
#include "Macierz.hh"
#include "Graniastoslup.hh"
#include "Prostopadloscian.hh"
#include "Uklad.hh"
#include "Rysowanie.hh"
#include "Krajobraz.hh"

using namespace std;

/*!
 * \file Dron.hh
 * Plik zawiera klasę Dron dziedzicącą z klas: Uklad oraz Rysowanie
*/

class Dron: public Uklad, public Rysowanie, public Krajobraz
  {
    private:
      /*!
       * \brief klasa, której pola rezprezentują elementy tworzace drona
       */
      Prostopadloscian korpus;
      Graniastoslup G1;         //wirniki
      Graniastoslup G2;
      Graniastoslup G3;
      Graniastoslup G4;
      double skala;  
      double kat = 0; 
    public:
      /*!
       * \brief Konstruktor
       * \param S - obiekt klasy Wektor<3>
       * \param O - obiekt klasy Macierz<3>
       * \param skala - double informujący o rozmiarze, w jakim dron ma powstać
       * \param rysownik - wskaźnik na obiekt klasy Draw3DAPI
       */
      Dron(Wektor<3> S, Macierz<3> O, double skala, drawNS::Draw3DAPI * rysownik);
      /*!
       * \brief przemieszcza drona o zadane wartości
       * \param kat - podany w stopniach informuje o kącie o jaki dron ma się obrócić
       * \param wysokosc - informuje o odleglości na jaką dron ma się wznieść podczas lotu
       * \param odleglosc - informuje o odleglosci o jaką dron ma sie przemiescić
       */      
      void lec(double kat, double wysokosc, double odleglosc);
      /*!
       * \brief obraca wirniki drona w miejscu
       */
      void wirniki();
      /*!
       * \brief unosi drona w powietrze
       * \param wysokosc - świadczy o tym, na jaką wysokość dron ma się wzieść
       */
      void gora(double wysokosc);
      /*!
       * \brief opuszcza drona
       * \param wysokosc - świadczy o tym, o jaką wysokość dron ma się opuścić
       */
      void dol(double wysokosc);
      /*!
       * \brief przemieszcza drona w płaszczyźnie poziomej
       * \param wysokosc - świadczy o odleglości, którą dron ma pokonać
       */
      void prosto(double kat, double odleglosc);
      /*!
       * \brief obraca drona w miejscu
       * \param kat - świadczy o tym, o jaki kąt w stopniach dron ma się obrócić
       */
      void obrot(double kat);
      /*!
       * \brief funkcja rysująca drona w gnuplocie
       */
      void rysuj() override;
      /*!
       * \brief funkcja sprawdzajaca czy pod dronem znajduje się jakiś obiekt
       * \param S - mówi o środku obiektu znajdującego się nad dronem
       * \param R - mówi o maksymalnym promieniu obiektu znajdującego się nad dronem
       * \return zwraca 1 gdy jest możliwe, a w przeciwnym wypadku zwraca 0
       */
      bool czy_nad(Wektor<3> S, double R) override;
      /*!
       * \brief sprawdza czy na obiekcie pod dronem możliwe jest wylądowanie
       * \param S - mówi o środku obiektu znajdującego się nad dronem
       * \param R - mówi o maksymalnym promieniu obiektu znajdującego się nad dronem
       * \return zwraca 1, gdy jest możliwe, a w przeciwnym wypadku zwraca 0
       */
      bool czy_ladowac(Wektor<3> S, double R) override;
      /*!
       * \brief funkcja zwracająca id drona
       * \return zwraca id drona
       */
      uint id() {return this->i;}
      /*!
       * \brief bezparametryczna funkcja podająca punkt środka drona
       * \return zwraca obiekt klasy Wektor<3>
       */
      Wektor<3> z_srodek() override {return this->srodek;}
      /*!
       * \brief abstrakcyjna bezparametryczna funkcja zmazująca drona z gnuplota
       */
      void zmarz() override;
       /*!
       * \brief funkcja pokajaca kąt o jaki dron jest już obrócony (gdzie patrzy)
       * \return zwraca kąt obrotu drona
       */
      double z_kat() {return this->kat;}
      /*!
       * \brief funkcja ustawiająca "punkt patrzenia" drona (kat)
       * \param kat - mowi o kącie (w stopniach) o jaki obraca się dron
       */
      void s_kat(double kat) {this->kat+=kat; if (this->kat >= 360) {this->kat-=360;}}
  };

#endif

