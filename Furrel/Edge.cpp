// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include <iostream>
#include "Edge.h"

/* Public Member Functions */

Edge::Edge(char readC, char writeC, bool dirC) : read(readC), write(writeC), dir(dirC) {}

/* Getter Functions */

char Edge::getRead() { return char(read); }

char Edge::getWrite() { return write; }

bool Edge::getDirection() { return dir; }