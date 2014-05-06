// Author: Kenji Hata
// Copyright: April 2014

#include "SpatialHash.hpp"
#include <float.h>

SpatialHash::SpatialHash(std::vector<cVector3d> &v, double r){
	this->r = r;
	minx = DBL_MAX; miny = DBL_MAX; minz = DBL_MAX; maxx = DBL_MIN; maxy = DBL_MIN; maxz = DBL_MIN;
	for (size_t i = 0; i<v.size(); i++){
		if(minx < v[i](0)) minx = v[i](0);
		if(miny < v[i](1)) miny = v[i](1);
		if(minz < v[i](2)) minz = v[i](2);
		if(maxx > v[i](0)) maxx = v[i](0);
		if(maxy > v[i](1)) maxy = v[i](1);
		if(maxz > v[i](2)) maxz = v[i](2);
	}
	x_buckets = (maxx- minx)/r + 1;
	y_buckets = (maxz- miny)/r + 1;
	z_buckets = (maxz- minz)/r + 1;
	for (size_t i=0; i < v.size(); i++){
		Bucket b;
		b.x = (v[i](0)-minx)/r; b.y = (v[i](1)-miny)/r; b.z = (v[i](2)-minz)/r;
		if (map.find(b) == map.end()){
			std::vector<cVector3d> tmp;
			tmp.push_back(v[i]);
			map.insert(std::pair<Bucket, std::vector<cVector3d> >(b, tmp));
		}
		else{
			map[b].push_back(v[i]);
		}
	}
}

	std::vector<cVector3d> SpatialHash::getNearbyPoints(cVector3d &x){
		std::vector<cVector3d> ans;
		int offset[] = {-1, 0, 1};
		double x_bucket = x(0)-minx;
		double y_bucket = x(1)-miny;
		double z_bucket = x(2)-minz;
		for(size_t i=0; i<27; i++){
			if(x_bucket + offset[i%3] < 0 || x_bucket + offset[i%3] >= x_buckets ||
					y_bucket + offset[(i/3)%3] < 0 || y_bucket + offset[(i/3)%3] >= y_buckets||
					z_bucket + offset[(i/9)%3] < 0 || z_bucket + offset[(i/9)%3] >= z_buckets ){
				Bucket b; b.x = int(x_bucket/r)+offset[i%3]; b.y = int(y_bucket/r)+offset[(i/3)%3]; b.z = int(z_bucket/r)+offset[(i/9)%3];
				std::vector<cVector3d> tmp = map[b];
				ans.insert(ans.end(), tmp.begin(), tmp.end());
			}
		}
		return ans;
	}


