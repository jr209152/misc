// Author: Kenji Hata
// Copyright: April 2014

#ifndef SPATIALHASH_HPP_
#define SPATIALHASH_HPP_

#include "chai3d.h"
using namespace chai3d;

class SpatialHash{
	public:
	SpatialHash(std::vector<cVector3d> &v, double r);
	std::vector<cVector3d> getNearbyPoints(cVector3d &x);
	struct Bucket{
		int x, y, z;
		bool operator==(const Bucket &c) const{
			return x == c.x && y==c.y && z==c.z;
		}
		bool operator<(const Bucket &c) const{
			return x < c.x && y<c.y && z<c.z;
		}
	};
	private:
	double minx, miny, minz, maxx, maxy, maxz, r;
	int x_buckets, y_buckets, z_buckets;
	std::map<Bucket, std::vector<cVector3d> > map;
};



#endif /* SPATIALHASH_HPP_ */
