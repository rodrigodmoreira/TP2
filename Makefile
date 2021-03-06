compile:
	g++ -std=c++11 *.cpp -lglut -lGLU -lGL -lGLEW -lSOIL -lm -lopenal -lalut -g -w

run:
	g++ -std=c++11 *.cpp -lglut -lGLU -lGL -lGLEW -lSOIL -lm -lopenal -lalut -g -w && ./a.out

clean:
	rm *.o a.out
