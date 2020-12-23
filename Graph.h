#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <list>

#include <iostream>
#include <cstdlib>
#include <ctime>

const int DATA_ERR =-1;
using namespace std;

class Nodo;
class Cluster;
class Arista;

class Nodo{
public:
	int x;
	int y;
	int rgb;
	long id;
	Cluster *segmento;
	Nodo() = default;
	Nodo(int xx, int yy, int a, int &altura){
		x = xx;
		y = yy;
		rgb = a;
		id = altura*xx + yy;
	}
	bool operator<(Nodo &nodo2){
		if(this->x == nodo2.x){
			return this->y < nodo2.y;
		}
		else{
			return this->x < nodo2.x;
		}
	}
	bool operator>(Nodo &nodo2){
		if(this->x == nodo2.x){
			return this->y > nodo2.y;
		}
		else{
			return this->x > nodo2.x;
		}
	}
};

class Arista{
public:
	Nodo* A;
	Nodo* B;
	int peso;
	Arista() = default;
	Arista(Nodo *a, Nodo *b){
		A = a;
		B = b;
		peso = abs(a->rgb - b->rgb);
	}
	bool operator<(Arista &arista2){
		return this->peso < arista2.peso;
	}
};
bool comparacion_arista_pointers(Arista *a1, Arista *a2){
	return a1->peso < a2->peso;
}


class Cluster{
public:
	vector<Nodo*> asociados;
	int cardinalidad;
	int max_arista;
	list<Cluster*>::iterator it;

	Cluster() = default;
	Cluster(Nodo* n){
		max_arista = DATA_ERR;
		asociados.push_back(n);
		n->segmento = this;
		cardinalidad = 1;
	}
	void agregar(Arista *a){
		if(a->peso > max_arista){
			max_arista = a->peso;
		}
		if(a->A->segmento != this){
			agregar(a->A->segmento);
			delete(a->A->segmento);
			return;
		}
		if(a->B->segmento != this){
			agregar(a->B->segmento);
			delete(a->B->segmento);
			return;
		}
	}
	void agregar(Cluster *c){
		for(auto &n:c->asociados){
			n->segmento = this;
			asociados.push_back(n);
			++cardinalidad;
		}
		if(c->max_arista > max_arista){
			max_arista = c->max_arista;
		}
		delete(c);
	}
	void agregar(Cluster *c, int p){
		for(auto &n:c->asociados){
			n->segmento = this;
			asociados.push_back(n);
			++cardinalidad;
		}
		if(c->max_arista > max_arista){
			max_arista = c->max_arista;
		}
		if(p > max_arista){
			max_arista = p;
		}
		delete(c);
	}
};

bool comparacion_cluster_pointers(Cluster *c1, Cluster *c2){
	return c1->cardinalidad > c2->cardinalidad;
}


class Grafo{
	vector<Arista*> aristas;
	int ancho;
	int altura;
	list<Cluster*> clusteres;
public:
	Grafo(string filename, bool malla8 = false){
		ifstream ifile(filename);
		string a, b, cs;
		int ia, ib, ic;
		ifile >> ia >> ib;
		this -> altura  = ia;
		this -> ancho = ib;

		Nodo* matrix[altura][ancho];
		// Crear nodos
		for(int i=0; i< altura; ++i){
			for(int j=0; j< ancho; ++j){
				ifile >> a;
				ia = stoi(a);
				Nodo *aux = new Nodo(i, j, ia,/* ib, ic,*/ altura);
				matrix[i][j] = aux;
				Cluster *c = new Cluster(aux);
				clusteres.push_back(c);
				c->it = --clusteres.end();
			}
		}
		ifile.close();

		// Crear aristas
		for(int i=0; i< altura-1; ++i){
			for(int j=0; j<ancho-1; ++j){
				Arista *a1 = new Arista(matrix[i][j], matrix[i+1][j]);
				Arista *a2 = new Arista(matrix[i][j], matrix[i][j+1]);
				aristas.push_back(a1);
				aristas.push_back(a2);
			}
		}

		if(malla8){
			for(int i = 0; i< altura-1; ++i){
				for(int j = 0; j< ancho-1; ++j){
					Arista *a3 = new Arista(matrix[i][j], matrix[i+1][j+1]); 
					Arista *a4 = new Arista(matrix[i][j+1], matrix[i+1][j]);
					aristas.push_back(a3);
					aristas.push_back(a4);
				}
			}
			for(int j = 0; j < ancho-1; ++j){
				Arista *a1 = new Arista(matrix[altura-1][j], matrix[altura-1][j+1]);
				aristas.push_back(a1);
			}
			for(int i = 0; i < altura-1; ++i){
				Arista *a1 = new Arista(matrix[i][ancho-1], matrix[i+1][ancho-1]);
				aristas.push_back(a1);
			}
		}
		else{
			clusteres.pop_back();
		}
		sort(aristas.begin(), aristas.end(), comparacion_arista_pointers);
	}

	double MInt(Arista *a, double k){
		double taoA, taoB;
		double maxA = a->A->segmento->max_arista;
		double maxB = a->B->segmento->max_arista;
		int carA = a->A->segmento->cardinalidad;
		int carB = a->B->segmento->cardinalidad;
		if(maxA == -1){
			maxA = 0;
		}
		if(maxB == -1){
			maxB = 0;
		}
		return min(maxA + (k/carA), maxB + (k/carB));
	}
	void Segmentar(double k){
		cout << "INIT: " << clusteres.size() << endl;
		Arista *a;
		long aristas_n = aristas.size();
		double MInt_v;
		for(long i=0; i < aristas_n; ++i){
			a = aristas[i];
			if(a->A->segmento != a->B->segmento){
				MInt_v = MInt(a, k);
				if(a->peso <= MInt_v){
					this->clusteres.erase(a->B->segmento->it);
					a->A->segmento->agregar(a->B->segmento, a->peso);
				}
			}
		}
		cout << "FINAL: "<< clusteres.size() << endl;
	}

	void Make_image(string s = "seg_img.out" ){
		s = "images_files/" + s;
		int newImg[altura][ancho];
		long i = 0;
		clusteres.sort(comparacion_cluster_pointers);

		for(auto &c:clusteres){
			for(auto &n:(c->asociados)){
				newImg[n->x][n->y] = i;
			}
			++i;
		}
		newImg[altura-1][ancho-1] = i;
		ofstream ofile(s);
		ofile << altura << " " << ancho << " "<< clusteres.size() << "\n";

		for(long i = 0; i < altura; ++i){
			for(long j = 0; j < ancho; ++j){
				ofile << newImg[i][j] << "\n";
			}
		}
		ofile.close();
	}

};


#endif