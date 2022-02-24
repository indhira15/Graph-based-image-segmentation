#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Graph.h"

using namespace std;

void segment_all(int k){
	fstream file;
	string line;

	file.open("images_list.txt");
	while(file >> line){
		Grafo gf("images_temporal/" + line + ".in");
		gf.Segmentar(k);
		gf.Make_image("images_temporal/" + line +"_" + to_string(k) + ".out");
	}
}

void segment_all(vector<int> ks){
	fstream file;
	string line;

	file.open("images_list.txt");
	while(file >> line){
		for(auto &i:ks){
			Grafo gf("images_temporal/" + line + ".in");
			gf.Segmentar(i);
			gf.Make_image("images_temporal/" + line + "_" + to_string(i) + ".out");
		}
	}
}

int main(){

	segment_all(1100);

	return 0;
}