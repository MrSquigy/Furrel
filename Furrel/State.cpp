#include "State.h"
#include "Edge.h"

State::State(int stateNum, bool halt) : num(stateNum), haltState(halt) {}

bool State::operator==(const State& ste) { return num == ste.num; }

int State::getNum() { return num; }

bool State::isHaltState() { return haltState; }