#include <iostream>
#include "Edge.h"

Edge::Edge(char readC, char writeC, bool dirC) : read(readC), write(writeC), dir(dirC) {}

char Edge::getRead() { return char(read); }

char Edge::getWrite() { return write; }

bool Edge::getDirection() { return dir; }