#ifndef SCENA_HH
#define SCENA_HH

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <list>
#include "interface.hh"
#include "gnuplot.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "Uklad.hh"
#include "Dron.hh"
#include "Krajobraz.hh"

using namespace std;

/*!
 * \file Scena.hh
 * Plik zawiera klasę Scena 
 */

class Scena 
  {
    private:
      /*!
       * \brief klasa, której pola rezprezentują scenę, na której znajdują się drony, krajobraz a także informujące o aktualnych parametrach dotyczacych zdarzen majacych na niej miejsce
       */
      std::vector<Krajobraz*> el_krajobrazu;
      std::vector<Dron*> el_dronow;
      double h;
      drawNS::Draw3DAPI * rysownik;
      int i = -1;       //numer drona który aktualnie jest wybrany przez użytkowanika do wykonywania jakichś akcji
      int j = -1;       //numer indeksu przeszkody nad którą można lądowac w danym momencie (dron lub krajobraz)
      char c = 'l';     //d jesli lądujemy nad dronem, k jesli nad krajobrazem, n jesli nie mozna ladowac, l jeśli ląduje się na powierzchni
    public:
      /*!
       * \brief funkcja obslugujaca menu dla użytowanika
       */
      void menu(); 
      /*!
       * \brief funkcja odpowiedzialna za tworzenie animacji ruchu dronów
       * \param kat - informuje o tym, o jaki kąt dron ma sie obrócic
       * \param odleglosc - informuje o tym, o jaką ogleglość dron ma sie przesunąc
       * \param wysokosc - mówi na jaka wysokość dron ma się wznieść
       * \param D - wskaźnik informujący o tym, który dron ma się ruszyć
       */
      void animacja_ruchu(double kat, double odleglosc, double wysokosc, Dron *D);
       /*!
       * \brief Konstruktor
       * \param _h - mówi o tym, na jakiej wysokości powstaje scena
       * \param _rysownik - wskaźnik na obiekt klasy Draw3DAPI 
       */
      Scena(double _h, drawNS::Draw3DAPI * _rysownik) {h = _h; rysownik = _rysownik;};      
       /*!
       * \brief funkcja sprawdzajaca czy występuje kolizja między elementami sceny a przedmiotem o zadanych parametrach
       * \param S - mówi o środku obiektu, którego kolizje sprawdzamy
       * \param R - mówi o maksymalnym promieniu obiektu, którego kolizję sprawdzamy
       * \return zwraca 1 gdy zachodzi kolizja, a w przeciwnym wypadku zwraca 0
       */
      bool sprawdz_kolizje(Wektor<3> S, double R);
       /*!
       * \brief funkcja sprawdzajaca czy istnieje możliwość kolizji drona z elementami krajobrazu(wlecenie w jakiś obiekt)
       * \param wysokosc - mówi o wysokości na jakiej dron miałby się przemieszcać
       * \return zwraca 1 gdy jest możliwośc zajścia kolizji, a w przeciwnym wypadku zwraca 0
       */
      bool sprawdz_kolizje_h(double wysokosc);
       /*!
       * \brief funkcja obsługująca menu dodawania obiektów do sceny
       */
      void dodaj_element();
       /*!
       * \brief funkcja usuwająca element krajobrazu
       * \param id - informuje o numerze indeksu elementu, który należy usunąć
       */
      void usun_element(int id);   
       /*!
       * \brief funkcja usuwająca drona 
       * \param id - informuje o numerze indeksu drona, który należy usunąć
       */
      void usun_drona(int id);
       /*!
       * \brief funkcja wypisująca wszytskie elementy krajobrazu znajdujące się na scenie
       */
      void pokaz_elementy();
       /*!
       * \brief funkcja wypisująca wszystkie drony znajdujące się na scenie
       */
      void pokaz_drony();
  };
  
#endif
