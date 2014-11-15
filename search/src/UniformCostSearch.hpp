#ifndef UNIFORM_COST_SEARCH_HPP_
#define UNIFORM_COST_SEARCH_HPP_

#include "Node.hpp"
#include "MDP.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <float.h>

template <class T> 
class UniformCostSearch{
public:
	UniformCostSearch(MDP<T> *mdp){
		problem = mdp;
		totalCost = 0;
		numStatesExplored = 0;
	};

	std::vector<std::string> getActions() { return actions; };
	void solve(){
		PriorityQueue<Node<T> *> frontier;

		// add the start state
		Node<T> startState = problem->getStartState();
		frontier.update(&startState, 0);

		while (true){
			// remove the lowest pastCost state
			double pastCost = 0;
			if (frontier.getSize() == 0) break;
			Node<T> *state = frontier.removeMin(pastCost);
			numStatesExplored++;

			// check if we reached the goal
			if (problem->isGoal(*state)){
				std::cout << "Problem Solved"<<std::endl;
				// print out rest of the stuff
				std::cout << "COST: "<< pastCost << std::endl;
				while (*state != startState ){
					std::cout << state->action_name << std::endl;
					state = state->parent;
				}
				return;
			}

			// go to rest of the successor states
			std::vector<Node<T> *> succ_vec = problem->getSuccAndCost(state);
			for (size_t i = 0; i < succ_vec.size(); i++){
				Node<T> *ns = succ_vec[i];
				frontier.update(ns, ns->cost + pastCost);
			}
		}
		std::cout << "No path found" << std::endl;
	};

private:
	std::vector<std::string> actions;
	MDP<T> *problem;
	double totalCost;
	double numStatesExplored;
};

#endif /* UNIFORM_COST_SEARCH_HPP_ */ 
