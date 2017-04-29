#include "patch.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <exception>
#include <math.h>


using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::exception;
using std::istringstream;
using std::istream_iterator;


int *patches;
int patches_size;
vector<Vertex*> points;
vector<Vertex*> final;

void patchBezier(int tesselate);
Vertex* calcular(float t, float *p1, float *p2, float *p3, float *p4);
Vertex* bezier(float u, float v, int p);

vector<Vertex*> patch(char * file,int n) {
	string line;
	ifstream ifile(file);
	int j = 0;
	
	if (ifile.fail())
    	throw std::ios_base::failure(string("Couldn't find file: ") + file);
	
	getline(ifile,line);    
	
	patches_size = stoi(line);
	patches = (int *) malloc (sizeof(int)*patches_size*16);

	for(int i = 0; i!=patches_size; i++){
		getline(ifile,line);

		istringstream buf(line);
		istream_iterator<string> beg(buf), end;
		vector<string> tokens(beg, end);

		for(auto& s: tokens)
        	patches[j++] = stoi(s) ;
	}
	getline(ifile,line);
	while(getline(ifile,line)){
		try {
			Vertex *v = new Vertex(line);
            points.push_back(v);
        } catch (exception& e) {
            throw std::invalid_argument(
              std::string("Couldn't parse file ") + file + ": " + e.what());
        }
	}

	patchBezier(n);
	free(patches);

	return final;
}

void patchBezier(int tesselate) {
	float inc = 1.0 / tesselate, u, v, u2, v2;
	int patchN;

	for(int w=0;w!= patches_size;w++){
		patchN = w * 16;
		for (int i = 0; i < tesselate; i++) {
			for (int j = 0; j < tesselate; j++) {
				u = i*inc;
				v = j*inc;
				u2 = (i + 1)*inc;
				v2 = (j + 1)*inc;

				Vertex* p0 = bezier(u , v , patchN);
				Vertex* p1 = bezier(u , v2, patchN);
				Vertex* p2 = bezier(u2, v , patchN);
				Vertex* p3 = bezier(u2, v2, patchN);

				final.push_back(p0);
				final.push_back(p2);
				final.push_back(p3);

				final.push_back(p0);
				final.push_back(p3);
				final.push_back(p1);
			}
		}
	}
}

Vertex* bezier(float u, float v, int p) {
	float bz[4][3], res[4][3];
	int i, j = 0, k = 0;

	for (i = 0; i < 16; i++) {
		bz[j][0] = points.at(patches[p+i])->getX();
		bz[j][1] = points.at(patches[p+i])->getY();
		bz[j][2] = points.at(patches[p+i])->getZ();
		j++;

		if (j % 4 == 0) {
			Vertex *p = calcular(u, bz[0], bz[1], bz[2], bz[3]);
			res[k][0] = p->getX();
			res[k][1] = p->getY();
			res[k][2] = p->getZ();

			k++;
			j = 0;
		}
	}
	return calcular(v, res[0], res[1], res[2], res[3]);
}

Vertex* calcular(float t, float *p1, float *p2, float *p3, float *p4) {
	float res[3];

	float it = 1.0 - t;

	float b0 = it*it*it;
	float b1 = 3 * t*it*it;
	float b2 = 3 * t*t*it;
	float b3 = t*t*t;

	res[0] = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
	res[1] = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
	res[2] = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];

	return (new Vertex(res[0], res[1], res[2]));
}