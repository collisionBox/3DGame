#pragma once

static const int mapObjectNumX = 19;
static const int mapObjectNumZ = 10;
static const int Block = 1;
static const int Cylinder = 2;
static const int VerticalMoveBlock = 3;
struct MapChip
{
	int Num;
	const int Data[mapObjectNumZ][mapObjectNumX];
};
// マップデータ.
MapChip MapData[] =
{
	{1,
	{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,3,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,}}
};
