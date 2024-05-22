#include <vector>
#include "Alice.h"

// you may define some global variables, but it does not work if you try to transfer any information from function Alice() to function Bob() through these variables.
// you had better not use the same global variables in function Alice() and in function Bob().

std::vector<std::pair<int,int>> Alice(){
	// add your code here
	
	// change below into your code
    long long x = setN(4);
    return std::vector<std::pair<int,int>>{{1, 2}, {2, 3}, {2, 4}};
}
