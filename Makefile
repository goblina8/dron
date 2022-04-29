CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17

__start__: drony
	./drony

drony: obj obj/main.o obj/Prostopadloscian.o obj/Macierz.o obj/Wektor.o obj/gnuplot.o obj/Powierzchnia.o obj/Graniastoslup.o obj/Scena.o obj/Dron.o obj/Wzgorze.o obj/Plaskowyz.o obj/Plaskowyz_prost.o
	g++ -Wall -pedantic -std=c++0x -o drony obj/main.o obj/Wektor.o\
                        obj/Macierz.o obj/Prostopadloscian.o obj/Powierzchnia.o obj/Graniastoslup.o obj/Dron.o  obj/Scena.o obj/Wzgorze.o obj/Plaskowyz.o obj/Plaskowyz_prost.o obj/gnuplot.o -lpthread
	

obj:
	mkdir obj

obj/gnuplot.o: src/gnuplot.cpp inc/gnuplot.hh 
	g++ -c ${CXXFLAGS} -o obj/gnuplot.o src/gnuplot.cpp  
	
obj/main.o: src/main.cpp inc/Prostopadloscian.hh inc/Macierz.hh inc/Wektor.hh inc/gnuplot.hh inc/Graniastoslup.hh inc/Prostopadloscian.hh inc/Uklad.hh inc/Powierzchnia.hh inc/Dron.hh inc/Krajobraz.hh inc/Plaskowyz.hh inc/Plaskowyz_prost.hh inc/Wzgorze.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

obj/Prostopadloscian.o: src/Prostopadloscian.cpp inc/Prostopadloscian.hh inc/Uklad.hh inc/Rysowanie.hh
	g++ -c ${CXXFLAGS} -o obj/Prostopadloscian.o src/Prostopadloscian.cpp
	
obj/Powierzchnia.o: src/Powierzchnia.cpp inc/Powierzchnia.hh inc/interface.hh inc/Rysowanie.hh
	g++ -c ${CXXFLAGS} -o obj/Powierzchnia.o src/Powierzchnia.cpp
	
obj/Graniastoslup.o: src/Graniastoslup.cpp inc/Graniastoslup.hh inc/Uklad.hh inc/Rysowanie.hh
	g++ -c ${CXXFLAGS} -o obj/Graniastoslup.o src/Graniastoslup.cpp
	
obj/Dron.o: src/Dron.cpp inc/Dron.hh inc/Uklad.hh inc/interface.hh inc/Rysowanie.hh
	g++ -c ${CXXFLAGS} -o obj/Dron.o src/Dron.cpp
		
obj/Macierz.o: src/Macierz.cpp inc/Macierz.hh inc/Wektor.hh inc/interface.hh
	g++ -c ${CXXFLAGS} -o obj/Macierz.o src/Macierz.cpp

obj/Wektor.o: src/Wektor.cpp inc/Wektor.hh inc/interface.hh
	g++ -c ${CXXFLAGS} -o obj/Wektor.o src/Wektor.cpp
	
obj/Scena.o: src/Scena.cpp inc/Scena.hh inc/interface.hh
	g++ -c ${CXXFLAGS} -o obj/Scena.o src/Scena.cpp
	
obj/Wzgorze.o: src/Wzgorze.cpp inc/Wzgorze.hh inc/interface.hh inc/Krajobraz.hh
	g++ -c ${CXXFLAGS} -o obj/Wzgorze.o src/Wzgorze.cpp
	
obj/Plaskowyz.o: src/Plaskowyz.cpp inc/Plaskowyz.hh inc/interface.hh inc/Krajobraz.hh
	g++ -c ${CXXFLAGS} -o obj/Plaskowyz.o src/Plaskowyz.cpp
	
obj/Plaskowyz_prost.o: src/Plaskowyz_prost.cpp inc/Plaskowyz_prost.hh inc/interface.hh inc/Krajobraz.hh
	g++ -c ${CXXFLAGS} -o obj/Plaskowyz_prost.o src/Plaskowyz_prost.cpp
		
gnuplot.hh: inc/interface.hh
	touch inc/gnuplot.hh

clean:
	rm -f obj/*.o drony
