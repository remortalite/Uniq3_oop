
#include <SFML/Graphics.hpp>

#include <iostream>

#define MAXX 600
#define MAXY 600

#include "tPoint.hpp"

tPoint* getArray(int N) {
	tPoint *array = new tPoint[N];
	int randX, randY;
	for (int i = 0; i < N; ++i) {
		randX = rand() % MAXX;
		randY = rand() % MAXY;
		array[i] = tPoint(randX, randY);
	}
	return array;
}

void run() {
	sf::RenderWindow window(sf::VideoMode(MAXX,MAXY), "Lab3");
	
	int N = 100;
	tPoint *arrayPoint = getArray(N);

	int *motion = new int[N];
	for (int i = 0; i < N; ++i) {
		motion[i] = 1;
	}

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
		}

		window.clear();
		
		tPoint p;
		for (int i = 0; i < N; ++i) {
			p = arrayPoint[i];
			sf::CircleShape shape(2.f);
			shape.setFillColor(sf::Color(p.getColorR(),
									p.getColorG(), p.getColorB()));
			shape.setPosition(p.getX(), p.getY());
			window.draw(shape);
		}

		#ifdef BROWN
		for (int i = 0; i < N; ++i) {
			arrayPoint[i].moveRandom();
		}
		#else
		for (int i = 0; i < N; ++i) {
			arrayPoint[i].moveLinear();
		}
		#endif

		window.display();
	}

	delete[] arrayPoint;
}

int main() {
	tPoint dot;
	tPoint dot2 (1, 2);

	dot.print();
	dot2.print();

	run();
		
	return 0;
}
