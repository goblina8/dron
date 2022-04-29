#include <iostream>
#include <vector>
#include "interface.hh"
#include "Powierzchnia.hh"

using namespace std;

  void Powierzchnia::rysuj()
    {
      this->rysownik->erase_shape(this->i);
      drawNS::Point3D P1(-250,-250,this->h), P2(-250,250,this->h), P3(250,-250,this->h), P4(250,250,this->h);
      std::vector<drawNS::Point3D> dane;
      dane.push_back(P1);
      dane.push_back(P2);
      dane.push_back(P3);
      dane.push_back(P4);
      dane.push_back(P1);
      dane.push_back(P3);
      dane.push_back(P4);
      dane.push_back(P2);
      this->i = (this->rysownik)->draw_polygonal_chain(dane, "grey");
    }
   

