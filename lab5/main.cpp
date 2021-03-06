
#include <SFML/Graphics.hpp>

#include <iostream>

#include "tFigure.hpp"

int getrandcoord() {
	return rand() % (MAXX-30);
}

tPoint* getArrayPoint(int N) {
	tPoint *array = new tPoint[N];
	int randX, randY;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		array[i] = tPoint(randX, randY);
	}
	return array;
}

tCircle* getArrayCircle(int N) {
	tCircle *array = new tCircle[N];
	int randX, randY;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		array[i] = tCircle(randX, randY, rand() % 18);
	}
	return array;
}

tEllipse* getArrayEllipse(int N) {
	tEllipse *array = new tEllipse[N];
	int randX, randY;
	int radius, radius2;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		radius = rand() % 4 * 3 + 5;
		radius2 = rand() % 5 * 3 + 5;
		array[i] = tEllipse(randX, randY, radius, radius2);
	}
	return array;
}

tTriangle* getArrayTriangle(int N) {
	tTriangle *array = new tTriangle[N];
	int randX, randY;
	int a;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 15 * 2 + 4;
		array[i] = tTriangle(randX, randY, a);
	}
	return array;
}

tRectangle* getArrayRectangle(int N) {
	tRectangle *array = new tRectangle[N];
	int randX, randY;
	int a, b;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 5 * 4 + 4;
		b = rand() % 5 * 4 + 4;
		array[i] = tRectangle(randX, randY, a, b);
	}
	return array;
}

tSquare* getArraySquare(int N) {
	tSquare *array = new tSquare[N];
	int randX, randY;
	int a;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 5 * 2 + 4;
		array[i] = tSquare(randX, randY, a);
	}
	return array;
}

tRombus* getArrayRombus(int N) {
	tRombus *array = new tRombus[N];
	int randX, randY;
	int a;
	int b;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 7 * 4 + 4;
		b = rand() % 7 * 4 + 4;
		array[i] = tRombus(randX, randY, a, b);
	}
	return array;
}

tLine* getArrayLine(int N) {
	tLine *array = new tLine[N];
	int randX, randY;
	int a;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 5 * 7 + 4;
		array[i] = tLine(randX, randY, a);
	}
	return array;
}

tFigure** getArray(int N) {
	tFigure **array = new tFigure*[N];
	int randX, randY, a, b;

	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 8 * 4 + 4;
		b = rand() % 8 * 4 + 4;
		switch(rand()%8) {
			case 0:
				array[i] = new tPoint(randX, randY);
				break;
			case 1:
				array[i] = new tCircle(randX, randY, a);
				break;
			case 2:
				array[i] = new tEllipse(randX, randY, a, b);
				break;
			case 3:
				array[i] = new tTriangle(randX, randY, a);
				break;
			case 4:
				array[i] = new tRectangle(randX, randY, a, b);
				break;
			case 5:
				array[i] = new tSquare(randX, randY, a);
				break;
			case 6:
				array[i] = new tRombus(randX, randY, a, b);
				break;
			case 7:
				array[i] = new tLine(randX, randY, a);
				break;
		}
	}

	return array;
}

void run() {
	sf::RenderWindow window(sf::VideoMode(MAXX,MAXY), "Lab5");

	srand(time(0));
	
	int N = 100;
	
	tFigure **array = getArray(N);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
		}

		window.clear();
		
		for (int i = 0; i < N; ++i) {
			window.draw(array[i]->getShape());
		}

		#ifdef BROWN
		for (int i = 0; i < N; ++i) {
			array[i]->moveRandom();
		}
		#else
		for (int i = 0; i < N; ++i) {
			array[i]->moveLinear();
		}
		#endif

		window.display();
	}

	delete[] array;
}

int main() {

	run();

	return 0;
}
