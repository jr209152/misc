#ifndef UNIFORM_COST_SEARCH_HPP_
#define UNIFORM_COST_SEARCH_HPP_

#include "Node.hpp"
#include "MDP.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <float.h>

// A crude implementation of a priority queue
// Fibonacci Heap would definitely speed this up.
template<class T>
struct PriorityQueue{
public:
	void update(T state, double newPriority){
		if (priorityMap.find(state) != priorityMap.end()){
			if (newPriority < priorityMap[state])
				priorityMap[state] = newPriority;
		}
		else {
			priorityMap[state] = newPriority;
		}
	};
	// returns the min state, while removing it from the queue.
	// furthermore, it returns by reference the cost.
	// assumes that size() != 0
	T removeMin(double& cost){
		double minVal = DBL_MAX;
		T minState;
		for (typename std::map<T, double>::iterator iter = priorityMap.begin(); iter != priorityMap.end(); ++iter){
			if (iter->second < minVal){
				minVal = iter->second;
				minState = iter->first;
			}
		}
		cost = minVal;
		priorityMap.erase(minState);
		return minState;
	};

	int getSize(){
		return priorityMap.size();
	}
private:
	std::map<T, double> priorityMap;
};

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
				std::cout << "Problem Solved\n\n";
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
