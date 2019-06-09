#include <iostream>
#include "TuringMachine.h"

int main() {
	// Test tm that adds 1 to a number of the form a*b
	std::string adderTM = "bbaaaabbababaabababaaaababaabbabaaaabaaabaaba#";
	
	TuringMachine adder(adderTM);

	return 0;
}