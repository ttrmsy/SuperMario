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
	Vector2D old_loction;		//初期座標
	bool box_out;				//ボックスから完全に出ているか
	int item_sound;			//アイテム取得sound

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}


	//移動処理
	virtual void Movement();

	//アイテムが出てくる処理
	void ItemPush();

	//ブロックがたたかれると上に跳ねる処理
	void Bounce();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	//アイテムタイプ取得
	Items GetItemType();

	//初期座標の保存
	void SetOldLocation(Vector2D a);

};