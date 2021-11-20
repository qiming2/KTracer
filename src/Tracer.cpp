#include "Tracer.h"

KT::Record::Record(Surface* surf, const vec3& norm, float t) :m_surf(surf), m_normal(norm), m_t(t)
{

}

KT::Record::Record()
{

}

KT::Record::Record(Surface* surf, float t) : m_surf(surf), m_t(t)
{

}

KT::Record KT::Sphere::intersection(const ray& r) const
{
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

std::ostream& KT::operator<<(std::ostream& out, const KT::Sphere& s)
{
	out << "Origin: " << s.m_o << " Radius: " << s.m_r;
	return out;
}

KT::SurfaceManager& KT::SurfaceManager::getInstance()
{
	static SurfaceManager instance;
	return instance;
}

void KT::SurfaceManager::Add(Surface& surf)
{
	surfaces.push_back(&surf);
}

extern KT::vec3 globalDir;
KT::Record KT::SurfaceManager::intersection(const ray& r, size_t level, size_t max_level, const Camera& c)
{
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
	const static vec3 color = vec3(rand() % 100 / 100.0f / 2.0f + 0.5f, 0.7f, rand() % 100 / 100.0f);
	//const static vec3 lightDir = normalize(vec3(-0.5f, 0.3f, -0.5f));
	const static vec3 lightDir = normalize(globalDir);
	const static vec3 lightColor = vec3(0.7f, 0.7f, 0.7f);
	const static vec3 ambientColor = vec3(0.2f, 0.2f, 0.2f);
	const static float shinness = 32.0f;
	vec3 output_color;
	vec3 hitPoint;
	vec3 halfDir;
	float dotH;
	float dotHN;
	float shadow;
	if (ret.m_surf) {
		// 3. Shading (flat shading without light first -> phong shading -> pbr)
		hitPoint = r.eval(ret.m_t);

		// Shadow Casting
		
		shadow = castShadow(hitPoint, lightDir);
		dotH = std::max(ret.m_normal.dot(-lightDir), 0.0f);

		// phong shading
		// ambient + diffuse + specular
		(halfDir = (-lightDir) + (c.m_frame.getPos() - normalize(hitPoint))).normalize();
		dotHN = std::max(halfDir.dot(ret.m_normal), 0.0f);
		output_color = ambientColor * color;
		output_color += (dotH * color * lightColor + std::pow(dotHN, shinness) * lightColor * color) * (1.0f - shadow);
		
		ret.m_color = output_color;
		// If hit something, we do a reflection
		ray reflect_ray;
		reflect_ray.m_o = hitPoint;
		reflect_ray.m_d = r.m_d + 2 * (-r.m_d.dot(ret.m_normal)) * ret.m_normal;
		// TODO Store some sort of material
		ret.m_color += 0.3 * intersection(reflect_ray, level + 1, max_level, c).m_color;
	}

	return ret;
}

// TODO: Change lightDir to maybe light info
float KT::SurfaceManager::castShadow(const vec3& point, const vec3& lightDir) const
{
	const ray shadowRay(point, normalize(-lightDir));
	for (size_t i = 0; i < surfaces.size(); ++i) {
		if (surfaces[i]->intersection(shadowRay).m_surf) {
			//print("enter?");
			return 1.0f;
		}
	}
	return 0.0f;
}

KT::SurfaceManager::SurfaceManager()
{

}
