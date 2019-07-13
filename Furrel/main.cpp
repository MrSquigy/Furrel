// Copyright (c) 2019 Jonathan Vice
// This file is part of Furrel.

#include <iostream>
#include "TuringMachine.h"

int main() {
	// Test tm that adds two numbers together, of the form a*ba*, with input 1, 1
	std::string adderTM = "bbaaaabbababaabababaaaababaabbabaaaabaaabaabab#aba";
	
	TuringMachine adder(adderTM);

	return 0;
}