#include "TileMap.h"
#include <iostream>
#include "BlockMovable.h"
#include "BlockTreasure.h"
#define MOVABLE_BLOCK 1
#define NORMAL_TILE   0
#define TREASURE 2


using namespace std;

//Construtor do TileMap, passando o arquivo com o mapa dos tiles, o tileset e o tilesize
TileMap::TileMap(std::string mapa, Sprite* tile, Sprite* block, float posX, float posY)
{
    this->mapColumns = 0;
    this->mapRows = 0;
    this->tile = tile;
    this->block = block;
    this->posX = posX;
    this->posY = posY;
    //carrega o mapa
    load(mapa);

}

void TileMap::load(std::string mapPath) {
    //abre o arquivo indicando leitura
    FILE* mapFile = fopen(mapPath.c_str(), "r");
    if(mapFile == NULL) {
        return;
    }
    int index = 0;
    //pega a largura, altura e layers do mapa, indicados na primeira linha do arquivo
    fscanf(mapFile, "%d,%d,", &mapColumns, &mapRows);
    //pula 4 linhas para cair na posição exata dos indices dos tiles indicados no arquivo txt
    fscanf(mapFile, "\n\n\n\n");
    int id = 0;
    //loop que percorre as colunas, linhas e os layers do arquivo txt


        for(int y = 0;y < mapRows;y++)
        {
            for(int x = 0; x < mapColumns;x++)
            {

                fscanf(mapFile, "%d,", &index);
                
                if(index == NORMAL_TILE)
                {

                	tiles.push_back(new Tile(tile, 0,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)), id));
                }
                else if(index == MOVABLE_BLOCK)
                {
                	
                	tiles.push_back(new Tile(tile
											, new BlockMovable(block,posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
											, posX+ tile->getWidth()*((int)(id%mapColumns))
											, posY + tile->getHeight()*((int)(id/mapColumns))
											, id));
                }
                else if(index == TREASURE)
                {
                	
					tiles.push_back(new Tile(tile
											, new BlockTreasure(new Sprite(SDLBase::resourcesPath + "bauanimacao.png"),posX+ tile->getWidth()*((int)(id%mapColumns)), posY + tile->getHeight()*((int)(id/mapColumns)))
											, posX+ tile->getWidth()*((int)(id%mapColumns))
											, posY + tile->getHeight()*((int)(id/mapColumns))
											, id));
                }
                id++;
            }
            fscanf(mapFile, "\n");
            fscanf(mapFile, "\n");
        }
    //fecha arquivo
    fclose(mapFile);

}


vector<Tile* > TileMap::getTiles(){
	return this->tiles;
}

int TileMap::getColumns(){
	return this->mapColumns;
}

int TileMap::getRows(){
	return this->mapRows;
}

TileMap::~TileMap()
{

}
