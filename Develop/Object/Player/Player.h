#pragma once
#include "../Character.h"
#include "PlayerState/PlayerStateBase.h"
#include "../../Utility/Camera.h"
#include <vector>

enum ePlayerState
{
	idle,
	walk,
	jump,
	get,
	none
};

enum ePlayerLevel
{
	Small,
	Big,
	Fire
};

class Player : public Character
{
private:
	std::vector<int> SmallMario_animation;
	std::vector<int> BigMario_animation;
	std::vector<int> FireMario_animation;
	std::vector<int> move_animation;	//Player画像
	std::vector<int> levelup_animation;	//アイテム取得時のアニメーション画像
	class PlayerStateBase* player_state;	//Playerの状態
	ePlayerState next_state;	//Playerの遷移先状態
	ePlayerLevel p_level;
	float animation_time;		//アニメーションの時間
	int animation_count;		//アニメーションの回数
	int animation_number;		//アニメーション配列の添え字
	float g_velocity;			//重力
	bool is_ground;
	bool hit[4];
	ePlayerState p_state;
	class Camera* camera;

	Vector2D dv;	//デバック用変数
	int is_death;

public:
	bool jump_flag;		//ジャンプできる状態かの判定フラグ
	bool slide_flag;	//マリオがブレーキを掛けている状態かの判定フラグ

	//アニメーションの順番
	int animation_num[4][3] = { { 1, 2, 3},		//マリオがSmallの時
								{ 2, 3, 4},		//マリオがBigとFireの時
								{ 0, 1, 0},		//マリオがレベルアップしたとき（下も同じ）
								{ 0, 1, 2}};	
								
public:
	virtual void Initialize() override;									//初期化処理
	virtual void Update(float delta_seconde) override;					//更新処理
	virtual void Draw(const Vector2D& screen_offset) const override;	//描画処理
	virtual void Finalize() override;									//終了処理
	virtual void OnHitCollision(GameObject* hit_object) override;		//当たり判定処理
	virtual const Collision& GetCollision() const override;				//コリジョン取得処理
	virtual const unsigned char GetZLayer() const override;				//Zレイヤー取得処理
	virtual const bool GetMobility() const override;					//可動性取得処理
	ePlayerState GetPlayerState() const;								//Player状態取得処理
	void SetNextState(ePlayerState next_state);
	void SetFilp_flag(bool flag);
	bool GetFilp_flag();
	Vector2D Get_Velocity();
	void Set_Velocity(Vector2D velocity);
	void Set_IsGround(bool flag);
	void Set_Camera(Camera* c);
	void Set_SlideFlag(bool flag);
	int Get_DeathCount();

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_seconde);
	void GetItem_Animation(float delta_seconde);
	void DeathCount();


};
