#pragma once
#include "../Character.h"
#include "../../Utility/Camera.h"
#include "../Player/Player.h"

class FireBall : public Character
{
private:
	std::vector<int> fire_image;	//ファイアボールの画像
	std::vector<int> blast_image;	//ファイアボールの爆破画像
	float g_velocity;				//重力
	double radian;					//回転量
	bool delete_flag;				//ファイアボールの削除フラグ
	class Player* player;
	class Camera* camera;					//カメラポインタ
	float animation_time;
	int animation_count;
	bool hit_flag;

public:
	virtual void Initialize() override;									//初期化処理
	virtual void Update(float delta_seconde) override;					//更新処理
	virtual void Draw(const Vector2D& screen_offset) const override;	//描画処理
	virtual void Finalize() override;									//終了処理
	virtual void OnHitCollision(GameObject* hit_object) override;		//当たり判定通知処理
	void Set_Filpflag(bool flag);										//反転フラグ設定処理
	bool Get_DeleteFlag();												//削除判定取得処理
	void Set_Camera(class Camera* c);											//カメラポインタ設定処理
	void Set_Player(class Player* p);

private:
	void Movement(float delta_seconde);
	void AnimationControl(float delta_seconde);
	
};

