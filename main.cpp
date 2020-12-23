#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Graph.h"

using namespace std;


int main(){

	// crea varias segmentaciones con distinto numero de k
	Grafo gf("images_files/test.in", 1);
	gf.Segmentar(500);
	gf.Make_image("seg_img_8_1.out");

	Grafo gf2("images_files/test.in", 1);
	gf2.Segmentar(800);
	gf2.Make_image("seg_img_8_2.out");

	Grafo gf3("images_files/test.in", 1);
	gf3.Segmentar(1100);
	gf3.Make_image("seg_img_8_3.out");

	Grafo gf4("images_files/test.in", 1);
	gf4.Segmentar(2000);
	gf4.Make_image("seg_img_8_4.out");


/*	gf.read("images_files/test1.in");
	gf.make_two_images();
*/

	return 0;
}