#pragma once

#include "Shape.h"
#include <vector>
#include <cmath>

constexpr float SOLAR_RENDER_RADIUS = 1.5f;        // Engine units

// =========================
// Radius (km)
// =========================

constexpr float SUN_RADIUS = 695700.0f;
constexpr float MERCURY_RADIUS = 2439.7f;
constexpr float VENUS_RADIUS = 6051.8f;
constexpr float EARTH_RADIUS = 6371.0f;
constexpr float MOON_RADIUS = 1737.4f;
constexpr float MARS_RADIUS = 3389.5f;
constexpr float JUPITER_RADIUS = 69911.0f;
constexpr float SATURN_RADIUS = 58232.0f;
constexpr float URANUS_RADIUS = 25362.0f;
constexpr float NEPTUNE_RADIUS = 24622.0f;
constexpr float PLUTO_RADIUS = 1188.3f;


constexpr float RADIUS_SCALE =
SUN_RADIUS / SOLAR_RENDER_RADIUS;

// Helper
constexpr float ScaleRadius(float radiusKm)
{
	return radiusKm / RADIUS_SCALE;
}

struct Sphere : public Shape
{
protected:

	std::vector<float> m_Vertices;
	GLuint m_VertexCount = 0;

public:

	Sphere(float radius,
		uint32_t stacks = 32,
		uint32_t sectors = 64)
	{
		constexpr float PI = 3.14159265359f;

		std::vector<float> temp;

		for (uint32_t i = 0; i <= stacks; i++)
		{
			float stackAngle = PI / 2.f - i * PI / stacks;

			float xy = radius * cosf(stackAngle);
			float z = radius * sinf(stackAngle);

			for (uint32_t j = 0; j <= sectors; j++)
			{
				float sectorAngle = j * 2.f * PI / sectors;

				float x = xy * cosf(sectorAngle);
				float y = xy * sinf(sectorAngle);

				float u = (float)j / sectors;
				float v = (float)i / stacks;

				temp.push_back(x);
				temp.push_back(y);
				temp.push_back(z);

				temp.push_back(u);
				temp.push_back(v);
			}
		}

		for (uint32_t i = 0; i < stacks; i++)
		{
			uint32_t k1 = i * (sectors + 1);
			uint32_t k2 = k1 + sectors + 1;

			for (uint32_t j = 0; j < sectors; j++, k1++, k2++)
			{
				if (i != 0)
				{
					for (int idx : { (int)k1, (int)k2, (int)k1 + 1 })
						for (int c = 0; c < 5; c++)
							m_Vertices.push_back(temp[idx * 5 + c]);
				}

				if (i != stacks - 1)
				{
					for (int idx : { (int)k1 + 1, (int)k2, (int)k2 + 1 })
						for (int c = 0; c < 5; c++)
							m_Vertices.push_back(temp[idx * 5 + c]);
				}
			}
		}

		m_VertexCount = m_Vertices.size() / 5;
	}

	inline size_t GetSize() override
	{
		return m_Vertices.size() * sizeof(float);
	}

	inline float* GetVertices() override
	{
		return m_Vertices.data();
	}

	inline GLuint GetVertexCount() const override
	{
		return m_VertexCount;
	}

	inline GLuint PositionIndex() const { return 0; }
	inline GLuint PositionSize() const { return 3; }
	inline size_t PositionStride() const { return 5 * sizeof(float); }
	inline size_t PositionOffset() const { return 0; }

	inline GLuint TexCoordIndex() const { return 1; }
	inline GLuint TexCoordSize() const { return 2; }
	inline size_t TexCoordStride() const { return 5 * sizeof(float); }
	inline size_t TexCoordOffset() const { return 3 * sizeof(float); }
};

struct Ring : public Shape
{
protected:

	std::vector<float> m_Vertices;
	GLuint m_VertexCount = 0;

public:

	Ring(float innerRadius,
		float outerRadius,
		uint32_t segments = 128)
	{
		constexpr float PI = 3.14159265359f;

		for (uint32_t i = 0; i < segments; i++)
		{
			float theta1 = (2.0f * PI * i) / segments;
			float theta2 = (2.0f * PI * (i + 1)) / segments;

			float c1 = cosf(theta1);
			float s1 = sinf(theta1);

			float c2 = cosf(theta2);
			float s2 = sinf(theta2);

			float verts[] =
			{
				// Triangle 1

				innerRadius * c1, 0.f, innerRadius * s1, 0.f, 0.f,
				outerRadius * c1, 0.f, outerRadius * s1, 1.f, 0.f,
				outerRadius * c2, 0.f, outerRadius * s2, 1.f, 1.f,

				// Triangle 2

				innerRadius * c1, 0.f, innerRadius * s1, 0.f, 0.f,
				outerRadius * c2, 0.f, outerRadius * s2, 1.f, 1.f,
				innerRadius * c2, 0.f, innerRadius * s2, 0.f, 1.f
			};

			m_Vertices.insert(
				m_Vertices.end(),
				verts,
				verts + sizeof(verts) / sizeof(float)
			);
		}

		m_VertexCount = m_Vertices.size() / 5;
	}

	inline size_t GetSize() override
	{
		return m_Vertices.size() * sizeof(float);
	}

