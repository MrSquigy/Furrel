#include <iostream>
#include <string>
#include "TuringMachine.h"

/* Public Member Functions */

TuringMachine::TuringMachine(std::string input) : tape() {
	states.push_back(std::shared_ptr<State>::shared_ptr(new State(0)));
	std::cout << "From\tTo\tRead\tWrite\tMove" << std::endl;
	decodeMachine(input);
	tapeHead = tape.begin();
	tapeHead++; // Move passed # in pos 0
}

TuringMachine::TuringMachine(TuringMachine& tm) : tapeHead(tm.tapeHead), tape() {
	states.push_back(std::shared_ptr<State>::shared_ptr(new State(0)));
	setTape(tm.getTapeAsString());
}

TuringMachine& TuringMachine::operator=(TuringMachine& tm) {
	states.push_back(std::shared_ptr<State>::shared_ptr(new State(0)));
	tapeHead = tm.tapeHead;
	setTape(tm.getTapeAsString());

	return *this;
}

void TuringMachine::addEdge(std::shared_ptr<State> firstState, std::shared_ptr<State> secondState, std::shared_ptr<Edge> edge) {
	// Check if a link exists
	for (auto& link : links) {
		if (link->checkLink(*firstState, *secondState)) {
			std::cout << "here" << std::endl;
			link->addEdge(edge);
			//std::cout << "Created edge (" << edge->getRead() << ", " << edge->getWrite() << ", " << edge->getDirection() << ") on link " << firstState->getNum() << " to " << secondState->getNum() << std::endl;
			return;
		}
	}
}

// Move the tape head left or right
void TuringMachine::move(bool dir) {
	if (dir) tapeHead--;
	else tapeHead++;
}

void TuringMachine::printTape() {
	std::cout << getTapeAsString() << std::endl;
}

/* Getter Functions */

char TuringMachine::getCurrentChar() { return *tapeHead; }

std::string TuringMachine::getTapeAsString() {
	std::string output = "";

	for (std::vector<char>::iterator letter = tape.begin(); letter != tape.end(); ++letter) output = output + *letter;

	return output;
}

/* Setter Functions */

void TuringMachine::setTape(std::string input) {
	tape.clear();
	tape.push_back('#');
	for (std::string::iterator i = input.begin(); i != input.end(); ++i) tape.push_back(*i);
}

/* Private Member Functions */
// Recursive function to decode the machine from CWL
void TuringMachine::decodeMachine(std::string &machine) {
	int from, to, i = -1, sFrom = -1, sTo = -1;
	char read, write, curr;
	bool dir;
	
	std::cout << "Machine Line: " << machine << std::endl;
	std::cout << "Length: " << machine.length() << std::endl;

	do {
		i++;
		curr = machine[i];
	} while (curr != 'b');
	from = i;

	do {
		i++;
		curr = machine[i];
	} while (curr != 'b');
	to = i > from ? i - from - 1 : from - i - 1;

	curr = machine[i];
	while (curr != 'b') {
		i++;
		to++;
		curr = machine[i];
	}
	i++;

	read = convertChar(machine.substr(i, 2));
	i += 2;
	write = convertChar(machine.substr(i, 2));
	i += 2;

	dir = machine[i++] == 'a';

	machine = machine.substr(i, (machine.length() - i)); // Prepare for next edge decoding

	// Create states if needed
	for (const auto& state : states) {
		if (state->getNum() == from) sFrom = from;
		if (state->getNum() == to) sTo = to;
	}
	
	if (sFrom == -1) {
		states.push_back(std::shared_ptr<State>::shared_ptr(new State(from, machine.length() == 1)));
		std::cout << "Created state " << from << std::endl;
	}
	if (sTo == -1) {
		states.push_back(std::shared_ptr<State>::shared_ptr(new State(to, machine.length() == 1)));
		std::cout << "Created state " << to << std::endl;
	}
	
	std::cout << from << "\t" << to << "\t" << read << "\t" << write << "\t" << dir << std::endl;

	std::shared_ptr<State> fromPtr = std::shared_ptr<State>::shared_ptr(states.at(from).get());
	std::shared_ptr<State> toPtr = std::shared_ptr<State>::shared_ptr(states.at(to).get());
	std::shared_ptr<Edge> edgePtr = std::shared_ptr<Edge>(new Edge(read, write, dir));

	addEdge(fromPtr, toPtr, edgePtr);
	
	if (machine.length() > 1) decodeMachine(machine);
}

// Function to convert the 2-char code into a single char
char TuringMachine::convertChar(std::string code) {
	if (code == "aa") return 'a';
	else if (code == "ab") return 'b';
	else if (code == "ba") return '^';
	else if (code == "bb") return '#';
	else return '!';
}