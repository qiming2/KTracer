#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "util.h"
#define EPSILON 0.001f

namespace KT {
	
	class Record;
	class Surface;
	struct vec3
	{
		union {
			struct {
				float m_x;
				float m_y;
				float m_z;
			};
			float data[3];
		};
		vec3():m_x(0.0f), m_y(0.0f), m_z(0.0f) {}
		vec3(float x, float y, float z):
			m_x(x), m_y(y), m_z(z)
		{
		}

		float dot(const vec3& other) const {
			return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
		}

		void normalize() {
			float length = len();
			m_x /= length;
			m_y /= length;
			m_z /= length;
		}

		float len() const {
			return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z);
		}
		vec3 operator-() const {
			return vec3(-m_x, -m_y, -m_z);
		}
		vec3 operator*(const vec3& other) const {
			return vec3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
		}

		vec3 operator+(const vec3& other) const {
			return vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
		}

		void operator+=(const vec3& other) {
			m_x += other.m_x;
			m_y += other.m_y;
			m_z += other.m_z;
		}

		vec3 operator-(const vec3& other) const {
			return vec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
		}
		
		vec3 operator*(float s) const {
			return vec3(m_x * s, m_y * s, m_z * s);
		}

		friend vec3 normalize(const vec3& v) {
			vec3 ret = v;
			ret.normalize();
			return ret;
		}

		friend vec3 operator*(float s, const vec3& other) {
			return vec3(other.m_x * s, other.m_y * s, other.m_z * s);
		}

