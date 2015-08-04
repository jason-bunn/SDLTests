#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <vector>
#include "Level.h"
#include "tinyxml.h"
#include "Layer.h"

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:

	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);

	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);

	void parseTextures(TiXmlElement* pTextureRoot);

	void parseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*> *pLayers);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif