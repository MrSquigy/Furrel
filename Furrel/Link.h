// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#ifndef LINK_H
#define LINK_H

#include <vector>
#include "Edge.h"
#include "State.h"

class Link {
public:
	/* Constructor with 2 States and an Edge */
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end, std::shared_ptr<Edge> edge);
	
	/* Constructor with 2 States */
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end);

	/* Adds an existing Edge */
	void addEdge(std::shared_ptr<Edge> edge);

	/* Creates and adds an Edge */
	void addEdge(char read, char write, bool dir);

	/* Returns true if an Edge is traversable */
	bool canCross(char letter);

	/* Returns true if this link is between the States passed */
	bool checkLink(const State& start, const State& end);
private:
	/* Start State */
	std::shared_ptr<State> startState;

	/* End State */
	std::shared_ptr<State> endState;

	/* Vector of Edges */
	std::vector<std::shared_ptr<Edge>> edges;
};

#endif // !LINK_H