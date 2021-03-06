#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>
#include <vector>

class TileLayer;

class GameObject
{
public:

	virtual ~GameObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual void clean() = 0;

	virtual void collision() = 0;

	Vector2D& getPosition() { return m_position; }
	Vector2D& getVelocity() { return m_velocity; }

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	bool updating() { return m_bUpdating; }
	bool dead() { return m_bDead; }
	bool dying() { return m_bDying; }

	//set whether to update the object or not
	void setUpdating(bool updating) { m_bUpdating = updating; }

	void setCollisionLayers(std::vector<TileLayer*>* layers) { m_pCollisionLayers = layers; }

	std::string type() { return m_type; }
protected:

	GameObject() : m_position(0, 0),
		m_velocity(0, 0),
		m_acceleration(0, 0),
		m_width(0),
		m_height(0),
		m_currentRow(0),
		m_currentFrame(0),
		m_bUpdating(false),
		m_bDead(false),
		m_bDying(false),
		m_angle(0),
		m_alpha(255)
	{

	}

	//movement
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	//size
	int m_width;
	int m_height;

	//animation
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	std::string m_textureID;

	//bools
	bool m_bUpdating;
	bool m_bDead;
	bool m_bDying;

	//rotation
	double m_angle;

	//blending
	int m_alpha;

	std::vector<TileLayer*>* m_pCollisionLayers;

	std::string m_type;
};


#endif