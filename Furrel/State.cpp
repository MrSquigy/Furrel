// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include "State.h"
#include "Edge.h"

/* Public Member Functions */

State::State(int stateNum, bool halt) : num(stateNum), haltState(halt) {}

bool State::operator==(const State& ste) { return num == ste.num; }

/* Getter Functions */

int State::getNum() { return num; }

bool State::isHaltState() { return haltState; }