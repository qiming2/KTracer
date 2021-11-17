#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "KLib.h"
#include "util.h"

using namespace KT;
using namespace std;

const char* welcomeSen = "This is a simple ray tracer developed from scratch";
const static int Height = 600;
const static int Width = 600;
const static float near = 1.0f;
const static float L = -1.0f;
const static float R = 1.0f;
const static float B = -1.0f;
const static float T = 1.0f;
int main() {
	println("Welcome to KTracer Engine");
	println(welcomeSen);

	// Simple math library
	/*KT::vec3 temp = 3 * vec3(1.0, 2.0, 3);
	KT::vec4 temp1 = KT::vec4(1.0, 2.0, 3, 2.3) * KT::vec4(1.3, 2.5, 4.0, 2);
	KT::ray r;
	KT::mat4 temp3;
	println(temp3);
	println(temp, temp1, r);*/
	
	// set seed based on time       
	srand(time(NULL));
	// TODO:
	// 0. Camera
	vec3 cam_pos(0.0f, 0.0f, 1.0f);
	KT::Camera c(Width, Height);
	c.setPos(cam_pos);
	// 1. Generating rays (Only implementing Perspective, orthogonal would be easy if finished perspective)
	vec3 background(0.8f, 0.3f, 0.0f);
	size_t index = 0;
	float r, g, b;
	float* image = new float[Height * Width * 3];
	for (size_t y = 0; y < Height; ++y) {
		for (size_t x = 0; x < Width; ++x) {
			index = y * Width * 3 + x * 3;
			image[index] = background.m_x;
			image[index + 1] = background.m_y;
			image[index + 2] = background.m_z;
		}
	}
	// ray.m_o = cam pos
	// ray.m_d = u* cam u + v * cam v + -w * cam w
	// w is the distance from cam pos to the center of near plane
	KT::ray cur_ray;
	cur_ray.m_o = c.m_frame.getPos();

	vec3 u = c.m_frame.getU();
	vec3 v = c.m_frame.getV();
	vec3 w = c.m_frame.getW();
	
	float u_coord;
	float v_coord;

	//Test first ray
	
	
	// 2. Generating objects (sphere as the most simplistic object to do the intersection test)
	// Hard code a sphere for intersection test
	
	KT::Sphere s;
	s.m_o = vec3(0.0f, 0.0f, 0.0f);
	s.m_r = 0.5f;
	const static vec3 color = vec3(rand() % 100 / 100.0f, 0.0f, rand() % 100 / 100.0f);
	
	static size_t cnt = 0;
	Record record;
	vec3 hitPoint;

	// Add a directional light
	static vec3 lightDir = vec3(0.5f, -0.5f, -0.5f);
	lightDir.normalize();
	lightDir = -lightDir;
	const static vec3 lightColor = vec3(0.7f, 0.7f, 0.7f);
	const static vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);
	float dotH;
	vec3 output_color;
	for (size_t y = 0; y < Height; ++y) {
		for (size_t x = 0; x < Width; ++x) {
			
			u_coord = L + ((R - L) * (float)(0.5 +  x)) / Width;
			v_coord = T - ((T - B) * (float)(0.5 +  y)) / Height;
			cur_ray.m_d = -near * w + u_coord * u + v_coord * v;
			record = s.intersection(cur_ray);
			if (record.m_surf) {
				// 3. Shading (flat shading without light first -> phong shading -> pbr)
				//(hitPoint = cur_ray.eval(record.m_t)).normalize();
				//print("Normal: ", record.m_normal, " LightDir: ", lightDir, " dot: ", record.m_normal.dot(lightDir));
				dotH = max(record.m_normal.dot(lightDir), 0.0f);
				output_color = ambientColor * color;
				output_color += dotH * color * lightColor;

				// Note: y * Width * 3 since we have width * 3 floats in a row!
				index = y * Width * 3 + x * 3;
				image[index] =	   output_color.m_x;
				image[index + 1] = output_color.m_y;
				image[index + 2] = output_color.m_z;
			}
		}
	}

	

	
	
	// 4. output to a ppm p3 version image for viewing

	// output a simple ppm image
	static bool output = true;
	if (output) {
		const int dimx = Width, dimy = Height;
		ofstream ofs("trace.ppm");
		ofs << "P3" << endl << dimx << " " << dimy << endl << "255" << endl;

		for (size_t y = 0; y < Height; ++y) {
			for (size_t x = 0; x < Width; ++x) {
				// Note: Order matters a lot!!
				// Since we are tracing rays from left to right and top to bottom
				// we need to store in the same order in ppm, otherwise the image might
				// flip upside down
				index = y * Width * 3 + x * 3;
				r = image[index] * 255.0f;
				g = image[index + 1] * 255.0f;
				b = image[index + 2] * 255.0f;
				ofs << r  << " " << g << " " << b << " ";
			}
		}
		ofs.close();
		
	}
	delete[] image;
	
	return 0;
}

