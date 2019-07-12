// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#ifndef LINK_H
#define LINK_H

#include <vector>
#include "Edge.h"
#include "State.h"

class Link {
public:
	/* Constructor with start and end States and an Edge between them */
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end, std::shared_ptr<Edge> edge);
	
	/* Constructor with start and end States */
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end);

	/* Adds an existing Edge */
	void addEdge(std::shared_ptr<Edge> edge);

	/* Creates and adds an Edge */
	void addEdge(char read, char write, bool dir);

	/* Returns true if an Edge is traversable */
	bool getTraversable(char letter);

	/* Traverses an Edge 
	   Precondition: getTraversable == true
	   Return val:   [char LetterToWrite, bool DirectionToMove, int NextStateNumber]
	*/
	std::vector<int> traverse(char letter);

	/* Returns true if this link is between the States passed */
	bool checkLink(const State& start, const State& end);

	/* Overload for first State only */
	bool checkLink(const State& start);
private:
	/* Start State */
	std::shared_ptr<State> startState;

	/* End State */
	std::shared_ptr<State> endState;

	/* Vector of Edges */
	std::vector<std::shared_ptr<Edge>> edges;
};

#endif // !LINK_H