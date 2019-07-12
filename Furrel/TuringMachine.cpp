// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include <iostream>
#include <string>
#include "TuringMachine.h"

/* Public Member Functions */

std::string getLine();

TuringMachine::TuringMachine(std::string input) : tape() {
	states.push_back(std::shared_ptr<State>::shared_ptr(new State(0)));
	std::string log = machineDecode(input);
	
	// Print stuff for user
	std::cout << std::endl << "Machine Diagram" << std::endl << getLine() << "From\tTo\tRead\tWrite\tMove" << std::endl;
	std::cout << log << std::endl;

	tapeHead = tape.begin();
	tapeHead++; // Move passed # in pos 0
	printTape();
	printTapeHead();
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

template <class T>
void printVector(std::vector<T> const &v) {
	for (unsigned int i = 0; i < v.size(); i++) std::cout << v.at(i) << " ";
}

std::string TuringMachine::run() {
	std::vector<int> availableLinks, operations;
	int currentState = 0; // Index for State
	bool moved;

	while (!states.at(currentState)->isHaltState()) { // Run through Edges until a halt State is reached
		moved = false;
		availableLinks = getLinks(*states.at(currentState));
		for (std::vector<int>::iterator i = availableLinks.begin(); i != availableLinks.end(); ++i) {
			if (links.at(*i)->getTraversable(*tapeHead)) {
				// Can get to the next State here
				operations = links.at(*i)->traverse(*tapeHead);
				printVector(operations);
				write(char(operations.at(0)));
				move(bool(operations.at(1)));
				currentState = operations.at(2);
				moved = true;
			}
		}

		std::cout << "Current state: " << currentState << std::endl;
		printTape();
		printTapeHead();

		if (!moved) return "The machine crashed";
	}

	return getTapeAsString();
}

void TuringMachine::addEdge(std::shared_ptr<State> firstState, std::shared_ptr<State> secondState, std::shared_ptr<Edge> edge) {
	// Check if a link exists
	for (auto& link : links) {
		if (link->checkLink(*firstState, *secondState)) {
			std::cout << "here" << std::endl;
			link->addEdge(edge);
			std::cout << "Created edge (" << edge->getRead() << ", " << edge->getWrite() << ", " << edge->getDirection() << ") on link " << firstState->getNum() << " to " << secondState->getNum() << std::endl;
			return;
		}
	}

	// Otherwise create one
	links.push_back(std::shared_ptr<Link>::shared_ptr(new Link(firstState, secondState, edge)));
	std::cout << "Created edge (" << edge->getRead() << ", " << edge->getWrite() << ", " << edge->getDirection() << ") on link " << firstState->getNum() << " to " << secondState->getNum() << std::endl;
}

void TuringMachine::move(bool dir) {
	if (dir) tapeHead--;
	else tapeHead++;
}

void TuringMachine::printTape() {
	std::cout << "The Tape: " << getTapeAsString() << std::endl;
}

void TuringMachine::printTapeHead() {
	std::cout << "Tape Head: " << *tapeHead << std::endl;
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

std::string getLine() {
	return "=========================================\n\n";
}

std::string TuringMachine::machineDecode(std::string machine) {
	int from, to, lineStart, sFrom, sTo, i = 0;
	char read, write, curr;
	bool dir;
	std::string localMachine = machine, ret;

	std::cout << "Machine Decoding" << std::endl << getLine();

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
			states.push_back(std::shared_ptr<State>::shared_ptr(new State(from, from == 1)));
			std::cout << "Created state " << from << std::endl;
		}

		if (sTo == -1 && sTo != sFrom) {
			states.push_back(std::shared_ptr<State>::shared_ptr(new State(to, to == 1)));
			std::cout << "Created state " << to << std::endl;
		}

		addEdge(std::shared_ptr<State>::shared_ptr(states.at(from)), std::shared_ptr<State>::shared_ptr(states.at(to)), std::shared_ptr<Edge>(new Edge(read, write, dir)));
		ret = ret + std::to_string(from) + "\t" + std::to_string(to) + "\t" + read + "\t" + write + "\t" + (dir ? "L" : "R") + "\n";
		//std::cout << from << "\t" << to << "\t" << read << "\t" << write << "\t" << (dir ? "L" : "R") << std::endl;
	}

	setTape(machine.substr(i, std::size(localMachine) - (unsigned)i) + "^^");

	return ret;
}

char TuringMachine::convertChar(std::string code) {
	if (code == "aa") return 'a';
	else if (code == "ab") return 'b';
	else if (code == "ba") return '^';
	else if (code == "bb") return '#';
	else return '!';
}

std::vector<int> TuringMachine::getLinks(const State& start) {
	std::vector<int> ret;
	int counter = 0;

	for (const auto& link : links) {
		if (link->checkLink(start)) {
			ret.push_back(counter);
			counter++;
		}
	}

	return ret;
}

void TuringMachine::write(char letter) {
	*tapeHead = letter;
}