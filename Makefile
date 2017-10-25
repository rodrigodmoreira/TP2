compile:
	g++ -std=c++11 *.cpp -lglut -lGLU -lGL -lGLEW -lSOIL -lm -lSDL2_mixer -lSDL2 -lopenal -lalut -g -w

run:
	g++ -std=c++11 *.cpp -lglut -lGLU -lGL -lGLEW -lSOIL -lm -lSDL2_mixer -lSDL2 -lopenal -lalut -g -w && ./a.out

clean:
	rm *.o a.out
