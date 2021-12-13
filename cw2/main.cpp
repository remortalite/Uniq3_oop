
#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <ctime>

//#include "tFigure.hpp"

enum class CreatureType { Hunter, Prey, Plant };

class Creature {

private:
	int m_idxX;
	int m_idxY;

	sf::Color m_color = sf::Color::White;

	float m_probability;

	char* m_name;

protected:

	const int m_period = 6;
	int m_phase = 0;

public:
	
	virtual CreatureType getType() {
	}

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

	virtual void step() {
		stepPhase();
	};

	int getPeriod() {
		return m_period;
	}

	int getPhase() {
		return m_phase;
	}

	void stepPhase() {
		++m_phase;
		if (m_phase == m_period)
			m_phase = 0;
	}

	virtual int isDead() {
		return 0;
	}

	virtual int getSpeed() {
		return 1;
	}

	virtual char* getTypeName() {
		return "???";
	}

};

class Plant : public Creature
{

	int m_lifetime = 6;

public:

	virtual CreatureType getType() {
		return CreatureType::Plant;
	}

	virtual char* getTypeName() {
		return "Plant";
	}

	Plant(int x, int y)
		: Creature(x, y)
	{
		setColor(sf::Color::Green);
		setProb(0.6f);
	}

	int getLifetime() {
		return m_lifetime;
	}

	virtual void step()
	{
		Creature::step();
		--m_lifetime;
	}

	virtual int isDead() {
		if (m_lifetime <= 0)
			return 1;
		return 0;
	}

	virtual int getSpeed() {
		return 0;
	}

};

class LivingCreature : public Creature
{

public:

	int m_hunger = 15;
	int m_eaten = 0;
	const int m_hungerStep = -2;
	const int m_gaveBirthStep = -4;
	const int m_eatStep = 2;

	uint8_t delta = 20;

	LivingCreature(int x, int y)
		: Creature(x, y)
	{
	}

	virtual void step() {
		Creature::step();

		m_hunger += m_hungerStep;
		sf::Color color = getColor();
		if (color.a-delta >= delta)
			setColor(sf::Color(color.r, color.g, color.b, color.a-delta));
	};

	virtual int isDead() {
		if (m_hunger <= 0)
			return 1;
		return 0;
	}

	void eat() {
		m_hunger += m_eatStep;
		++m_eaten;
		
		sf::Color color = getColor();
		if (color.a+delta >= 254)
			setColor(sf::Color(color.r, color.g, color.b, color.a+delta));
	}

	void giveBirth() {
		m_hunger += m_gaveBirthStep;
	}

	int getCountEaten() {
		return m_eaten;
	}

	void makeMovement(int newX, int newY) {
		//m_hunger += m_hungerStep;

		setPosition(newX, newY);
	}

};

class Prey : public LivingCreature
{

public:

	virtual CreatureType getType() {
		return CreatureType::Prey;
	}

	virtual char* getTypeName() {
		return "Prey";
	}

	Prey(int x, int y)
		: LivingCreature(x, y)
	{
		setColor(sf::Color::Yellow);
		setProb(0.4f);
	}

	virtual int getSpeed() {
		return 1;
	}

};

class Hunter : public LivingCreature
{

public:

	virtual CreatureType getType() {
		return CreatureType::Hunter;
	}

	virtual char* getTypeName() {
		return "Hunter";
	}

	Hunter(int x, int y)
		: LivingCreature(x, y)
	{
		setColor(sf::Color::Red);
		setProb(0.1f);
	}

	virtual int getSpeed() {
		if (m_hunger <= 5)
			return 2;
		return 1;
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

	int m_sizeArrayCreatures = 10;
	int m_countCreatures = 0;

	CreatureArray* m_board;

	int m_steps = 0;

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
		return CreatureType::Plant;
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
		if (m_board[x][y] == nullptr)
			return 1;
		return 0;
	}

	int isSideIndexAvailable() {
		for (int i = 0; i < m_Nrow; ++i)
			if (m_board[i][0] == nullptr || m_board[i][m_Nrow-1] == nullptr)
				return 1;
		for (int j = 0; j < m_Nrow; ++j)
			if (m_board[0][j] == nullptr || m_board[m_Nrow-1][j] == nullptr)
				return 1;
		return 0;
	}

