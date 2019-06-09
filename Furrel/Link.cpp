#include <iostream>
#include "Link.h"

Link::Link(std::shared_ptr<State> start, std::shared_ptr<State> end, std::shared_ptr<Edge> edge) : startState(start), endState(end) {
	edges.push_back(edge);
}

Link::Link(std::shared_ptr<State> start, std::shared_ptr<State> end) : startState(start), endState(end) {};

void Link::addEdge(std::shared_ptr<Edge> edge) {
	edges.push_back(edge);
}

void Link::addEdge(char read, char write, bool dir) {
	edges.push_back(std::shared_ptr<Edge>::shared_ptr(new Edge(read, write, dir))); // Create and transfer ownership of new Edge object
}

// Returns true if the edge is traversable, otherwise false
bool Link::canCross(char letter) { 
	for (const auto &edge : edges) {
		if (letter == edge->getRead()) {
			return true;
		}
	}

	return false;
}

bool Link::checkLink(const State& start, const State& end) {
	return *startState == start && *endState == end;
}