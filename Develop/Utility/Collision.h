#pragma once
#include "Vector2D.h"
#include <vector>


enum eObjectType
{
	eNone,
	ePlayer,
	eEnemy,
	eBlock,
	eGround,
	eItem,
	eGoal,
	ePipe,
	ePipeEnter,
	eFireBall,
	eHardBlock
};

enum Items
{
	eNull,
	eCoin,
	eMushroom,
	eFlower,
	eOneup,
	eStar
};

enum eSide
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

class Collision
{
public:
	bool is_blocking;
	Vector2D box_size;
	Vector2D pivot;
	eObjectType object_type;
	Items item_type;
	std::vector<eObjectType> hit_object_type;

	bool IsCheckHitTarget(eObjectType object_type) const;
	bool IsCheckHitCollision(Collision target1, Collision target2);
};

