#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <iostream>
#include <vector>
#include "tinyxml.h"

//forward declarations
class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:

	Level* parseLevel(const char* stateFile);

private:

	void parseTextures(TiXmlElement* pTextureRoot);
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);

	int m_tileSize;
	int m_width;
	int m_height;

};


#endif