#include "Edge.h"

Edge::Edge(char readC, char writeC, bool dirC) : read(readC), write(writeC), dir(dirC) {}

bool Edge::checkCross(char letter) { return letter == read; }

char Edge::getRead() { return read; }

char Edge::getWrite() { return write; }

bool Edge::getDirection() { return dir; }