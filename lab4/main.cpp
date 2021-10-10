
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
		array[i] = tCircle(randX, randY);
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
		radius = rand() % 2 * 3 + 5;
		radius2 = rand() % 3 * 3 + 5;
		array[i] = tEllipse(randX, randY, radius, radius2);
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
		a = rand() % 5 * 2 + 4;
		b = rand() % 5 * 2 + 4;
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

tTriangle* getArrayTriangle(int N) {
	tTriangle *array = new tTriangle[N];
	int randX, randY;
	int a;
	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 5 * 2 + 4;
		array[i] = tTriangle(randX, randY, a);
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

void run() {
	sf::RenderWindow window(sf::VideoMode(MAXX,MAXY), "Lab3");
	
	int N = 100;
	
	//tPoint *array = getArrayPoint(N);
	//tCircle *array = getArrayCircle(N);
	//tEllipse *array = getArrayEllipse(N);
	//tRectangle *array = getArrayRectangle(N);
	//tSquare *array = getArraySquare(N);
	//tTriangle *array = getArrayTriangle(N);
	tRombus *array = getArrayRombus(N);
	//tLine *array = getArrayLine(N);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
		}

		window.clear();
		
		for (int i = 0; i < N; ++i) {
			window.draw(array[i].getShape());
		}

		#ifdef BROWN
		for (int i = 0; i < N; ++i) {
			array[i].moveRandom();
		}
		#else
		for (int i = 0; i < N; ++i) {
			array[i].moveLinear();
		}
		#endif

		window.display();
	}

	delete[] array;
}

int main() {

	tEllipse fig (1, 2, 3, 6);
	fig.print();
	std::cout << "Radius: " << fig.getRadius() << std::endl;
	std::cout << "Radius: " << fig.getRadius2() << std::endl;

	run();

	return 0;
}
