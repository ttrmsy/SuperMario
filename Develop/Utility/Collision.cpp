#include "Collision.h"
#include <math.h>

bool Collision::IsCheckHitTarget(eObjectType object_type) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
	for (eObjectType type : hit_object_type)
	{
		if (type == object_type)
		{
			return true;
		}
	}

	return false;
}

bool Collision::IsCheckHitCollision(Collision target1, Collision target2)
{
	float side[2][4];
	Vector2D tg1, tg2, center[2], distance,size;
	tg1 = target1.pivot;
	tg2 = target2.pivot;
	center[0].x = target1.box_size.x / 2;
	center[0].y = target1.box_size.y / 2;
	center[1].x = target2.box_size.x / 2;
	center[1].y = target2.box_size.y / 2;

	distance.x = tg1.x - tg2.x;
	distance.y = tg1.y - tg2.y;

	if (distance.x < 0)
	{
		distance.x *= -1;
	}

	if (distance.y < 0)
	{
		distance.y *= -1;
	}

	size.x = (target1.box_size.x + target2.box_size.x) / 2;
	size.y = (target1.box_size.y + target2.box_size.y) / 2;

	if (distance.x <= size.x && distance.y <= size.y)
	{
		return true;
	}

	return false;
	////target1�̋�`�����蔻��̕ӂ̍��W
	//side[0][UP] = tg1.y - (target1.box_size.y / 2);
	//side[0][RIGHT] = tg1.x + (target1.box_size.x / 2);
	//side[0][DOWN] = tg1.y + (target1.box_size.y / 2);
	//side[0][LEFT] = tg1.x - (target1.box_size.x / 2);

	////target2�̋�`�����蔻��̕ӂ̍��W
	//side[1][UP] = tg2.y - (target1.box_size.y / 2);
	//side[1][RIGHT] = tg2.x + (target1.box_size.x / 2);
	//side[1][DOWN] = tg2.y + (target1.box_size.y / 2);
	//side[1][LEFT] = tg2.x - (target1.box_size.x / 2);

}