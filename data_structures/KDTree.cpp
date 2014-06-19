// Author: Kenji Hata
// Copyright: April 2014
#include "KDTree.hpp"

#define BIN_SIZE 5
using namespace std;
int gl_axis=0;

bool comparePoint(const cVector3d &x, const cVector3d &y){
	return x.get(gl_axis) < y.get(gl_axis);
}

KDTree::KDTree(std::vector<cVector3d> v){
	root = makeTree(v);
}

KDTree::Node* KDTree::makeTree(std::vector<cVector3d> &v){
	if(v.size() <= 0) return NULL;
	KDTree::Node *n = new KDTree::Node();
	if(v.size() > BIN_SIZE) n->v = NULL;
	else{
		n->v = new std::vector<cVector3d>(v);
		return n;
	}
	double varx=0, vary=0, varz =0, meanx=0, meany=0, meanz=0;
	for (size_t i=0; i<v.size(); i++){
		meanx += v[i](0); meany+=v[i](1); meanz+=v[i](2);
	}
	meanx /= v.size(); meany /= v.size(); meanz /= v.size();
	for (size_t i=0; i<v.size(); i++){
		varx += pow(v[i](0)-meanx,2); vary+=pow(v[i](1)-meany, 2); varz+=pow(v[i](2)-meanz, 2);
	}
	if (varx > vary && varx > varz)	gl_axis = 0;
	else if(vary > varx && vary > varz) gl_axis = 1;
	else gl_axis = 2;
	n->axis = gl_axis;
	int median  = v.size()/2;
	std::sort(v.begin(), v.end(), comparePoint);
	n->median_val = v[median](gl_axis);
	std::vector<cVector3d> left, right;
	for (size_t i=0; i<median; i++){
		left.push_back(v[i]);
	}
	for (size_t i=median; i<v.size(); i++){
		right.push_back(v[i]);
	}
	n->left = makeTree(left);
	n->right = makeTree(right);
	return n;
}

std::vector<cVector3d> KDTree::getNearbyPoints(cVector3d x, double r){
	std::vector<cVector3d> ans;
	checkHalfspace(ans, x, r, root);
	return ans;
}

void KDTree::checkHalfspace(std::vector<cVector3d> &v, const cVector3d &x, double r, Node *n){
	if(n == NULL) return;
	if(n->v){
		v.insert(v.end(), n->v->begin(), n->v->end());
	}else{
		int axis = n->axis;
		if(abs(n->median_val - x.get(axis)) <= r){
			checkHalfspace(v, x, r, n->left);
			checkHalfspace(v, x, r, n->right);
		}
		else{
			if(n->median_val > x.get(axis))
				checkHalfspace(v, x, r, n->left);
			else
				checkHalfspace(v, x, r, n->right);
		}
	}
}

void KDTree::Node::print(int depth, int& max_depth, int& num_leaves,
		int& num_nodes, int& num_points){
	    // Update values
	    num_nodes++;

	    // Prepend tabs for readability
	    for(int i = 0; i < depth; ++i) cout << "|  ";

	    // Print if leaf
	    if(v)
	    {
	        num_leaves++;
	        num_points += (int)v->size();
	        if(depth > max_depth) max_depth = depth;
	        cout << "Leaf: ";
	    }
	    else cout << "Node: ";

//	    cout << "lower=" << lowerbounds.str(3) << ", upper=" << upperbounds.str(3);

	    if(v) cout << ", points=" << v->size();

	    cout << "\n";

	    if(!v)
	    {
	        left->print(depth+1,max_depth,num_leaves,num_nodes,num_points);
	        right->print(depth+1,max_depth,num_leaves,num_nodes,num_points);
	    }
}
