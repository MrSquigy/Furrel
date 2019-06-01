#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
	Edge(char read, char write, bool dir);
	bool checkCross(char letter);
	char getRead();
	char getWrite();
	bool getDirection();
private:
	char read;
	char write;
	bool dir;
};

#endif // EDGE_H