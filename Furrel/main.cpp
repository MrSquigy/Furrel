// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include <iostream>
#include "TuringMachine.h"

int main() {
	// Test tm that adds 1 to a number of the form a*b, with input 1
	std::string adderTM = "bbaaaabbababaabababaaaababaabbabaaaabaaabaabab#ab";
	
	TuringMachine adder(adderTM);

	return 0;
}