
#include <SFML/Graphics.hpp>

#include <iostream>

#include "tFigure.hpp"

tPoint* getArrayPoint(int N) {
	tPoint *array = new tPoint[N];
	int randX, randY;
	for (int i = 0; i < N; ++i) {
		randX = rand() % MAXX;
		randY = rand() % MAXY;
		array[i] = tPoint(randX, randY);
	}
	return array;
}

tCircle* getArrayCircle(int N) {
	tCircle *array = new tCircle[N];
	int randX, randY;
	for (int i = 0; i < N; ++i) {
		randX = rand() % MAXX;
		randY = rand() % MAXY;
		array[i] = tCircle(randX, randY);
	}
	return array;
}

tEllipse* getArrayEllipse(int N) {
	tEllipse *array = new tEllipse[N];
	int randX, randY;
	int radius, radius2;
	for (int i = 0; i < N; ++i) {
		randX = rand() % (MAXX-10);
		randY = rand() % (MAXY-10);
		radius = rand() % 3 + 2;
		radius2 = rand() % 3 + 2;
		array[i] = tEllipse(randX, randY, radius, radius2);
	}
	return array;
}


void run() {
	sf::RenderWindow window(sf::VideoMode(MAXX,MAXY), "Lab3");
	
	int N = 100;
	
	//tPoint *array = getArrayPoint(N);
	//tCircle *array = getArrayCircle(N);
	tEllipse *array = getArrayEllipse(N);

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

	run();

	return 0;
}
