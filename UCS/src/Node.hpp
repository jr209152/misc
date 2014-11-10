#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>

template <class T>
struct Node{
	Node(){};
	Node(std::string str, T n, double c){
		action_name = str;
		state = n;
		cost = c;
	};
	Node(std::string str, T n, double c, Node<T>* p){
		action_name = str;
		state = n;
		cost = c;
		parent = p;
	};
	std::string action_name;
	Node<T> *parent;
	T state;
	double cost;
	bool operator<(const Node<T>& rhs) const{
		return state < rhs.state;
	}
	bool operator==(const Node<T>& rhs) const{
		return state == rhs.state;
	}
	bool operator!=(const Node<T>& rhs) const{
		return state != rhs.state;
	}
};

#endif /* NODE_HPP_*/ 
