#include <iostream>
#include "KMath.h"
#include "util.h"
#include <fstream>

using namespace KT;
using namespace std;
int main() {
	println("Welcome to KTracer Engine");
	const char* welcomeSen = "This is a simple ray tracer developed from scratch";
	println(welcomeSen);
	KT::vec3 temp = 3 * vec3(1.0, 2.0, 3);
	KT::vec4 temp1 = KT::vec4(1.0, 2.0, 3, 2.3) * KT::vec4(1.3, 2.5, 4.0, 2);
	KT::ray r;
	println(temp, temp1, r);

	// output a simple ppm image
	if (0) {
		const int dimx = 800, dimy = 800;
		ofstream ofs("first.ppm");
		ofs << "P3" << endl << dimx << " " << dimy << endl << "255" << endl;

		//memset(image, 255, sizeof(image));
		for (auto j = 0u; j < dimy; ++j)
			for (auto i = 0u; i < dimx; ++i)

				ofs << (i % 256) << " " << (j % 256) << " " << ((i * j) % 256) << " ";       // red, green, blue
		//
		ofs.close();
	}
	
	return 0;
}
