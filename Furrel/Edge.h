// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#ifndef EDGE_H
#define EDGE_H

#include <vector>

class Edge {
public:
	/* Default Constructor
	
	@param readC   Character to be read when traversing
	@param writeC	 Character to be written when traversing
	@param dirC    Bool to represent direction to take while traversing: true for left, false for right
	
	*/
	Edge(char readC, char writeC, bool dirC);

	/* Returns character to be read while traversing */
	char getRead();

	/* Returns character to be written while traversing */
	char getWrite();

	/* Returns direction to take while traversing */
	bool getDirection();
private:
	/* Character to be read while traversing */
	char read;

	/* Character to be written while traversing */
	char write;

	/* Bool to represent direction to take while traversing */
	bool dir;
};

#endif // EDGE_H