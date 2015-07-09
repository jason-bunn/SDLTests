#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets) :
m_position(Vector2D(0,0)),
m_velocity(Vector2D(0,0)),
m_tilesets(tilesets)
{

}

void TileLayer::update()
{

}

void TileLayer::render()
{

}

Tileset TileLayer::getTileSetByID(int tileID)
{

}