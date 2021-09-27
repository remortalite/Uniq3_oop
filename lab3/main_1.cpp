#include <SFML/Graphics.hpp>

#include <iostream>

#define MAXX 600
#define MAXY 600

class tPoint
{
public:
	int m_x;
	int m_y;

	int m_colorR;
	int m_colorG;
	int m_colorB;

	tPoint() 
		: m_x(0), m_y(0)
	{
		setRandColor();
	}

	tPoint (int x, int y) : 
			m_x(x), m_y(y)
	{
		setRandColor();
	}

	void print() {
		printf("Point (%d, %d) Color: (%d,%d,%d)\n", m_x, m_y,
						m_colorR, m_colorG, m_colorB);
	}

	void move(int dx, int dy) {
		m_x += dx;
		m_y += dy;
	}

	void moveLinear() {
		if (m_x-1 < 0 || m_x+1 > MAXY)
			motion *= -1;
		move(motion, 0);
	}

	void moveRandom() {
		int dx = rand() % 2 * 2 - 1;
		int dy = rand() % 2 * 2 - 1;
		int newX = m_x + dx;
		int newY = m_y + dy;
		if (newX < 0 || newX > MAXX)
			dx *= -1;
		if (newY < 0 || newY > MAXY)
			dy *= -1;
		move(dx, dy);
	}

private:
	int motion = 1;

	void setRandColor() {
		m_colorR = rand() % 255;
		m_colorG = rand() % 255;
		m_colorB = rand() % 255;
	}
};

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
	sf::RenderWindow window(sf::VideoMode(600,600), "Lab3");
	
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
			shape.setFillColor(sf::Color(p.m_colorR, p.m_colorG, p.m_colorB));
			shape.setPosition(p.m_x, p.m_y);
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
}

int main() {
	tPoint dot;
	tPoint dot2 (1, 2);

	dot.print();
	dot2.print();

	run();
		
	return 0;
}
