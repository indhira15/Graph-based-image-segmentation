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
	pair<int,int> p;
	file.open("images_list.txt");
	while(file >> line){
		Grafo gf("images_temporal/" + line + ".in");
		p = gf.Segmentar(k);
		gf.Make_image("images_temporal/" + line +"_k_" + to_string(k) + "init_clust=" + to_string(p.first) +  "_final_clust=" + to_string(p.second)  + ".out");
	}
}

void segment_all(vector<int> ks){
	fstream file;
	string line;
	pair<int,int> p;
	file.open("images_list.txt");
	while(file >> line){
		for(auto &i:ks){
			cout << "segmenting " << line << " with k " << i<< endl;
			Grafo gf("images_temporal/" + line + ".in");
			p = gf.Segmentar(i);
			gf.Make_image("images_temporal/" + line +"_k_" + to_string(i) + "init_clust=" + to_string(p.first) +  "_final_clust=" + to_string(p.second)  + ".out");
		}
	}

}

int main(){

	vector<int> v{500,750,1000,1250,1500,2000,3000,4000,5000,10000};
	segment_all(v);


	return 0;
}