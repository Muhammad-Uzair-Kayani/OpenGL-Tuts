#pragma once
#include "Resources/Model/Model.h"
#include "Resources/Shapes/Stars.h"
#include <vector>

constexpr float SOLAR_DISTANCE_SCALE = 500000000.0f;
constexpr float MOON_DISTANCE_SCALE = 13000000.0f;
constexpr float SUN_RENDER_RADIUS = 1.5f;
constexpr float SAFE_MARGIN = 0.2f;

// =========================
// Distance (km)
// =========================

// From the Sun
constexpr float MERCURY_DISTANCE = 57909227.0f;
constexpr float VENUS_DISTANCE = 108209475.0f;
constexpr float EARTH_DISTANCE = 149597870.0f;
constexpr float MARS_DISTANCE = 227943824.0f;
constexpr float JUPITER_DISTANCE = 778340821.0f;
constexpr float SATURN_DISTANCE = 1426666422.0f;
constexpr float URANUS_DISTANCE = 2870658186.0f;
constexpr float NEPTUNE_DISTANCE = 4498396441.0f;
constexpr float PLUTO_DISTANCE = 5906376272.0f;

// Relative to Earth
constexpr float MOON_DISTANCE = 384400.0f;


// =========================
// Ring Radius (km)
// =========================

// Saturn
constexpr float SATURN_RING_INNER_RADIUS = 117580.0f;
constexpr float SATURN_RING_OUTER_RADIUS = 140220.0f;

// Uranus
constexpr float URANUS_RING_INNER_RADIUS = 41837.0f;
constexpr float URANUS_RING_OUTER_RADIUS = 51149.0f;

// =========================
// Axial Tilt (degrees)
// =========================

constexpr float SUN_AXIAL_TILT = 7.25f;
constexpr float MERCURY_AXIAL_TILT = 0.034f;
constexpr float VENUS_AXIAL_TILT = 177.4f;
constexpr float EARTH_AXIAL_TILT = 23.44f;
constexpr float MOON_AXIAL_TILT = 6.68f;
constexpr float MARS_AXIAL_TILT = 25.19f;
constexpr float JUPITER_AXIAL_TILT = 3.13f;
constexpr float SATURN_AXIAL_TILT = 26.73f;
constexpr float URANUS_AXIAL_TILT = 97.77f;
constexpr float NEPTUNE_AXIAL_TILT = 28.32f;
constexpr float PLUTO_AXIAL_TILT = 122.53f;

// =========================
// Rotation Period (Earth days)
// Negative = retrograde
// =========================

constexpr float SUN_ROTATION_PERIOD = 25.38f;
constexpr float MERCURY_ROTATION_PERIOD = 58.646f;
constexpr float VENUS_ROTATION_PERIOD = -243.025f;
constexpr float EARTH_ROTATION_PERIOD = 1.0f;
constexpr float MOON_ROTATION_PERIOD = 27.32f;
constexpr float MARS_ROTATION_PERIOD = 1.026f;
constexpr float JUPITER_ROTATION_PERIOD = 0.4135f;
constexpr float SATURN_ROTATION_PERIOD = 0.4396f;
constexpr float URANUS_ROTATION_PERIOD = -0.71833f;
constexpr float NEPTUNE_ROTATION_PERIOD = 0.6713f;
constexpr float PLUTO_ROTATION_PERIOD = -6.387f;


constexpr float ScaleDistance(float distanceKm)
{
	return SUN_RENDER_RADIUS + SAFE_MARGIN + (distanceKm / SOLAR_DISTANCE_SCALE);
}


inline float g_SolarTime = 0.0f;
inline float g_TimeScale = 30.0f; // 1 real second = n simulated days
inline std::tuple<float, float, float> m_EarthPos;

void OnSolarSystemUpdate(float deltaTime)
{
	g_SolarTime += deltaTime * g_TimeScale;
}

constexpr float PI = 3.14159265359f;

constexpr float DegreesToRadians(float degrees)
{
	return degrees * (PI / 180.0f);
}

float ComputeSpinAngle(float rotationPeriod)
{
	if (rotationPeriod == 0.0f) return 0.0f;
	return (g_SolarTime / rotationPeriod) * (2.0f * PI);
}

