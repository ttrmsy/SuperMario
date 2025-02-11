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
	damage,
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
	std::vector<int> FireMario_animation;//Player画像
	std::vector<int> levelup_animation;	//アイテム取得時のアニメーション画像
	class PlayerStateBase* player_state;	//Playerの状態
	ePlayerState next_state;	//Playerの遷移先状態
	ePlayerLevel p_level;
	float animation_time;		//アニメーションの時間
	int move_animation_count;		//アニメーションの回数
	int move_animation_number;		//アニメーション配列の添え字
	int level_animation_count;		//レベル変更時のアニメーション用カウント
	int level_animation_number;		//レベル変更時のアニメーション用添え字
	float g_velocity;			//重力
	bool is_ground;
	bool hit[4];
	ePlayerState p_state;
	class Camera* camera;
	int fire_count;		//ファイアーボールを出した数
	bool change_flag;

	int is_death;

public:
	bool jump_flag;		//ジャンプできる状態かの判定フラグ
	bool slide_flag;	//マリオがブレーキを掛けている状態かの判定フラグ

	//アニメーションの順番
	int animation_num[5][3] = { { 1, 2, 3},		//マリオがSmallの時
								{ 2, 3, 4},		//マリオがBigとFireの時
								{ 0, 1, 0},		//マリオがレベルアップしたとき（下も同じ）
								{ 0, 1, 2},
								{ 2, 1, 0} };	//マリオがレベルダウンしたとき
								
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
	void SetNextState(ePlayerState next_state);							//Playerの次の状態取得処理
	void SetFilp_flag(bool flag);										//反転フラグの設定処理
	bool GetFilp_flag();												//反転フラグの取得処理
	Vector2D Get_Velocity();											//移動量の取得処理
	void Set_Velocity(Vector2D velocity);								//移動量の設定処理
	void Set_IsGround(bool flag);										//地面に着地しているかの判定設定処理
	void Set_Camera(Camera* c);											//カメラのポインタ設定処理
	void Set_SlideFlag(bool flag);										//ブレーキを掛けている状態かの判定設定処理
	int Get_DeathCount();												
	void Set_FireCount(int count);
	ePlayerLevel Get_PlayerLevel();										//Playerのレベル取得処理

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_seconde);
	void GetItem_Animation(float delta_seconde);
	void PowerDown_Animation(float delta_seconde);
	void DeathCount();


};
