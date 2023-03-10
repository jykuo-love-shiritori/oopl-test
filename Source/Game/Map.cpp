#include "stdafx.h"
#include "Map.h"

using namespace game_framework;

////////////////////////////// Getter //////////////////////////////
bool Map::hasLeftMap()
{
	// FIXME: hardcode for test
	return frameIndex == 1;
}

bool Map::hasRightMap()
{
	// FIXME: hardcode for test
	return frameIndex == 0;
}
bool Map::hasUpMap()
{
	// FIXME: hardcode for test
	return false;
}

bool Map::hasDownMap()
{
	// FIXME: hardcode for test
	return false;
}

////////////////////////////// Move //////////////////////////////
void Map::MoveToLeft()
{
	// FIXME: hardcode for test
	frameIndex = 0;
}

void Map::MoveToRight()
{
	// FIXME: hardcode for test
	frameIndex = 1;
}

void Map::MoveToUp()
{
	// FIXME: didn't implement
}

void Map::MoveToDown()
{
	// FIXME: didn't implement
}