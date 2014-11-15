#ifndef PRIORITY_QUEUE_HPP_
#define PRIORITY_QUEUE_HPP_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <float.h>

// A crude implementation of a priority queue
// Fibonacci Heap would definitely speed this up.
template<class T>
class PriorityQueue{
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

	// returns the max state, while removing it from the queue.
	// furthermore, it returns by reference the cost.
	// assumes that size() != 0
	T removeMax(double& cost){
		double maxVal = -DBL_MAX;
		T maxState;
		for (typename std::map<T, double>::iterator iter = priorityMap.begin(); iter != priorityMap.end(); ++iter){
			if (iter->second > maxVal){
				maxVal = iter->second;
				maxState = iter->first;
			}
		}
		cost = maxVal;
		priorityMap.erase(maxState);
		return maxState;
	};

	int getSize(){
		return priorityMap.size();
	};

	std::vector<T> getKeys(){
		std::vector<T> v;
		for (typename std::map<T, double>::iterator iter = priorityMap.begin(); iter != priorityMap.end(); ++iter)
		{
			v.push_back(iter->first);
		}
		return v;
	};
private:
	std::map<T, double> priorityMap;
};

#endif /* PRIORITY_QUEUE_HPP_ */ 
