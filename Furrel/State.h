// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#ifndef STATE_H
#define STATE_H

#include <vector>

class State {
public:
	/* Constructor with State number and optional halt param */
	State(int stateNum, bool halt = false);

	/* Equality operator, returns true if the passed object matches this one */
	bool operator==(const State& ste);

	/* Returns the State number */
	int getNum();

	/* Returns true if this is a halt State */
	bool isHaltState();
private:
	/* State number */
	int num;

	/* Whether or not this is a halt State */
	bool haltState;
};

#endif // STATE_H