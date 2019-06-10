// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include <iostream>
#include <string>
#include "TuringMachine.h"

/* Public Member Functions */

TuringMachine::TuringMachine(std::string input) : tape() {
	states.push_back(std::shared_ptr<State>::shared_ptr(new State(0)));
	std::cout << "From\tTo\tRead\tWrite\tMove" << std::endl;
	machineDecode(input);
	tapeHead = tape.begin();
	tapeHead++; // Move passed # in pos 0
	std::cout << "Tape Head: " << *tapeHead << std::endl;
	printTape();
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

void TuringMachine::move(bool dir) {
	if (dir) tapeHead--;
	else tapeHead++;
}

void TuringMachine::printTape() {
	std::cout << "The Tape: " << getTapeAsString() << std::endl;
}

/* Getter Functions */

char TuringMachine::getCurrentChar() { return *tapeHead; }

std::string TuringMachine::getTapeAsString() {
	std::string output(tape.begin(), tape.end());

	return output;
}

/* Setter Functions */

void TuringMachine::setTape(std::string input) {
	tape.clear();
	if (input[0] != '#') tape.push_back('#');
	for (std::string::iterator i = input.begin(); i != input.end(); ++i) tape.push_back(*i);
}

/* Private Member Functions */

void TuringMachine::machineDecode(std::string machine) {
	int from, to, lineStart, sFrom, sTo, i = 0;
	char read, write, curr;
	bool dir;
	std::string localMachine = machine;

	while (localMachine[i] != '#') {
		// Set default vars for loop
		lineStart = i;
		sFrom = sTo = -1;
		
		// Count first number of a's (First State number)
		curr = localMachine[i];
		while (curr != 'b') curr = localMachine[++i];
		from = i - lineStart;

		// Count second number of a's (Second State number)
		curr = localMachine[++i];
		while (curr != 'b') curr = localMachine[++i];
		to = i - lineStart - from - 1; // Extra 1 because of the b between

		// Get the read/write characters
		read = convertChar(machine.substr(++i, 2));
		i += 2;
		write = convertChar(machine.substr(i, 2));
		i += 2;

		dir = machine[i++] == 'a'; // Get direction

		// Create states if needed
		for (const auto& state : states) {
			if (state->getNum() == from) sFrom = from;
			if (state->getNum() == to) sTo = to;
		}

		if (sFrom == -1) {
			states.push_back(std::shared_ptr<State>::shared_ptr(new State(from)));
			std::cout << "Created state " << from << std::endl;
		}

		if (sTo == -1) {
			states.push_back(std::shared_ptr<State>::shared_ptr(new State(to)));
			std::cout << "Created state " << to << std::endl;
		}

		addEdge(std::shared_ptr<State>::shared_ptr(states.at(from)), std::shared_ptr<State>::shared_ptr(states.at(to)), std::shared_ptr<Edge>(new Edge(read, write, dir)));

		std::cout << from << "\t" << to << "\t" << read << "\t" << write << "\t" << (dir ? "L" : "R") << std::endl;
	}

	setTape(machine.substr(i, std::size(localMachine) - (unsigned)i));
}

char TuringMachine::convertChar(std::string code) {
	if (code == "aa") return 'a';
	else if (code == "ab") return 'b';
	else if (code == "ba") return '^';
	else if (code == "bb") return '#';
	else return '!';
}