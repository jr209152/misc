#include "UniformCostSearch.hpp"
#include "MDP.hpp"
#include "Node.hpp"
#include "SimpleLineMDP.hpp"
#include "BeamSearch.hpp"
#include <iostream>

int main(){
	SimpleLineMDP *mdp = new SimpleLineMDP();
	std:: cout << "UCS START" << std::endl;
	UniformCostSearch<int> ucs = UniformCostSearch<int> (mdp);
	ucs.solve();
	std::cout << "UCS DONE" << std::endl;

	std::cout << "\n\n";

	std:: cout << "BEAM START" << std::endl;
	BeamSearch<int> beam = BeamSearch<int> (mdp,2);
	beam.solve();
	std::cout << "BEAM DONE" << std::endl;
	return 0;
}