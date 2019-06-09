#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <vector>
#include "Link.h"

class TuringMachine {
public:
	TuringMachine(std::string input = "");
	TuringMachine(TuringMachine &tm);
	TuringMachine& operator=(TuringMachine &tm);
	void addEdge(std::shared_ptr<State> firstState, std::shared_ptr<State> secondState, std::shared_ptr<Edge> edge);
	void move(bool dir);
	void printTape();
	char getCurrentChar();
	std::string getTapeAsString();
	void setTape(std::string input);
private:
	void decodeMachine(std::string &machine);
	char convertChar(std::string code);
	std::vector<std::shared_ptr<State>> states;
	std::vector<std::shared_ptr<Link>> links;
	std::vector<char> tape;
	std::vector<char>::iterator tapeHead;
};

#endif // TURING_MACHINE_H