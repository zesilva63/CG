#include <sphere.h>

#define PI 3.14159265358979323846

void esfera(double raio, int slices, int stacks, string file_name) {

    double camadas = PI / slices;
	double rotacoes = 2 * PI / stacks;
	Vertex p = Vertex::Vertex();
	ofstream file(file_name);
	vector<Vertex> points;


	for (int i = 0; i <= slices; i++) {
		double angYX = camadas * i; // 0 a 180º na vertical

		for (int j = 0; j <= stacks; j++) {

			double angZX = rotacoes * j; // 0 a 360º na horizontal

			double x1 = raio * sin(angYX) * sin(angZX);
			double y1 = raio * cos(angYX);
			double z1 = raio * sin(angYX) * cos(angZX);

			file << x1 << " " << y1 << " " << z1 << endl;

			p = Vertex(x1 / raio, y1 / raio, z1 / raio);
			points.push_back(p);
		}
	}

	int nn = points.size();
	file << nn << endl;

	for (int i = 0; i < nn; i++) {
		Vertex p = points[i];
		file << p.getX() << "," << p.getY() << "," << p.getZ() << endl;
	}

	file.close();
}
