// Author: Kenji Hata
// Copyright: April 2014

#ifndef CHAIKDTREE_HPP_
#define CHAIKDTREE_HPP_

#include <stdlib>
#include "chai3d.h"

class ChaiKDTree{
public:
	ChaiKDTree(std::vector<cGenericObject*> v, int depth=0);
	typedef struct Node{
		Node *left;
		Node *right;
	}Node;
private:
	void partitionAroundMedian(int left, int right){
		int pivot = (left+right)/2;
		double pivotValue = points[pivot];
	}
	std::vector<cGenericObject*> points;
};


#endif /* CHAIKDTREE_HPP_ */
