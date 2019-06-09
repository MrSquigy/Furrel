#ifndef STATE_H
#define STATE_H

#include <vector>

class State {
public:
	State(int stateNum, bool halt = false);
	bool operator==(const State& ste);
	int getNum();
	bool isHaltState();
private:
	int num;
	bool haltState;
};

#endif // STATE_H