#pragma once
#include "../Character.h"
#include "../Blocks/Brick.h"

#define D_GRAVITY (9.807f)		//重力加速度


class ItemBase : public Character
{
protected:
	std::vector<int> move_animation;	//アニメーション画像
	float animation_count;				//アニメーションカウント
	float animation_time;
	Vector2D old_loction;		//初期座標
	bool box_out;				//ボックスから完全に出ているか
	int item_sound;			//アイテム取得sound
	bool is_ground;
	bool hit_flag;
	float g_velocity;
	class Brick* block_p;

public:
	ItemBase();
	~ItemBase();

	void Finalize() {
		move_animation.clear();
	}


	//移動処理
	virtual void Movement(float delta_seconde);

	//アイテムが出てくる処理
	void ItemPush();

	//ブロックがたたかれると上に跳ねる処理
	void Bounce();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	//初期座標の保存
	void SetOldLocation(Vector2D a);

};