		friend std::ostream& operator<<(std::ostream& out, const vec3& data) {
			out << data.m_x << " " << data.m_y << " " << data.m_z;
			return out;
		}
	};
	

	struct vec4
	{
		union {
			struct {
				float m_x;
				float m_y;
				float m_z;
				float m_w;
			};
			float data[4];
		};
		vec4() :m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(0.0f) {}
		vec4(float x, float y, float z, float w) :
			m_x(x), m_y(y), m_z(z), m_w(w)
		{
		}

		float dot(const vec4& other) const {
			return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
		}

		void normalize() {
			float length = len();
			m_x /= length;
			m_y /= length;
			m_z /= length;
			m_w /= length;
		}

		friend vec4 normalize(const vec4& v) {
			vec4 ret = v;
			ret.normalize();
			return ret;
		}

		float len() const {
			return sqrtf(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
		}

		vec4 operator-() const {
			return vec4(-m_x, -m_y, -m_z, -m_w);
		}

		vec4 operator*(const vec4& other) const {
			return vec4(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z, m_w * other.m_w);
		}

		vec4 operator+(const vec4& other) const {
			return vec4(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w);
		}

		void operator+=(const vec4& other) {
			m_x += other.m_x;
			m_y += other.m_y;
			m_z += other.m_z;
			m_w += other.m_w;
		}

		vec4 operator-(const vec4& other) const {
			return vec4(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w * other.m_w);
		}

		vec4 operator*(float s) const {
			return vec4(m_x * s, m_y * s, m_z * s, m_w * s);
		}
		friend vec4 operator*(float s, const vec4& other) {
			return vec4(other.m_x * s, other.m_y * s, other.m_z * s, other.m_w * s);
		}
		friend std::ostream& operator<<(std::ostream& out, const vec4& data) {
			out << data.m_x << " " << data.m_y << " " << data.m_z << " " << data.m_w;
			return out;
		}
	};


	struct ray {
		vec3 m_o; // origin
		vec3 m_d; // direction
		ray() {}
		ray(vec3 o, vec3 d):
			m_o(o), m_d(d)
		{

		}

		vec3 eval(float t) const {
			return m_o + m_d * t;
		}

		friend std::ostream& operator<<(std::ostream& out, const ray& r) {
			out << "Origin: " << r.m_o << " ";
			out << "Direction: " << r.m_d;
			return out;
		}
	};

	struct mat4 {
		union {
			float m[4][4];
			float m16[16];
		};

		mat4() {
			clear();
			identity();
		}

		mat4(const float& m0, const float& m1, const float& m2, const float& m3,
			 const float& m4, const float& m5, const float& m6, const float& m7,
			 const float& m8, const float& m9, const float& m10, const float& m11,
			 const float& m12,const float& m13, const float& m14, const float& m15) {
			m[0][0] = m0; m[0][1] = m4; m[0][2] = m8; m[0][3] = m12;
			m[1][0] = m1; m[0][1] = m5; m[0][2] = m9; m[0][3] = m13;
			m[2][0] = m2; m[0][1] = m6; m[0][2] = m10; m[0][3] = m14;
			m[3][0] = m3; m[0][1] = m7; m[0][2] = m11; m[0][3] = m15;
		}
		
		
		mat4(const vec3& u, const vec3& v, const vec3& w, const vec3& pos) {
			setU(u); setV(v); setW(w); setPos(pos);
		}

		void setU(const vec3& u) {
			m[0][0] = u.m_x;
			m[1][0] = u.m_y;
			m[2][0] = u.m_z;
		}
		
		vec3 getU() const {
			return vec3(m[0][0], m[1][0], m[2][0]);
		}
		vec3 getV() const {
			return vec3(m[0][1], m[1][1], m[2][1]);
		}
		vec3 getW() const {
			return vec3(m[0][2], m[1][2], m[2][2]);
		}
		vec3 getPos() const {
			return vec3(m[0][3], m[1][3], m[2][3]);
		}
		void setV(const vec3& v) {
			m[0][1] = v.m_x;
			m[1][1] = v.m_y;
			m[2][1] = v.m_z;
		}

		void setW(const vec3& w) {
			m[0][2] = w.m_x;
			m[1][2] = w.m_y;
			m[2][2] = w.m_z;
		}

		void setPos(const vec3& pos) {
			m[0][3] = pos.m_x;
			m[1][3] = pos.m_y;
			m[2][3] = pos.m_z;
		}

		void identity() {
			clear();
			m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
		}

		void clear() {
			memset((void*)m, 0, sizeof(m));
		}

		friend std::ostream& operator<<(std::ostream& out, const mat4& m) {
			out << m.m[0][0] << " " << m.m[0][1] << " " << m.m[0][2] << " " << m.m[0][3] << "\n"
				<< m.m[1][0] << " " << m.m[1][1] << " " << m.m[1][2] << " " << m.m[1][3] << "\n"
				<< m.m[2][0] << " " << m.m[2][1] << " " << m.m[2][2] << " " << m.m[2][3] << "\n"
				<< m.m[3][0] << " " << m.m[3][1] << " " << m.m[3][2] << " " << m.m[3][3];
			return out;
		}
	};

	class Camera {
	public:
		mat4 m_frame;
		float m_width;
		float m_height;
		Camera(const mat4& frame, float width, float height):
			m_frame(frame), m_width(width), m_height(height)
		{
			
		}

		Camera(float width, float height):
			m_width(width), m_height(height)
		{
				
		}

		void setPos(const vec3& pos) {
			m_frame.setPos(pos);
		}

		friend std::ostream& operator<<(std::ostream& out, const Camera& camera) {
			out << camera.m_frame << "Width: " << camera.m_width << " Height: " << camera.m_height;
			return out;
		}
	};

	class Record {
	public:
		vec3 m_color;
		vec3 m_normal;
		const Surface* m_surf = nullptr;
		float m_t = std::numeric_limits<float>::infinity();
		Record() {};
		Record(Surface* surf, float t) :m_surf(surf), m_t(t) {};
		Record(Surface* surf, const vec3& norm, float t) :m_surf(surf), m_normal(norm), m_t(t) {};
	};

	class Surface {
	public:
		virtual Record intersection(const ray& r) const { return {}; };
	};
	
	class Sphere : public Surface {
	public:
		vec3 m_o; // origin
		float m_r;

		virtual Record intersection(const ray& r) const override {
			Record record;
			vec3 e_minus_c = r.m_o - m_o;
			float d_dot_d = r.m_d.dot(r.m_d);
			float e_dot_d = r.m_d.dot(e_minus_c);
			float discrim = e_dot_d * e_dot_d - d_dot_d * ((e_minus_c.dot(e_minus_c) - m_r * m_r));
			if (discrim < EPSILON) {
				return record;
			}
			discrim = sqrtf(discrim);
			vec3 point;
			float t1 = (-e_dot_d - discrim) / d_dot_d;
			if (t1 > EPSILON) {
				record.m_surf = this;
				record.m_t = t1;
				
				point = r.eval(t1);
				
				record.m_normal = point - m_o;
				record.m_normal.normalize();
				//println(record.m_normal);
				return record;
			}

			float t2 = (-e_dot_d + discrim) / d_dot_d;
			if (t2 > EPSILON) {
				record.m_surf = this;
				record.m_t = t2;

				point = r.eval(t2);

				record.m_normal = point - m_o;
				record.m_normal.normalize();
				return record;
			}

			return record;
		}

		friend std::ostream& operator<<(std::ostream& out, const Sphere& s) {
			out << "Origin: " << s.m_o << " Radius: " << s.m_r;
			return out;
		}
	};
	
	// Surface Manager: Contains all necessary object data necessary for doing
	// intersection test
	// Singletone class
	class SurfaceManager {
		
	public:
		
		static SurfaceManager& getInstance() {
			static SurfaceManager instance;
			return instance;
		}
		void Add(Surface& surf) {
			surfaces.push_back(&surf);
		}

		Record intersection(const ray& r, size_t level, size_t max_level, const Camera& c) {
			
			Record ret;
			if (level == max_level) return ret;
			
			
			Record record;

			for (size_t i = 0; i < surfaces.size(); ++i) {
				record = surfaces[i]->intersection(r);
				if (record.m_surf && ret.m_t > record.m_t - EPSILON) {
					ret = record;
				}
			}
			// Add a directional light
			const static vec3 color = vec3(rand() % 100 / 100.0f / 2.0f + 0.5f, 0.3f, rand() % 100 / 100.0f);
			const static vec3 lightDir = normalize(vec3(0.5f, -0.5f, -0.5f));
			const static vec3 lightColor = vec3(0.7f, 0.7f, 0.7f);
			const static vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);
			const static float shinness = 32.0f;
			vec3 output_color;
			vec3 hitPoint;
			float dotH;
			vec3 halfDir;
			float dotHN;
			if (ret.m_surf) {
				// 3. Shading (flat shading without light first -> phong shading -> pbr)
				hitPoint = r.eval(ret.m_t);
				//print(hitPoint);
				//print("Normal: ", record.m_normal, " LightDir: ", lightDir, " dot: ", record.m_normal.dot(lightDir));
				dotH = std::max(ret.m_normal.dot(-lightDir), 0.0f);
				// phong shading
				// ambient + diffuse + specular
				output_color = ambientColor * color;
				output_color += dotH * color * lightColor;
				(halfDir = (-lightDir) + (c.m_frame.getPos() - normalize(hitPoint))).normalize();
				dotHN = std::max(halfDir.dot(ret.m_normal), 0.0f);
				output_color += std::pow(dotHN, shinness) * lightColor * color;
				ret.m_color = output_color;
				
				// If hit something, we do a reflection
				ray reflect_ray;
				reflect_ray.m_o = hitPoint;
				reflect_ray.m_d = r.m_d + 2 * (-r.m_d.dot(ret.m_normal)) * ret.m_normal;
				ret.m_color += intersection(reflect_ray, level + 1, max_level, c).m_color;
			}
			
			return ret;
		}
		void operator=(const SurfaceManager&) = delete;
		SurfaceManager(const SurfaceManager&) = delete;
		
	private:
		// static SurfaceManager* instance;
		std::vector<Surface*> surfaces;
		SurfaceManager() {}
	};
}