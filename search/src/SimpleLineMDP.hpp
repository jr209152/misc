#ifndef SIMPLE_LINE_MDP_HPP_
#define SIMPLE_LINE_MDP_HPP_

#include "MDP.hpp"

class SimpleLineMDP : public MDP<int>{
public:
	SimpleLineMDP(){ 
		start_state = Node<int> ("start", 0, 0);
	};
	Node<int> getStartState(){ 
		return start_state;
	};

	bool isGoal(Node<int> state){
		return state.state ==10;
	};

	std::vector<Node<int> *> getSuccAndCost(Node<int> *node){
		std::vector<Node<int> *> ret_val;
		Node<int> *ns = new Node<int>("lower", node->state-1, 1, node); 
		ret_val.push_back(ns);
		ns = new Node<int> ("up", node->state+1, 2, node);
		ret_val.push_back(ns);
		ns = new Node<int>("up2", node->state+3, 3, node);
		ret_val.push_back(ns);
		return ret_val;
	};
};

#endif /* SIMPLE_LINE_MDP_ */ 
