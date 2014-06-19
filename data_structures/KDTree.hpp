// Author: Kenji Hata
// Copyright: April 2014

#ifndef KDTREE_HPP_
#define KDTREE_HPP_

#include "chai3d.h"
using namespace chai3d;
class KDTree{
public:
	KDTree(std::vector<cVector3d> v);
	struct Node{
		Node *left;
		Node *right;
		std::vector<cVector3d> *v;
		int axis;
		double median_val;

		void print(int depth, int& max_depth, int& num_leaves,
int& num_nodes, int& num_points);
	};
	Node *root;
	std::vector<cVector3d> getNearbyPoints(cVector3d x, double r);
	void printTree();
private:
	Node *makeTree(std::vector<cVector3d> &v);
	void checkHalfspace(std::vector<cVector3d> &v, const cVector3d &x, double r, Node *n);

};


#endif /* KDTREE_HPP_ */
