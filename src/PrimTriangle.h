// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param pShader Pointer to the shader to be applied for the prim
	 */
	CPrimTriangle(Vec3f a, Vec3f b, Vec3f c, std::shared_ptr<IShader> pShader)
		: CPrim(pShader)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		const Vec3f edge1 = m_b - m_a;
		const Vec3f edge2 = m_c - m_a;
		
		const Vec3f pvec = ray.dir.cross(edge2);
		
		const float det = edge1.dot(pvec);
		if (fabs(det) < Epsilon) return false;
		
		const float inv_det = 1.0f / det;
		
		const Vec3f tvec = ray.org - m_a;
		float lambda = tvec.dot(pvec);
		lambda *= inv_det;
		
		if (lambda < 0.0f || lambda > 1.0f) return false;
		
		const Vec3f qvec = tvec.cross(edge1);
		float mue = ray.dir.dot(qvec);
		mue *= inv_det;
		
		if (mue < 0.0f || mue + lambda > 1.0f) return false;
		
		float f = edge2.dot(qvec);
		f *= inv_det;
		if (ray.t <= f || f <  Epsilon  ) return false;
        ray.t = f;

        Vec3f p = ray.org + ray.t * ray.dir; ///hit point
        Vec3f c = p - m_a;
        float d00 = edge1.dot(edge1);
        float d01 = edge1.dot(edge2);
        float d11 = edge2.dot(edge2);
        float d20 = c.dot(edge1);
        float d21 = c.dot(edge2);
        float invDenom = 1.0f / (d00 * d11 - d01 * d01);
        
        
        ray.v = (d11 * d20 - d01 * d21) * invDenom;
		float w = (d00 * d21 - d01 * d20) * invDenom;
        ray.u = 1.0f - ray.v - w;
        
		ray.hit = this;
		return true;
	}

	virtual Vec3f getNormal(const Ray& ray) const override
	{
		const Vec3f edge1 = m_b - m_a;
		const Vec3f edge2 = m_c - m_a;
		Vec3f normal = normalize(edge1.cross(edge2));
		return normal;
	}
	
	virtual CBoundingBox calcBounds(void) const override
	{
		CBoundingBox res;
		res.extend(m_a);
		res.extend(m_b);
		res.extend(m_c);
		return res;
	}
	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
