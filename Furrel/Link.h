#ifndef LINK_H
#define LINK_H

#include <vector>
#include "Edge.h"
#include "State.h"

class Link {
public:
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end, std::shared_ptr<Edge> edge);
	Link(std::shared_ptr<State> start, std::shared_ptr<State> end);
	void addEdge(std::shared_ptr<Edge> edge);
	void addEdge(char read, char write, bool dir);
	bool canCross(char letter);
	bool checkLink(const State& start, const State& end);
private:
	std::shared_ptr<State> startState;
	std::shared_ptr<State> endState;
	std::vector<std::shared_ptr<Edge>> edges;
};

#endif // !LINK_H