all: clean q3 bmp Canvas

bmp: bmp.h	
	g++ -std=c++1y -o bmp bmp.h 

Canvas: bmp.h Canvas.cpp Canvas.h
	g++ -std=c++11 Main.cpp `wx-config --libs` `wx-config --cxxflags` -o Canvas	

q3: base.h Main.cpp 
	g++ -std=c++11 Main.cpp `wx-config --libs` `wx-config --cxxflags` -o q3	
clean:
	rm -f q2 q3 bmp Canvas *.o
