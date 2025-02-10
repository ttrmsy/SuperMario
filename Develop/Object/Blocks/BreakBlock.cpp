#include "BreakBlock.h"
#include "../../Utility/ResourceManager.h"
#include "../GameObjectManager.h"
#include "../../Utility/Singleton.h"
#include "DxLib.h"

#define MAX_COUNT	(8)		//ボックス上昇・下降する上限カウント
#define BOX_HALF	(16.0f)		//ボックス上昇・下降する上限カウント
#define D_DOWN_SPEED	(50.0f)		//下降スピード

void BreakBlock::Initialize()
{	
	ResourceManager* rm = ResourceManager::GetInstance();			//インスタンス取得
	image = rm->GetImageResource("Resource/Images/Block/bloak_1.png")[0];			//画像の読み込み
	break_sound = rm->GetSoundResource("Resource/Sounds/SE_BlockBreak.wav");		//SEの読み込み

	PlaySoundMem(break_sound, DX_PLAYTYPE_BACK);	//SE再生

	is_mobility = true;

	z_layer = 5;

	rotate_count = 0;

	velocity.x = 2.0f;
	velocity.y = -10.0f;
}

void BreakBlock::Update(float delta_seconde)
{
	//落下処理
	Falling(delta_seconde);

	//roteta_countが10より大きくなると破片の角度を変更する
	if (rotate_count > 10)
	{
		radian += 0.8f;		//角度の変更
		rotate_count = 0;	//カウントの初期化
	}

	//画面外に行くと消す処理
	if (location.y > 640)
	{
		//ゲームオブジェクトのポインタを取得
		GameObjectManager* gm_p = GameObjectManager::GetInstance();

		//自身を削除リストに追加
		gm_p->DestroyGameObject(this);
	}

	//移動力の加算
	velocity.y = velocity.y + 1.0f;
	velocity.x = velocity.x + 0.1f;

	//
	rotate_count++;
}

//描画処理
void BreakBlock::Draw(const Vector2D& screen_offset) const
{
	//左上破片の描画
	DrawRotaGraphF(loc_1.x - screen_offset.x, loc_1.y - screen_offset.y, 1.0, -radian, image, TRUE, filp_flag);

	//左下破片の描画
	DrawRotaGraphF(loc_2.x - screen_offset.x, loc_2.y - screen_offset.y, 1.0, -radian, image, TRUE, filp_flag);

	//右上破片の描画
	DrawRotaGraphF(loc_3.x - screen_offset.x, loc_3.y - screen_offset.y, 1.0, radian, image, TRUE, filp_flag);

	//右下破片の描画
	DrawRotaGraphF(loc_4.x - screen_offset.x, loc_4.y - screen_offset.y, 1.0, radian, image, TRUE, filp_flag);

}

//終了時処理
void BreakBlock::Finalize()
{
	image = NULL;
	break_sound = NULL;
}

//移動処理
void BreakBlock::Falling(float delta_seconde)
{
	//下に落ちていく処理
	loc_1.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_2.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_3.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;
	loc_4.y += (velocity.y * D_DOWN_SPEED) * delta_seconde;

	//左右に分かれていく処理
	loc_1.x -= (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_2.x -= (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_3.x += (velocity.x * D_DOWN_SPEED) * delta_seconde;
	loc_4.x += (velocity.x * D_DOWN_SPEED) * delta_seconde;
}

//上下左右の座標設定
void BreakBlock::SetLocation(Vector2D location)
{
	this->location = location;

	//左上の座標
	loc_1.x = (location.x - BOX_HALF);
	loc_1.y = (location.y - BOX_HALF);

	//左下の座標
	loc_2.x = (location.x - BOX_HALF);
	loc_2.y = (location.y + BOX_HALF);

	//右上の座標
	loc_3.x = (location.x + BOX_HALF);
	loc_3.y = (location.y - BOX_HALF);

	//右下の座標
	loc_4.x = (location.x + BOX_HALF);
	loc_4.y = (location.y + BOX_HALF);
	
}