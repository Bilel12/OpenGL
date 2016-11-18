#include "Shape.h"

int main() {
	Shape shape;

	shape.drawSphere(3., 2., 2.);

	shape.buildSphere(3., 2., 2.);

	/*for (auto iter = shape.vertices_sphere.begin(); iter != shape.vertices_sphere.end(); iter += 12) {
		cout << *iter << endl;
	}*/

	cout << shape.vertices_sphere.size();

	/*for (int i = 0; i < shape.vertices_sphere.size(); i++) {
		cout << shape.vertices_sphere.at(i) << endl;
	}*/
	std::cin.get();

	return 0;
}