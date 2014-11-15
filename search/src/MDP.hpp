#ifndef MDP_HPP_
#define MDP_HPP_

#include <vector>
#include "Node.hpp"

template <class T>
class MDP{
public:
	MDP(){};
	virtual Node<T> getStartState() = 0;
	virtual bool isGoal(Node<T> state) = 0;
	virtual std::vector<Node<T> *> getSuccAndCost(Node<T> *state) = 0;
protected:
	Node<T> start_state;
};

#endif /* MDP_ */ 
