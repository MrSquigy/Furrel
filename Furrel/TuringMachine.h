// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include <vector>
#include "Link.h"

class TuringMachine {
public:
	/* Constructor from machine CWL string */
	TuringMachine(std::string input = "");
	
	/* Copy constructor */
	TuringMachine(TuringMachine &tm);
	
	/* Copy assignment constructor */
	TuringMachine& operator=(TuringMachine &tm);

	/* Runs the TM */
	std::string run();
	
	/* Adds Edge and new Link if needed between States passed */
	void addEdge(std::shared_ptr<State> firstState, std::shared_ptr<State> secondState, std::shared_ptr<Edge> edge);
	
	/* Moves the tape head left or right */
	void move(bool dir);
	
	/* Prints the tape to console */
	void printTape();

	/* Prints the tape head to the console */
	void printTapeHead();
	
	/* Returns character read by the tape head */
	char getCurrentChar();

	/* Returns the tape as a string */
	std::string getTapeAsString();

	/* Set the tape to param and tape head to start */
	void setTape(std::string input);
private:
	/* Decodes the machine CWL */
	std::string machineDecode(std::string machine);
	
	/* Converts the 2-char code into a single char */
	char convertChar(std::string code);

	/* Returns vector of Links with start State passed */
	std::vector<int> getLinks(const State& start);

	/* Write char at the tape head */
	void write(char letter);
	
	/* Vector of States */
	std::vector<std::shared_ptr<State>> states;
	
	/* Vector of Links */
	std::vector<std::shared_ptr<Link>> links;
	
	/* Tape vector */
	std::vector<char> tape;

	/* Tape head iterator */
	std::vector<char>::iterator tapeHead;
};

#endif // TURING_MACHINE_H