std::vector<std::tuple<float, float, float>> UpdateOrbitPosition(
	float orbitalRadius,
	float orbitalPeriod,
	float axialTilt,
	float rotationPeriod)
{
	float angle =
		(g_SolarTime / orbitalPeriod) *
		(2.0f * PI);

	float x = orbitalRadius * cosf(angle);
	float y = 0.0f;
	float z = orbitalRadius * sinf(angle);

	float spinAngle = ComputeSpinAngle(rotationPeriod);

	return {
		{ x, y, z },
		{ DegreesToRadians(axialTilt), spinAngle, 0.0f }
	};
}

std::vector<std::tuple<float, float, float>> UpdateSunRotation()
{
	float spinAngle = ComputeSpinAngle(SUN_ROTATION_PERIOD);

	return {
		{ 0.0f, 0.0f, 0.0f },
		{ DegreesToRadians(SUN_AXIAL_TILT), spinAngle, 0.0f }
	};
}

std::vector<std::tuple<float, float, float>> UpdateMercuryPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(MERCURY_DISTANCE),
		88.0f,
		MERCURY_AXIAL_TILT,
		MERCURY_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateVenusPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(VENUS_DISTANCE),
		224.7f,
		VENUS_AXIAL_TILT,
		VENUS_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateEarthPosition()
{
	auto result = UpdateOrbitPosition(
		ScaleDistance(EARTH_DISTANCE),
		365.25f,
		EARTH_AXIAL_TILT,
		EARTH_ROTATION_PERIOD
	);

	m_EarthPos = result[0];

	return result;
}


std::vector<std::tuple<float, float, float>> UpdateMarsPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(MARS_DISTANCE),
		686.98f,
		MARS_AXIAL_TILT,
		MARS_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateJupiterPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(JUPITER_DISTANCE),
		4332.59f,
		JUPITER_AXIAL_TILT,
		JUPITER_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateSaturnPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(SATURN_DISTANCE),
		10759.22f,
		SATURN_AXIAL_TILT,
		SATURN_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateUranusPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(URANUS_DISTANCE),
		30688.5f,
		URANUS_AXIAL_TILT,
		URANUS_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateNeptunePosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(NEPTUNE_DISTANCE),
		60182.0f,
		NEPTUNE_AXIAL_TILT,
		NEPTUNE_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdatePlutoPosition()
{
	return UpdateOrbitPosition(
		ScaleDistance(PLUTO_DISTANCE),
		90560.0f,
		PLUTO_AXIAL_TILT,
		PLUTO_ROTATION_PERIOD
	);
}

std::vector<std::tuple<float, float, float>> UpdateMoonPosition()
{
	auto [earthX, earthY, earthZ] = m_EarthPos;

	float angle =
		(g_SolarTime / 27.32f) *
		(2.0f * PI);

	float moonOrbit = MOON_DISTANCE / MOON_DISTANCE_SCALE;

	float x = earthX + moonOrbit * cosf(angle);
	float y = earthY;
	float z = earthZ + moonOrbit * sinf(angle);

	float spinAngle = ComputeSpinAngle(MOON_ROTATION_PERIOD);

	return {
		{ x, y, z },
		{ DegreesToRadians(MOON_AXIAL_TILT), spinAngle, 0.0f }
	};
}

