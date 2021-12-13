
#include <SFML/Graphics.hpp>

#include <iostream>

#include "tFigure.hpp"


int getrandcoord() {
	return rand() % (MAXX-30);
}

class Creature {

private:
	int m_idxX;
	int m_idxY;

	sf::Color m_color;

	float m_probability;

public:
	Creature(int x, int y) 
		: m_idxX(x), m_idxY(y) 
	{
	}

	void setX(int newX) {
		m_idxX = newX;
	}

	int getX() {
		return m_idxX;	
	}
	
	void setY(int newY) {
		m_idxY = newY;
	}

	int getY() {
		return m_idxY;	
	}

	void setPosition(int newX, int newY) {
		m_idxX = newX;
		m_idxY = newY;
	}

	void setColor(sf::Color color) {
		m_color = color;
	}

	virtual sf::Color getColor() {
		return m_color;
	}

	virtual float getProb() {
		return m_probability;
	}

	void setProb(float prob) {
		m_probability = prob;
	}

};

class Plant : public Creature
{

public:
	Plant(int x, int y)
		: Creature(x, y)
	{
		setColor(sf::Color::Green);
		setProb(0.6f);
	}

};

class Prey : public Creature
{
	
public:
	Prey(int x, int y)
		: Creature(x, y)
	{
		setColor(sf::Color::Yellow);
		setProb(0.4f);
	}

};

class Hunter : public Creature
{
	
public:
	Hunter(int x, int y)
		: Creature(x, y)
	{
		setColor(sf::Color::Red);
		setProb(0.1f);
	}

};



class Game
{

	int m_Xsize;
	int m_Ysize;

	const char* m_gameTitle = "Game of life";

	sf::RenderWindow m_window;

	int m_Nrow = 10; // square count per column or row

	int m_borderSize = 2;

	int m_squareSize;

	typedef Creature** CreatureArray;
	enum class CreatureType { Hunter, Prey, Plant };

	int m_sizeArrayCreatures = 10;
	int m_countCreatures = 0;

	CreatureArray m_creatures = new Creature*[m_sizeArrayCreatures];

	CreatureArray* m_board;

	// probabilities
	
	int m_probSizeArray;
	int* m_probArray;

	typedef enum CreatureInt {
		CreatureInt_Hunter = 1,
		CreatureInt_Prey = 2,
		CreatureInt_Plant = 3
	} CreatureInt;

	void fillProbArray() {
		int coef = 100;

		int hunterProb = Hunter(0,0).getProb() * coef;
		int preyProb = Prey(0,0).getProb() * coef;
		int plantProb = Plant(0,0).getProb() * coef;
		m_probSizeArray = hunterProb + preyProb + plantProb;

		m_probArray = new int[m_probSizeArray];
		for (int i = 0; i < hunterProb; ++i)
			m_probArray[i] = CreatureInt_Hunter;
		for (int i = 0; i < preyProb; ++i)
			m_probArray[hunterProb+i] = CreatureInt_Prey;
		for (int i = 0; i < plantProb; ++i)
			m_probArray[m_probSizeArray-1-i] = CreatureInt_Plant;
	}

	CreatureType chooseRandomCreatureType() {
		int randIdx = rand() % m_probSizeArray;
		switch(m_probArray[randIdx]) {
			case CreatureInt_Hunter: return CreatureType::Hunter;
			case CreatureInt_Prey: return CreatureType::Prey;
			case CreatureInt_Plant:  return CreatureType::Plant;
			default: std::cerr << "Errrr choose (" << m_probArray[randIdx] << ") ! That not supposed to happen!" << std::endl;
		}
	}
	
	
public:

	Game(int Xsize, int Ysize) 
		: m_Xsize(Xsize), m_Ysize(Ysize), 
		m_window(sf::VideoMode(m_Xsize, m_Ysize), m_gameTitle)
	{
		m_squareSize = (m_Xsize < m_Ysize ? m_Xsize : m_Ysize) / m_Nrow - m_borderSize;
		m_board = new Creature**[m_Nrow];
		for (int i = 0; i < m_Nrow; ++i) {
			m_board[i] = new Creature*[m_Nrow];
			for (int j = 0; j < m_Nrow; ++j)
				m_board[i][j] = nullptr;
		}
		initializeArray();
	}

	Game(int Xsize) 
		: Game(Xsize, Xsize)
	{
	}

	Game() 
		: Game(600, 600)
	{
	}