	int isBoardFull() {
		for (int i = 0; i < m_Nrow; ++i)
			for (int j = 0; j < m_Nrow; ++j)
				if (m_board[i][j] == nullptr)
					return 0;
		return 1;
	}

	Creature* getCreature(CreatureType type, int onSide = 0) {
		int randX, randY;
		if (m_countCreatures+1 > m_Nrow*m_Nrow || isBoardFull() == 1) {
			std::cerr << "No available cell!" << std::endl;
			return nullptr;
		}
		if (onSide == 1) {
			if (isSideIndexAvailable() == 0) {
				return nullptr;
			}
		}
		int counter = 0;
		do {
			randX = rand() % m_Nrow;
			randY = rand() % m_Nrow;
			if (onSide) {
				int onSideCoef = rand() % 2;
				int onSideCoef9 = rand() % 2;
				randX *= onSideCoef;
				randY *= !onSideCoef;
				randX += randX ? 0 : 
					onSideCoef9 ? m_Nrow-1 : 0;
				randY += randY ? 0 : 
					onSideCoef9 ? m_Nrow-1 : 0;
			}
			++counter;
		} while (isIndexAvailable(randX, randY) == 0);

		switch(type) {
			case CreatureType::Hunter	: return new Hunter(randX, randY);
			case CreatureType::Prey		: return new Prey(randX, randY);
			case CreatureType::Plant	: return new Plant(randX, randY);
			default: std::cerr << "Errrr get! That not supposed to happen!" << std::endl;
				break;
		}
		return nullptr;
	}

	Creature* getRandomCreature() {
		switch(chooseRandomCreatureType()) {
			case CreatureType::Hunter: return getCreature(CreatureType::Hunter);
			case CreatureType::Prey: return getCreature(CreatureType::Prey);
			case CreatureType::Plant: return getCreature(CreatureType::Plant); 
			default: std::cerr << "Errrr! That not supposed to happen!" << std::endl;
		}
		return nullptr;
	}

	void initializeArray() {
		fillProbArray();
		for (int i = 0; i < m_sizeArrayCreatures; ++i) {
			Creature* creature = getRandomCreature();

			if (creature == nullptr) break;

			m_board[creature->getX()][creature->getY()] = creature;
			++m_countCreatures;
		}
	}

	void updateEnvironment() {
	

				if (m_steps % 5 == 0)
					for (int i = 0; i < 15; ++i) {
						Creature* creature = getCreature(CreatureType::Plant);
						if (creature == nullptr) break;
						m_board[creature->getX()][creature->getY()] = creature;
						++m_countCreatures;
					}

				if (countHunters() < 5) {
					for (int i = 0; i < 5; ++i) {
						Creature* creature = getCreature(CreatureType::Hunter, 1);
						if (creature == nullptr) break;
						else m_board[creature->getX()][creature->getY()] = creature;
						++m_countCreatures;
					}
				}

			
				if (countPreys() < 3) {
					for (int i = 0; i < 2; ++i) {
						Creature* creature = getCreature(CreatureType::Prey, 1);
						if (creature == nullptr) break;
						else m_board[creature->getX()][creature->getY()] = creature;
						++m_countCreatures;
					}
	
				}

	}

