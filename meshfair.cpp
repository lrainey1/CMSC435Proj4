#include "io.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <getopt.h>
#include <vector>

#include "io.cpp"

void subdivide(char *argv[], std::vector<Tri> tris, std::vector<Eigen::Vector3d> pts){
	for(int j=0; j<tris.size(); j++){
		pts[tris[j][0]] = 2*pts[tris[j][0]] + (0.1875)*(pts[tris[j][0]]+pts[tris[j][1]]+pts[tris[j][2]]);
		pts[tris[j][1]] = (1-3)*pts[tris[j][1]] + (3/16)*(pts[tris[j][0]]+pts[tris[j][1]]+pts[tris[j][2]]);
		pts[tris[j][2]] = (1-3)*pts[tris[j][2]] + (3/16)*(pts[tris[j][0]]+pts[tris[j][1]]+pts[tris[j][2]]);
	}
	writeObjFile(argv[2], pts, tris);
}

int main(int argc, char *argv[]){
	std::vector<Tri> tris;
	std::vector<Eigen::Vector3d> pts;
	std::vector<double> m;
	std::vector<Eigen::Vector3d> lap;

	bool fileOpen = readObjFile(argv[1], pts, tris);
	if(!fileOpen){	
		printf("File Failed \n");
		return 0;
	}

	if(argc>5){
		std::string argID = argv[5];
		//printf("%s\n", argID);
		if(argID == "-s"){
			int eps = atoi(argv[6]);
			printf("woosh %d\n", pts[tris[1][1]]);
			subdivide(argv,tris,pts);
			return 0;	
		}
	}

	
	for(int i=0; i<atoi(argv[4]); i++){
		for(int j=0; j<pts.size(); j++){
			m.push_back(0);
			Eigen::Vector3d zlap; zlap<< 0,0,0;
			lap.push_back(zlap);
		}
	
	
		for(int z=0; z<(int)tris.size(); z++){
			lap[tris[z][0]] += pts[tris[z][1]] - pts[tris[z][0]];
			lap[tris[z][0]] += pts[tris[z][2]] - pts[tris[z][0]];

			lap[tris[z][1]] += pts[tris[z][0]] - pts[tris[z][1]];
			lap[tris[z][1]] += pts[tris[z][2]] - pts[tris[z][1]];

			lap[tris[z][2]] += pts[tris[z][0]] - pts[tris[z][2]];
			lap[tris[z][2]] += pts[tris[z][1]] - pts[tris[z][2]];

			m[tris[z][0]] += 2;
			m[tris[z][1]] += 2;
			m[tris[z][2]] += 2;					
		}

		for(int x=0; x<(int)pts.size(); x++){
			pts[x] = pts[x] + atof(argv[3]) * lap[x] / m[x];
		}
	}
	
	writeObjFile(argv[2], pts, tris);
}
