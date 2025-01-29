#pragma once
#include "../Character.h"

enum Items
{
	eNull,
	eCoin,
	eMushroom,
	wFlower,
	eOneup,
	eStar
};

class ItemBase : public Character
{
protected:
	std::vector<int> move_animation;	//アニメーション画像
	Items item_type;					//アイテムタイプ
	float animation_count;				//アニメーションカウント
	float animation_time;

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}

	//アイテムが出てくる処理
	void ItemPush();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	//アイテムタイプ取得
	Items GetItemType();
};