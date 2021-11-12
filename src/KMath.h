#pragma once
#include <iostream>
namespace KT {
	
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

		vec3 operator*(const vec3 other) {
			return vec3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
		}

		vec3 operator+(const vec3 other) {
			return vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
		}

		vec3 operator-(const vec3 other) {
			return vec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
		}

		vec3 operator*(float s) {
			return vec3(m_x * s, m_y * s, m_z * s);
		}

		friend vec3 operator*(float s, vec3 other) {
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

		vec4 operator*(const vec4 other) {
			return vec4(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z, m_w * other.m_w);
		}

		vec4 operator+(const vec4 other) {
			return vec4(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w);
		}

		vec4 operator-(const vec4 other) {
			return vec4(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w * other.m_w);
		}

		vec4 operator*(float s) {
			return vec4(m_x * s, m_y * s, m_z * s, m_w * s);
		}
		friend vec4 operator*(float s, vec4 other) {
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

		vec3 eval(float t) {
			return m_o + m_d * t;
		}

		friend std::ostream& operator<<(std::ostream& out, ray r) {
			out << "Origin: " << r.m_o << " ";
			out << "Direction: " << r.m_d << "\n";
			return out;
		}
	};
}

