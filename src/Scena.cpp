#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <vector>
#include <list>
#include "Prostopadloscian.hh"
#include "Wektor.hh"
#include "Macierz.hh"
#include "gnuplot.hh"
#include "Uklad.hh"
#include "interface.hh"
#include "Scena.hh"
#include "Dron.hh"
#include "Rysowanie.hh"
#include "Krajobraz.hh"
#include "Plaskowyz.hh"
#include "Powierzchnia.hh"
#include "Plaskowyz_prost.hh"
#include "Wzgorze.hh"

    void Scena:: menu()
      {
        //PAKIET STARTOWY GOTOWIEC
        //POWIERCHNIA
        Powierzchnia Pow(h,this->rysownik);
        Pow.rysuj();
        //WEKTORY DLA KRAJOBRAZU   
        Wektor<3> W{0,0,h},O{-160,0,h},N{0,-140,h},L{-10,180, h};
        Macierz<3> M(0);
        double skala=2;
        //DRON    
        Dron *D = new Dron(W, M, skala, this->rysownik);
        D->rysuj();
        el_dronow.push_back(D); 
        //KRAJOBRAZ 
        skala = 15; 
        //WZGORZE
        Wzgorze *X = new Wzgorze(O,skala, this->rysownik);
        X->rysuj();
        el_krajobrazu.push_back(X);
        //PLASKOWYZ
        skala = 18;
        Plaskowyz *Y = new Plaskowyz(L,skala, this->rysownik);
        Y->rysuj();
        el_krajobrazu.push_back(Y);
        //PLASKOWYZ_PROST
        Wektor<3> Q{0,0,3};
        O = O+Q;
        Plaskowyz_prost *Z = new Plaskowyz_prost(N,M,50,40,10,this->rysownik,-1);
        Z->rysuj();
        el_krajobrazu.push_back(Z);
        //DANE DO MENU
        double kat;
        double wysokosc;
        double odleglosc;
        int id;
        char wybor;
        int warunek_wyjscia = 1;
        int dronix;
        //MENU
        while (warunek_wyjscia)
          { 
            cout << "MENU:" << endl;
            cout << "l - podaj w jaki sposob dron ma sie przemiescic" << endl;
            cout << "d - dodaj element" << endl;
            cout << "u - usun krajobraz" << endl;
            cout << "v - usun drona" << endl;
            cout << "e - wyswietl elementy" << endl;
            cout << "k - koniec dzialania programu" << endl;
            cin >> wybor;
            system("clear");
            switch (wybor)
              {
                case 'l':
                  {
                    cout << "Podaj numer indeksu drona wśród dronów, którym chcesz polecieć:" << endl;
                    cin >> dronix;
                    if (dronix > (int)el_dronow.size()-1)
                      {
                        cout << "Nie ma drona o takim indeksie" << endl;
                        break;
                      }
                    else
                      {
                        this->i = dronix;
                      }
                    cout << "Podaj kat o jaki chcesz obrocic dron (w stopniach):" << endl;
                    cin >> kat;
                    if (!((kat >= 0) && (kat <= 360))) 
                      {
                        cout << "Kat musi byc z zakresu 0 360 stopni" << endl;
                        break;
                      }
                    cout << "Podaj wysokosc na jaka dron ma sie wzniesc:" << endl;
                    cin >> wysokosc;
                    if (wysokosc < 0)
                      {
                        cout << "Wysokosc musi byc nieujemna" << endl;
                        break;
                      }
                    cout << "Podaj odleglosc na jaka ma sie oddalic dron:" << endl;
                    cin >> odleglosc;
                    if (odleglosc < 0)
                      {
                        cout << "Odleglosc musi byc nieujemna" << endl;
                        break;
                      }
                    switch (sprawdz_kolizje_h(wysokosc))
                      {
                        case 1:  
                          {
                            cout << "Lot niemozliwy - wystepuje ryzyko kolizji (dron leci na nisko)" << endl;
                            break;
                          }
                         default:
                          {
                            cout << kat << endl;
                            kat +=  this->el_dronow[dronix]->z_kat();
                            this->el_dronow[dronix]->s_kat(kat);
                            cout << kat << endl;
                            Dron *F = this->el_dronow[dronix];
                            animacja_ruchu(kat,odleglosc,wysokosc, F);
                            break;
                          }
                       }
                    break;
                  }
                case 'd':
                  {
                    dodaj_element();
                    break;
                  }
                case 'u':
                  {
                    cout << "Podaj id krajobrazu do usuniecia" << endl;
                    cin >> id;
                    usun_element(id);
                    break;
                  }
                case 'v':
                  {
                    cout << "Podaj id drona do usuniecia" << endl;
                    cin >> id;
                    usun_drona(id);
                    break;
                  }
                case 'e':
                  {
                    pokaz_elementy();
                    cout << endl;
                    pokaz_drony();
                    break;
                  }
                case 'k':
                  {
                    //KONIEC I ILE WEKTOROW
                    int s = W.get_suma();
                    int a = W.get_aktualne();
                    cout << "suma: " << s << " aktualne: " << a << endl;  
                    warunek_wyjscia = 0;
                    break;
                  }
                default:
                  {
                    cout << "Blednie wybrana opcja" << endl << endl;
                    break;
                  }
              }
          }
      } 
                     
     void Scena:: animacja_ruchu(double kat, double odleglosc, double wysokosc, Dron *D)
      {
         int v = 6;
         if (wysokosc != 0)
           {
             double wys_tym = wysokosc;
             if (this->j != -1)
               {
                 if (this->c == 'd')
                   {
                     wys_tym = wysokosc - this->el_dronow[j]->h();
                   }
                 if (this->c == 'k')
                   {
                     wys_tym = wysokosc - this->el_krajobrazu[j]->h();
                   }
                }
             for (int i = 0; i < wys_tym/v; i++)
               {
                 D->gora(wys_tym/(wys_tym/v));
                 D->wirniki();
                 D->rysuj();
                 std::this_thread::sleep_for(std::chrono::milliseconds(100));
               }
           }
           
         if (kat != 0)
           {
             for (int i = 0; i < kat/v; i++)
               {
                 D->obrot(kat/(kat/v));
                 D->wirniki();
                 D->rysuj();
                 std::this_thread::sleep_for(std::chrono::milliseconds(100));
               }
           }
         if (odleglosc != 0)
           { 
             for (int i = 0; i < odleglosc/v; i++)
               {
                 D->prosto(kat,odleglosc/(odleglosc/v));
                 D->wirniki();
                 D->rysuj();
                 std::this_thread::sleep_for(std::chrono::milliseconds(100));
               }
           }
         if (wysokosc != 0)
           {
              if (!sprawdz_kolizje(D->z_srodek(), D->promienmax()))
               {
                 switch (this->c)
                   {
                     case 'd':
                       {
                         double odjac = this->el_dronow[this->j]->h();
                         double cyfra = wysokosc-odjac;
                         for (int i = 0; i < (cyfra/v); i++)
                           {
                             D->dol(cyfra/(cyfra/v));
                             D->wirniki();
                             D->rysuj();
                             std::this_thread::sleep_for(std::chrono::milliseconds(100));
                             wysokosc = cyfra;
                          }
                         break;
                       }
                     case 'k':
                       {
                         double odjac = this->el_krajobrazu[this->j]->h();
                         double cyfra = wysokosc-odjac;
                         for (int i = 0; i < (cyfra/v); i++)
                           {
                             D->dol(cyfra/(cyfra/v));
                             D->wirniki();
                             D->rysuj();
                             std::this_thread::sleep_for(std::chrono::milliseconds(100));
                             wysokosc = cyfra;
                           }
                         break;
                        }
                      case 'l':
                        {
                          for (int i = 0; i < (wysokosc/v); i++)
                             {
                               D->dol(wysokosc/(wysokosc/v));
                               D->wirniki();
                               D->rysuj();
                               std::this_thread::sleep_for(std::chrono::milliseconds(100));
                             }
                          break;
                        } 
                     }
                   }
                else
                  { 
                    cout << "Ladowanie niemozliwe" << endl;
                    for (int i = 0; i < (kat+180)/v; i++)
                      {
                        if (kat < 180)
                          {
                            D->obrot(180/(180/v));
                            D->wirniki();
                            D->rysuj();
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          }
                        else
                          {
                            D->obrot(180/(180/v));
                            D->wirniki();
                            D->rysuj();
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          } 
                      }
                    for (int i = 0; i < odleglosc/v; i++)
                      {
                        if (kat < 180)
                          {
                            D->prosto(kat+180, odleglosc/(odleglosc/v));
                            D->wirniki();
                            D->rysuj();
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          }
                        else
                          {
                            D->prosto(kat+180, odleglosc/(odleglosc/v));
                            D->wirniki();
                            D->rysuj();
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                          } 
                      }
                     double wys_tym = wysokosc;
                     if (this->j != -1)
                      {
                        if (this->c == 'd')
                          {
                             wys_tym = wysokosc - this->el_dronow[j]->h();
                          }
                        if (this->c == 'k')
                          {
                             wys_tym = wysokosc - this->el_krajobrazu[j]->h();
                          }
                       }
                    for (int i = 0; i < wys_tym/v; i++)
                      {
                        D->dol(wys_tym/(wys_tym/v));
                        D->wirniki();
                        D->rysuj();
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                      }
                      cout << "Powrot do punktu wyjściowego" << endl;
                  }
             }
      } 
      
     void Scena:: dodaj_element() 
       {          
         double skala;
         char wybor;
         Wektor<2> v; //srodek [x,y]
         Wektor<3> V; //srodek [x,y,h]
         Wektor<3> XYZ;
         Macierz<3> M(0);
         int warunek_wyjscia = 1;
         system("clear");
         while (warunek_wyjscia)
           { 
             cout << "Co chcesz dodac:" << endl;
             cout << "p - plaskowyz" << endl;
             cout << "r - plaskowyz prostopaloscienny" << endl;
             cout << "w - wzgorze" << endl;
             cout << "d - drona" << endl;
             cout << "c - wroc do menu" << endl;
             cin >> wybor;
             system("clear");
            switch (wybor)
              {
                case 'p':
                  {
                    cout << "Podaj punkt w ktorym chcesz umiescic plaskowyz: [x,y]" << endl;
                    cin >> v;
                    V[0] = v[0];
                    V[1] = v[1];
                    V[2] = this->h;
                    cout << "Podaj skale w jakiej chcesz stowrzyc plaskowyz:" << endl;
                    cin >> skala;
                    Plaskowyz *Y = new Plaskowyz(V,skala,this->rysownik);
                    if (!(sprawdz_kolizje(Y->z_srodek(), Y->promienmax())))
                      {
                        Y->rysuj();
                        el_krajobrazu.push_back(Y);
                        system("clear");                    
                        cout << "Dodano plaskowyz" << endl << endl;
                      }
                    else 
                      {
                        cout << "Dodanie niemozliwe - elementy sie nakladaja" << endl << endl;
                      }
                    break;
                  }
                case 'r':
                  {
                    cout << "Podaj punkt w ktorym chcesz umiescic prostopadloscienny plaskowyz: [x,y]" << endl;
                    cin >> v;
                    V[0] = v[0];
                    V[1] = v[1];
                    V[2] = this->h;
                    cout << "Podaj wymiary jakie ma miec twoj plaskowyz [x,y,z]:" << endl;
                    cin >> XYZ;
                    Plaskowyz_prost *Z = new Plaskowyz_prost(V,M,XYZ[0],XYZ[1],XYZ[2],this->rysownik,-1);
                    if (!(sprawdz_kolizje(Z->z_srodek(), Z->promienmax())))
                      {
                        Z->rysuj();
                        el_krajobrazu.push_back(Z);
                        system("clear");                    
                        cout << "Dodano plaskowyz" << endl << endl;
                      }
                    else 
                      {
                        cout << "Dodanie niemozliwe - elementy sie nakladaja" << endl << endl;
                      }
                  break;
                  }
                case 'w':
                  {
                    cout << "Podaj punkt w ktorym chcesz umiescic wzgorze: [x,y]" << endl;
                    cin >> v;
                    V[0] = v[0];
                    V[1] = v[1];
                    V[2] = this->h;
                    cout << "Podaj skale w jakiej chcesz stowrzyc wzgorze:" << endl;
                    cin >> skala;
                    Wzgorze *X = new Wzgorze(V,skala,this->rysownik);
                    if (!(sprawdz_kolizje(X->z_srodek(), X->promienmax())))
                      {
                        X->rysuj();
                        el_krajobrazu.push_back(X);
                        system("clear");                    
                        cout << "Dodano wzgorze" << endl << endl;
                      }
                    else 
                      {
                        cout << "Dodanie niemozliwe - elementy sie nakladaja" << endl << endl;
                      }
                  break;
                  }
                case 'd':
                  {
                    cout << "Podaj punkt w ktorym chcesz umiescic drona: [x,y]" << endl;
                    cin >> v;
                    V[0] = v[0];
                    V[1] = v[1];
                    V[2] = this->h;
                    cout << "Podaj skale w jakiej chcesz storzyc drona:" << endl;
                    cin >> skala;
                    Dron *G = new Dron(V, M, skala, this->rysownik);
                    if (!(sprawdz_kolizje(G->z_srodek(), G->promienmax())))
                      {
                        G->rysuj();
                        el_dronow.push_back(G);
                        system("clear");                    
                        cout << "Dodano drona" << endl << endl;
                      }
                    else 
                      {
                        cout << "Dodanie niemozliwe - elementy sie nakladaja" << endl << endl;
                      }
                  break;
                  }
                case 'c':
                  {
                    warunek_wyjscia = 0;
                    break;
                  }
                default:
                  {
                    system("clear");
                    cout << "Blednie wybrana opcja" << endl << endl;
                    break;
                  }
              }
          }
       } 

    void Scena:: usun_element(int id) 
     {
       if (id < (int)el_krajobrazu.size())
         {
           if (!(sprawdz_kolizje((this->el_krajobrazu[id])->z_srodek(),(this->el_krajobrazu[id])->promienmax() == 0)))
             {
               Krajobraz *tmp;
               tmp = (this->el_krajobrazu)[id];      
               tmp->zmarz();
               el_krajobrazu.erase(el_krajobrazu.begin()+id); 
             }
           else
             {
               cout << "Nie mozna usunac elementu na ktorym znajduje sie dron" << endl;
             }
          }
        else
          {
            throw std::logic_error("Błąd indeksu");
          }
     }
     
    void Scena:: usun_drona(int id) 
     {
       if (id < (int)el_dronow.size())
         {
           Dron *tmp;
           tmp = (this->el_dronow)[id];      
           tmp->zmarz();
           el_dronow.erase(el_dronow.begin()+id); 
           delete (this->el_dronow[id]);
         }
       else
         {
           throw std::logic_error("Błąd indeksu");
         } 
     }
 
    void Scena:: pokaz_elementy() 
      {
        for (int i = 0; i < (int)el_krajobrazu.size(); i++)
          {
            cout << "obiekt o indeksie: " << i << " jest w punkcie " << el_krajobrazu[i]->z_srodek() << endl;  
          }
       }
       
    void Scena:: pokaz_drony() 
      {
        for (int i = 0; i < (int)el_dronow.size(); i++)
          {
            cout << "dron o indeksie: " << i << " jest w punkcie " << el_dronow[i]->z_srodek() << endl;  
          }
       }

    bool Scena:: sprawdz_kolizje(Wektor<3> S, double R) 
      {
        for (int k = 0; k < (int)el_krajobrazu.size(); k++)
          { 
           cout << "element kraj " << k << endl;
            if (el_krajobrazu[k]->czy_nad(S, R) == 1) //dron jest nad jakims elementem
              {
                cout << "jest nad el kraj " << k << endl;
                if (el_krajobrazu[k]->czy_ladowac(S, R) == 0) //nie da sie ladowac - kolizja
                  { 
                     cout << "kolizja z el kraj " << k << endl;
                     this->c = 'n';
                     this->j = -1;
                     return 1;  
                  }
                else
                  {
                    this->j = k;
                    this->c = 'k';
                    return 0;
                  }
              }
           } 
         for (int k = 0; k < (int)el_dronow.size(); k++)
           {
             cout << "dron nr " << k << endl;
             if ((el_dronow[k]->czy_nad(S, R) == 1) && (k != this->i))  //dron jest nad jakims elementem
               {
                 cout << "jest nad dronem nr " << k << endl;
                 if (el_dronow[k]->czy_ladowac(S, R) == 0) //nie da sie ladowac - kolizja
                   {
                      cout << "kolizja z dronem nr " << k << endl;
                      this->c = 'n';
                      this->j = -1;
                      return 1;  
                   }
                 else
                   {
                     this->j = k;
                     this->c = 'd';
                     return 0;
                   }
                }
            }
          this->c = 'l';
          this->j = -1;
          this->i = -1;
          return 0;   
        }
       
      bool Scena:: sprawdz_kolizje_h(double wysokosc)
        {
          for (int i = 0; i < (int)el_krajobrazu.size(); i++)
            {
              if (el_krajobrazu[i]->h() > wysokosc) //dron chce wzniesc sie za nisko - ryzyko kolizji
                {
                  return 1; 
                }          
            }
           return 0;
         }
         
