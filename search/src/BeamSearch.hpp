#ifndef BEAM_SEARCH_HPP_
#define BEAM_SEARCH_HPP_

#include "Node.hpp"
#include "MDP.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <float.h>

template <class T> 
class BeamSearch{
public:
	BeamSearch(MDP<T> *mdp, int K){
		problem = mdp;
		totalCost = 0;
		numStatesExplored = 0;
		this->K = K;
	};

	void solve(){
		PriorityQueue<Node<T> *> frontier;

		// add the start state
		Node<T> startState = problem->getStartState();
		frontier.update(&startState, 0);

		while (true){
			PriorityQueue<Node<T> *> newFrontier;
			while (frontier.getSize() > 0){
				double pastCost = 0;
				Node<T> *state = frontier.removeMax(pastCost);
				numStatesExplored++;

				// check if we reached the goal
				if (problem->isGoal(*state)){
					std::cout << "Problem Solved"<<std::endl;
					// print out rest of the stuff
					std::cout << "COST: " << pastCost << std::endl;
					while (*state != startState){
						std::cout << state->action_name << std::endl;
						state = state->parent;
					}
					return;
				}

				// append the successor states
				std::vector<Node<T> *> succ_vec = problem->getSuccAndCost(state);
				for (size_t i = 0; i < succ_vec.size(); i++){
					Node<T> *ns = succ_vec[i];
					newFrontier.update(ns, ns->cost + pastCost); // maybe add pastcost?
				}
			}
			
			// take K best states
			double temp = 0;
			while (newFrontier.getSize() > K){
				newFrontier.removeMax(temp);
			}
			frontier = newFrontier;	
		}
		std::cout << "No path found" << std::endl;
	};

private:
	MDP<T> *problem;
	double totalCost;
	double numStatesExplored;
	int K;
};

#endif /* BEAM_SEARCH_HPP_ */ 