Model* CreateSun()
{
	Sun* shape = new Sun();

	Model* model = new Model(
		shape,
		glm::vec3(0.f, 0.f, 0.f),
		"Sun",
		UpdateSunRotation
	);

	model->BindShader(
		"src/Resources/Shaders/SunVertex.txt",
		"src/Resources/Shaders/SunFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/sun.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateMercury()
{
	Mercury* shape = new Mercury();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(MERCURY_DISTANCE), 0.0f, 0.0f),
		"Mercury",
		UpdateMercuryPosition
	);

	model->BindShader(
		"src/Resources/Shaders/MercuryVertex.txt",
		"src/Resources/Shaders/MercuryFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/mercury.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateVenus()
{
	Venus* shape = new Venus();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(VENUS_DISTANCE), 0.0f, 0.0f),
		"Venus",
		UpdateVenusPosition
	);

	model->BindShader(
		"src/Resources/Shaders/VenusVertex.txt",
		"src/Resources/Shaders/VenusFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/venus.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateEarth()
{
	Earth* shape = new Earth();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(EARTH_DISTANCE), 0.0f, 0.0f),
		"Earth",
		UpdateEarthPosition
	);

	model->BindShader(
		"src/Resources/Shaders/EarthVertex.txt",
		"src/Resources/Shaders/EarthFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/earth.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateMoon()
{
	Moon* shape = new Moon();

	float moonInitialX = ScaleDistance(EARTH_DISTANCE) + (MOON_DISTANCE / MOON_DISTANCE_SCALE);

	Model* model = new Model(
		shape,
		glm::vec3(moonInitialX, 0.0f, 0.0f),
		"Moon",
		UpdateMoonPosition
	);

	model->BindShader(
		"src/Resources/Shaders/MoonVertex.txt",
		"src/Resources/Shaders/MoonFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/moon.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateMars()
{
	Mars* shape = new Mars();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(MARS_DISTANCE), 0.0f, 0.0f),
		"Mars",
		UpdateMarsPosition
	);

	model->BindShader(
		"src/Resources/Shaders/MarsVertex.txt",
		"src/Resources/Shaders/MarsFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/mars.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateJupiter()
{
	Jupiter* shape = new Jupiter();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(JUPITER_DISTANCE), 0.0f, 0.0f),
		"Jupiter",
		UpdateJupiterPosition
	);

	model->BindShader(
		"src/Resources/Shaders/JupiterVertex.txt",
		"src/Resources/Shaders/JupiterFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/jupiter.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateSaturn()
{
	Saturn* shape = new Saturn();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(SATURN_DISTANCE), 0.0f, 0.0f),
		"Saturn",
		UpdateSaturnPosition
	);

	model->BindShader(
		"src/Resources/Shaders/SaturnVertex.txt",
		"src/Resources/Shaders/SaturnFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/saturn.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateSaturnRing()
{
	SaturnRing* shape = new SaturnRing();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(SATURN_DISTANCE), 0.0f, 0.0f),
		"SaturnRing",
		UpdateSaturnPosition
	);

	model->BindShader(
		"src/Resources/Shaders/SaturnRingVertex.txt",
		"src/Resources/Shaders/SaturnRingFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/saturn_ring.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateUranus()
{
	Uranus* shape = new Uranus();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(URANUS_DISTANCE), 0.0f, 0.0f),
		"Uranus",
		UpdateUranusPosition
	);

	model->BindShader(
		"src/Resources/Shaders/UranusVertex.txt",
		"src/Resources/Shaders/UranusFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/uranus.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateUranusRing()
{
	UranusRing* shape = new UranusRing();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(URANUS_DISTANCE), 0.0f, 0.0f),
		"UranusRing",
		UpdateUranusPosition
	);

	model->BindShader(
		"src/Resources/Shaders/UranusRingVertex.txt",
		"src/Resources/Shaders/UranusRingFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/uranus_ring.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateNeptune()
{
	Neptune* shape = new Neptune();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(NEPTUNE_DISTANCE), 0.0f, 0.0f),
		"Neptune",
		UpdateNeptunePosition
	);

	model->BindShader(
		"src/Resources/Shaders/NeptuneVertex.txt",
		"src/Resources/Shaders/NeptuneFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/neptune.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreatePluto()
{
	Pluto* shape = new Pluto();

	Model* model = new Model(
		shape,
		glm::vec3(ScaleDistance(PLUTO_DISTANCE), 0.0f, 0.0f),
		"Pluto",
		UpdatePlutoPosition
	);

	model->BindShader(
		"src/Resources/Shaders/PlutoVertex.txt",
		"src/Resources/Shaders/PlutoFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/pluto.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}

Model* CreateAsteroid()
{
	Asteroid* shape = new Asteroid();

	Model* model = new Model(
		shape,
		glm::vec3(38.f, 0.f, 0.f),
		"Asteroid",
		nullptr
	);

	model->BindShader(
		"src/Resources/Shaders/AsteroidVertex.txt",
		"src/Resources/Shaders/AsteroidFragment.txt"
	);

	model->BindBuffer(
		shape->PositionIndex(),
		shape->PositionSize(),
		shape->PositionStride(),
		shape->PositionOffset()
	);

	model->BindTexture(
		"src/Resources/Textures/asteroid.jpg",
		0, 0, 0, 0,
		GL_TEXTURE0,
		"u_Texture",
		shape->TexCoordIndex(),
		shape->TexCoordSize(),
		shape->TexCoordStride(),
		shape->TexCoordOffset()
	);

	return model;
}