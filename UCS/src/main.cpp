#include "UniformCostSearch.hpp"
#include "MDP.hpp"
#include "Node.hpp"
#include "SimpleLineMDP.hpp"
#include <iostream>

int main(){
	SimpleLineMDP *mdp = new SimpleLineMDP();
	UniformCostSearch<int> ucs = UniformCostSearch<int> (mdp);
	ucs.solve();
	std::cout << "DONE" << std::endl;
	system("PAUSE");
	return 0;
}