	sf::Vector2f getCoord(int idxX, int idxY) {
		float coordX = idxX * (m_squareSize + m_borderSize);
		float coordY = idxY * (m_squareSize + m_borderSize);
		return sf::Vector2f(coordX, coordY);
	}

	sf::RectangleShape createShape(Creature* creature) {
		sf::RectangleShape shape = 
			sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));
		shape.setPosition(getCoord(creature->getX(), creature->getY()));
		shape.setFillColor(creature->getColor());
		return shape;
	}

	int isIndexAvailable(int x, int y) {
		for (int i = 0; i < m_countCreatures; ++i) {
			if (m_creatures[i]->getX() == x &&
					m_creatures[i]->getY() == y )
				return 0;
		}
		return 1;
	}


	Creature* getCreature(CreatureType type) {
		int randX, randY;
		if (m_countCreatures+1 > m_Nrow*m_Nrow) {
			std::cerr << "No available cell!" << std::endl;
			return nullptr;
		}
		do { 
			randX = rand() % m_Nrow;
			randY = rand() % m_Nrow;
		} while (isIndexAvailable(randX, randY) == 0);

		switch(type) {
			case CreatureType::Hunter	: return new Hunter(randX, randY);
			case CreatureType::Prey		: return new Prey(randX, randY);
			case CreatureType::Plant	: return new Plant(randX, randY);
			default: std::cerr << "Errrr get! That not supposed to happen!" << std::endl;
				break;
		}
	}

	Creature* getRandomCreature() {
		switch(chooseRandomCreatureType()) {
			case CreatureType::Hunter: return getCreature(CreatureType::Hunter);
			case CreatureType::Prey: return getCreature(CreatureType::Prey);
			case CreatureType::Plant: return getCreature(CreatureType::Plant); 
			default: std::cerr << "Errrr! That not supposed to happen!" << std::endl;
		}
	}

	CreatureArray initializeArray() {
		fillProbArray();
		for (int i = 0; i < m_sizeArrayCreatures; ++i) {
			Creature* creature = getRandomCreature();

			if (creature == nullptr) break;

			m_creatures[i] = creature;
			m_board[creature->getX()][creature->getY()] = creature;
			++m_countCreatures;
		}
	}

	void lifeStep() {
		
	}

	void run() {
		while(m_window.isOpen()) {
			sf::Event event;
			while(m_window.pollEvent(event)) {
				if (event.type == sf::Event::Closed || 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						m_window.close();
			}

			m_window.clear(sf::Color::Black);

			//for (int i = 0; i < m_countCreatures; ++i) {
			//	m_window.draw(createShape(m_creatures[i]));
			//}
			
			for (int i = 0; i < m_Nrow; ++i) {
				for (int j = 0; j < m_Nrow; ++j) {
					Creature* creature = m_board[i][j];
					if (!creature) continue;
					m_window.draw(createShape(m_board[i][j]));	
				}
			}

			m_window.display();

		}
	}

};

int main() {
	srand(time(0));

	Game game;
	game.run();
}
/*
sf::RectangleShape** getArray(int Nrow, int Ncol) {

	int randX, randY, a, b;
	int N = Nrow*Ncol;

	sf::RectangleShape **array = new sf::RectangleShape*[N];

		float size = MAXX/10-BORDER;
		window.draw(sf::RectangleShape(sf::Vector2f(size, size)));

		sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(size+BORDER, 0));

	for (int i = 0; i < N; ++i) {
		randX = getrandcoord();
		randY = getrandcoord();
		a = rand() % 8 * 4 + 4;
		b = rand() % 8 * 4 + 4;
		array[i] = new sf::RectangleShape();
		array[i]->setPosition(randX, randY);
		array[i]->setScale(randX, randY);
		array[i]->setFillColor(sf::Color::Red);
	}

	return array;
}

void run() {
	sf::RenderWindow window(sf::VideoMode(MAXX,MAXY), "Lab5");

	srand(time(0));
	
	int Nrow = 10;
	int Ncol = 10;

	int N = Nrow*Ncol;
	
	sf::RectangleShape **array = getArray(Nrow, Ncol);

	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
					window.close();
		}

		window.clear(sf::Color::Black);
		
		for (int i = 0; i < N; ++i) {
			window.draw(*array[i]);
		}

		float size = MAXX/10-BORDER;
		window.draw(sf::RectangleShape(sf::Vector2f(size, size)));

		sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(size+BORDER, 0));
		window.draw(shape);

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

int main2() {

	run();

	return 0;
}
*/
