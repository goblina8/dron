#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include "Wektor.hh"
#include "Macierz.hh"
#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "Powierzchnia.hh"
#include "Uklad.hh"
#include "Dron.hh"
#include "gnuplot.hh"
#include "interface.hh"
#include "Scena.hh"
#include "Rysowanie.hh"
#include "Krajobraz.hh"
#include "Plaskowyz.hh"
#include "Plaskowyz_prost.hh"
#include "Wzgorze.hh"

using namespace std;

int main()
  {
    drawNS::Draw3DAPI * rysownik = new drawNS::APIGnuPlot3D(-250,250,-250,250,-50,350,1000);
    rysownik->change_ref_time_ms(0);
    double h=0;
//WYSOKOSC
    //cout << "Podaj wysokosc plaszyzny" << endl;
    //cin >> h;
//SCENA I INTERFACE
    Scena S(h,rysownik);
    system("clear");
    S.menu();
//KONIEC
    delete rysownik;
    return 0;
  }