	void lifeStep() {

		++m_steps;
		
		int dx, dy;
		for (int i = 0; i < m_Nrow; ++i) {
			for (int j = 0; j < m_Nrow; ++j) {
				Creature* creature = m_board[i][j];
				if (!creature) continue;
				creature->step();
				if (creature->isDead()) {
					m_board[i][j] = nullptr;
					--m_countCreatures;
					continue;
				}

				int speed = creature->getSpeed();
				if (speed == 1) {
					dx = rand() % 3 - 1;
					dy = rand() % 3 - 1;
				} else {
					dx = rand() % 5 - 2;
					dy = rand() % 5 - 2;
				}

				if (i+dx < 0 || i+dx >= m_Nrow) dx = 0;
				if (j+dy < 0 || j+dy >= m_Nrow) dy = 0;
				Creature* nextCell = m_board[i+dx][j+dy];
				int isChild;
				switch (creature->getType()) {
					case CreatureType::Plant:
						break;
					case CreatureType::Prey:
						isChild = rand() % 100 < 25 ? 1 : 0;
						if (nextCell == nullptr) {
							m_board[i+dx][j+dy] = m_board[i][j];
							
							if (isChild) {
								Creature* child = getCreature(CreatureType::Prey);
								if (child) {
									m_board[i][j] = child;
									++m_countCreatures;
								} else
									m_board[i][j] = nullptr;
							} else
								m_board[i][j] = nullptr;
						} else {
							if (nextCell && nextCell->getType() == CreatureType::Plant) {
								Prey* creature = (Prey*)m_board[i][j];
								creature->makeMovement(i+dx, j+dy);
								creature->eat();
								--m_countCreatures;
								m_board[i+dx][j+dy] = m_board[i][j];
								if (isChild) {
									Creature* child = getCreature(CreatureType::Prey);
									if (child) {
										child->setPosition(i,j);
										m_board[i][j] = child;
										++m_countCreatures;
										creature->giveBirth();
									} else
										m_board[i][j] = nullptr;
								} else {
									m_board[i][j] = nullptr;
								}
							}
						}
						break;
					case CreatureType::Hunter:
						if (nextCell == nullptr) {
							m_board[i+dx][j+dy] = m_board[i][j];
							m_board[i][j] = nullptr;
						} else {
							if (nextCell && nextCell->getType() == CreatureType::Prey) {
								Hunter* creature = (Hunter*)m_board[i][j];
								creature->eat();
								if (creature->getCountEaten() == 2)
									isChild = rand() % 100 < 25 ? 1 : 0;
								m_board[i+dx][j+dy] = nullptr;
								--m_countCreatures;
								m_board[i+dx][j+dy] = m_board[i][j];
								creature->makeMovement(i+dx, j+dy);
								if (isChild) {
									Creature* child = getCreature(CreatureType::Hunter);
									if (child != nullptr) {
										child->setPosition(i,j);
										m_board[i][j] = child;
										++m_countCreatures;
										creature->giveBirth();
									} else {
										m_board[i][j] = nullptr;
									}
								} else {
									m_board[i][j] = nullptr;
								}
							}
						}
						break;

					default: break;
					
				}
				
			}
		}

		// update in-class positions
		for (int i = 0; i < m_Nrow; ++i)
			for (int j = 0; j < m_Nrow; ++j)
				if (m_board[i][j] != nullptr)
					m_board[i][j]->setPosition(i,j);

		updateEnvironment();
	}

	int countHunters() {
		int count = 0;
		for (int i = 0; i < m_Nrow; ++i)
			for (int j = 0; j < m_Nrow; ++j)
				if (m_board[i][j] && m_board[i][j]->getType() == CreatureType::Hunter)
					++count;
		return count;
	}

	int countPreys() {
		int count = 0;
		for (int i = 0; i < m_Nrow; ++i)
			for (int j = 0; j < m_Nrow; ++j)
				if (m_board[i][j] && m_board[i][j]->getType() == CreatureType::Prey)
					++count;
		return count;
	}

	void run() {
		while(m_window.isOpen()) {
			sf::Event event;
			while(m_window.pollEvent(event)) {
				if (event.type == sf::Event::Closed || 
					sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
						m_window.close();
				else if (event.type == sf::Event::KeyPressed &&
						sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					lifeStep();
				}
			}

					lifeStep();
			// update inside-class coordinates
			for (int i = 0; i < m_Nrow; ++i)
				for (int j = 0; j < m_Nrow; ++j)
					if (m_board[i][j] != nullptr)
						m_board[i][j]->setPosition(i,j);

			m_window.clear(sf::Color::Black);

			for (int i = 0; i < m_Nrow; ++i) {
				for (int j = 0; j < m_Nrow; ++j) {
					Creature* creature = m_board[i][j];
					if (creature == nullptr) continue;
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
