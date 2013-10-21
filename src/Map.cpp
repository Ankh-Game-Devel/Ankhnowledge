/*
 * Map.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: makoto
 */

#include "Map.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

Map::Map(Sprite * tile, Sprite * block, float x, float y):GameObject(x,y) {
	this->tile = tile;
	this->tile->incNumRef();
	this->block = block;
	this->block->incNumRef();
	this->char1 = new Sprite("../Ankhnowledge/resources/images/adam.png");
	this->char2 = new Sprite("../Ankhnowledge/resources/images/suti.png");

	srand (time(NULL));

	for(int i = 0; i < 400; i++)
	{
		int random = rand() % 2;

		if(random == 1 || i == 20 || i == 39)
			tiles.push_back(new Tile(tile,getX()+ tile->getWidth()*((int)(i%20)), getY() + tile->getHeight()*((int)(i/20))));
		else
			tiles.push_back(new Tile(tile, block,getX()+ tile->getWidth()*((int)(i%20)), getY() + tile->getHeight()*((int)(i/20))));
	}

}

Map::~Map() {
	this->tile->decNumRef();
	this->tile = 0;

	this->block->decNumRef();
	this->block = 0;
	// TODO Auto-generated destructor stub
}

void Map::render(float cameraX, float cameraY){
	for(int i = 0; i < tiles.size(); i++)
	{
		tiles.at(i)->render(0,0);
	}
	char1->render(getX(),getY());
	char2->render(getX()+tile->getWidth()*19,getY());
}

int Map::update(int dt){

	return 0;
}
