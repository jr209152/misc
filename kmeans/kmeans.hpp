#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>
#include <iostream>
#include <pcl/point_types.h>
#include <cstdlib>
#include <random>

class Kmeans{
	Kmeans(std::vector<pcl::PointXYZ> v, unsigned int x){
		pts = v;
		num_bins = x;		
	};

	double squareDistance(pcl::PointXYZ a, pcl::PointXYZ b){
		return (a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y()) + (a.z()-b.z())*(a.z()-b.z());
	}

	void findCentroids(){
		for(int i=0; i < num_bins; i++){
			double x = 0, y = 0, z = 0;
			for (int j=0; j < bins[i].size(); i++){
				x += bins[i][j].x();
				y += bins[i][j].y();
				z += bins[i][j].z();
			}
			x /= bins[i].size();
			y /= bins[i].size();
			z /= bins[i].size();
			centroids[i] = pcl::PointXYZ(x,y,z);
		}
	};

	double assignPointsToCentroids(){
		double val = 0;
		for(int i=0; i < num_bins; i++){
			bins[i].clear();
		}
		for(int i=0; i < pts.size(); i++){
			double minDist = 10000000000000;
			double minBin = 0;
			for (int j=0 ; j<num_bins; j++){
				double d = squareDistance(centroids[j], pts[i]);
				if(d < minDist){
					minDist = d;
					minBin = i;
				}
			}
			val += minDist;
			bins[minBin].push_back(pts[i]);
		}
		return val;
	};

	std::vector<int> RandomSamplingWithoutReplacement(std::vector<int>& vData, int N){
    // Random generator
		std::random_device rd;
		std::mt19937 randomGenerator(rd());

		int max = static_cast<int>(vData.size()-1);
		std::vector<int> vResult;

		for (int n=1; n<=N; n++) {
			std::uniform_int_distribution<> uniformDistribution(0,max);
			int index = uniformDistribution(randomGenerator);
			std::swap(vData[index],vData[max]);
			vResult.push_back(vData[max]);
			max--;
		}

		return vResult;
	}

	double solve(){
		bins.clear();
		centroids.clear();
		std::vector<int> tmp; 
		for (int i=0; i< pts.size(); i++){
			tmp.push_back(i);
		}
		tmp = RandomSamplingWithoutReplacement(tmp, num_bins);
		for(int i =0; i < num_bins; i++){
			centroids.push_back(pts[tmp[i]]);
			bins.push_back(std::vector<pcl::PointXYZ>());
		}
		double prev = 0;
		double curr = assignPointsToCentroids();
		while (prev != curr){
			prev = curr;
			findCentroids();
			curr = assignPointsToCentroids();
		}
		return curr;
	};
private:
	std::vector<std::vector<pcl::PointXYZ> > bins;
	std::vector<pcl::PointXYZ> centroids;
	std::vector<pcl::PointXYZ> pts;
	unsigned int num_bins;
};

#endif 