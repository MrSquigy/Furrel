#ifndef EDGE_H
#define EDGE_H

#include <vector>

class Edge {
public:
	Edge(char readC, char writeC, bool dirC);
	char getRead();
	char getWrite();
	bool getDirection();
private:
	char read;
	char write;
	bool dir;
};

#endif // EDGE_H