	inline float* GetVertices() override
	{
		return m_Vertices.data();
	}

	inline GLuint GetVertexCount() const override
	{
		return m_VertexCount;
	}

	inline GLuint PositionIndex() const { return 0; }
	inline GLuint PositionSize() const { return 3; }
	inline size_t PositionStride() const { return 5 * sizeof(float); }
	inline size_t PositionOffset() const { return 0; }

	inline GLuint TexCoordIndex() const { return 1; }
	inline GLuint TexCoordSize() const { return 2; }
	inline size_t TexCoordStride() const { return 5 * sizeof(float); }
	inline size_t TexCoordOffset() const { return 3 * sizeof(float); }
};

struct Asteroid : public Shape
{
protected:

	std::vector<float> m_Vertices;
	GLuint m_VertexCount = 0;

public:

	Asteroid(
		float radius = 0.6f,
		float roughness = 0.18f,
		uint32_t stacks = 20,
		uint32_t sectors = 40)
	{
		constexpr float PI = 3.14159265359f;

		std::vector<float> temp;

		srand(42);

		for (uint32_t i = 0; i <= stacks; i++)
		{
			float stackAngle = PI / 2.f - i * PI / stacks;

			for (uint32_t j = 0; j <= sectors; j++)
			{
				float sectorAngle = 2.f * PI * j / sectors;

				float noise =
					((rand() % 1000) / 1000.0f - 0.5f) *
					roughness;

				float r = radius + noise;

				float x = r * cosf(stackAngle) * cosf(sectorAngle);
				float y = r * sinf(stackAngle);
				float z = r * cosf(stackAngle) * sinf(sectorAngle);

				float u = (float)j / sectors;
				float v = (float)i / stacks;

				temp.push_back(x);
				temp.push_back(y);
				temp.push_back(z);
				temp.push_back(u);
				temp.push_back(v);
			}
		}

		for (uint32_t i = 0; i < stacks; i++)
		{
			uint32_t k1 = i * (sectors + 1);
			uint32_t k2 = k1 + sectors + 1;

			for (uint32_t j = 0; j < sectors; j++, k1++, k2++)
			{
				if (i != 0)
				{
					for (int idx : { (int)k1, (int)k2, (int)k1 + 1 })
						for (int c = 0; c < 5; c++)
							m_Vertices.push_back(temp[idx * 5 + c]);
				}

				if (i != stacks - 1)
				{
					for (int idx : { (int)k1 + 1, (int)k2, (int)k2 + 1 })
						for (int c = 0; c < 5; c++)
							m_Vertices.push_back(temp[idx * 5 + c]);
				}
			}
		}

		m_VertexCount = m_Vertices.size() / 5;
	}

	inline size_t GetSize() override
	{
		return m_Vertices.size() * sizeof(float);
	}

	inline float* GetVertices() override
	{
		return m_Vertices.data();
	}

	inline GLuint GetVertexCount() const override
	{
		return m_VertexCount;
	}

	inline GLuint PositionIndex() const { return 0; }
	inline GLuint PositionSize() const { return 3; }
	inline size_t PositionStride() const { return 5 * sizeof(float); }
	inline size_t PositionOffset() const { return 0; }

	inline GLuint TexCoordIndex() const { return 1; }
	inline GLuint TexCoordSize() const { return 2; }
	inline size_t TexCoordStride() const { return 5 * sizeof(float); }
	inline size_t TexCoordOffset() const { return 3 * sizeof(float); }
};

struct Sun : public Sphere
{
	Sun()
		: Sphere(ScaleRadius(695700.0f))
	{
	}
};

struct Mercury : public Sphere
{
	Mercury()
		: Sphere(ScaleRadius(2439.7f))
	{
	}
};

struct Venus : public Sphere
{
	Venus()
		: Sphere(ScaleRadius(6051.8f))
	{
	}
};

struct Earth : public Sphere
{
	Earth()
		: Sphere(ScaleRadius(6371.0f))
	{
	}
};

struct Moon : public Sphere
{
	Moon()
		: Sphere(ScaleRadius(1737.4f))
	{
	}
};

struct Mars : public Sphere
{
	Mars()
		: Sphere(ScaleRadius(3389.5f))
	{
	}
};

struct Jupiter : public Sphere
{
	Jupiter()
		: Sphere(ScaleRadius(69911.0f))
	{
	}
};

struct Saturn : public Sphere
{
	Saturn()
		: Sphere(ScaleRadius(58232.0f))
	{
	}
};

struct SaturnRing : public Ring
{
	SaturnRing()
		: Ring(
			ScaleRadius(117000.0f),
			ScaleRadius(180000.0f)
		)
	{
	}
};

struct Uranus : public Sphere
{
	Uranus()
		: Sphere(ScaleRadius(25362.0f))
	{
	}
};

struct UranusRing : public Ring
{
	UranusRing()
		: Ring(
			ScaleRadius(51000.0f),
			ScaleRadius(98000.0f)
		)
	{
	}
};

struct Neptune : public Sphere
{
	Neptune()
		: Sphere(ScaleRadius(24622.0f))
	{
	}
};

struct Pluto : public Sphere
{
	Pluto()
		: Sphere(ScaleRadius(1188.3f))
	{
	}
};

