#include "io.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <getopt.h>
#include <vector>

#include "io.cpp"

//void readObj(std::string objIn, std::vector<Eigen::Vector3d> pts, std::vector<Triangle> tris){
	//std::ifstream in(objIn.c_str(), std::ios_base::in);
	//std::string line;
  //	//Fill fill;
//	while (in){
//		getline(in, line);
//		if(line.substr(0,1)=="v"){
			//double x,y,z;
//			Eigen::Vector3d v;	
//			std::stringstream ss(line.substr(2));
//			ss>>v[0]>>v[1]>>v[2];
//			pts.push_back(v);			
//		} else{
//			std::stringstream ss(line.substr(2));
//			Eigen::Vector3d v;
//			ss>>v[0]>>v[1]>>v[2];
//			//tris.push_back(new Triangle(v[0],v[1],v[2]));			
//		}
//	}

//}

//void writeObj(std::string objOut, std::vector<Eigen::Vector3d> pts, std::vector<Triangle> tris){
//}

int main(int argc, char *argv[]){
	std::vector<Tri> tris;
	std::vector<Eigen::Vector3d> pts;
	std::vector<double> m;
	std::vector<Eigen::Vector3d> lap;

	bool fileOpen = readObjFile(argv[1], pts, tris);
	if(!fileOpen){	
		printf("File Failed \n");
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
