
#include <SFML/Graphics.hpp>

#include <iostream>

#include "tFigure.hpp"

int getrandcoord() {
	return rand() % (MAXX-30);
}

tFigure** getArray(int N) {
	tFigure **array = new tFigure*[N];
	int randX, randY, a, b;

	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 8 * 4 + 4;
		b = rand() % 8 * 4 + 4;
		array[i] = new tCircle(randX, randY, a);
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
