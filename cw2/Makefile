all:
	g++ -W -Wall -lsfml-graphics -lsfml-window -lsfml-system main.cpp Creature.cpp Plant.cpp LivingCreature.cpp Prey.cpp Hunter.cpp Game.cpp
	./a.out

.clang-format:
	wget -O $@ -c "https://csc-software-development.readthedocs.io/ru/2021/_static/.clang-format"

format: .clang-format
	find . -name "*.cpp" | xargs clang-format -i
	find . -name "*.hpp" | xargs clang-format -i
	@echo Done!

.PHONY: all clean format

