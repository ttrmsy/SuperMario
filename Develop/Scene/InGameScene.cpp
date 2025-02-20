#include "InGameScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Object/Player/Player.h"
#include "../Utility/Collision.h"
#include "../Object/Enemy/Kuribo.h"
#include "../Object/Enemy/Nokonoko.h"
#include "../Object/Blocks/Ground.h"
#include "../Object/BackGround/Cloud.h"
#include "../Object/BackGround/Sky.h"
#include "../Object/Blocks/Question.h"
#include "../Object/Blocks/Pipe.h"
#include "../Object/Blocks/Pipeenter.h"
#include "../Object/Blocks/Brick.h"
#include "../Object/Blocks/HardBlock.h"
#include "../Object/Goal/GoalFlag.h"
#include <fstream>

#define MAX_LOAD_LINE	20;
#define MAX_LOAD_COLUMN	(15);

void InGameScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	UI_num = rm->GetImageResource("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	num_image = UI_num[0];
	num_time = UI_num[0];
	num_world = UI_num[0];

	//BGMのループ再生
	PlayMusic("Resource/Sounds/BGM_MarioGround.wav", DX_PLAYTYPE_LOOP);

	p = nullptr;
	objm = GameObjectManager::GetInstance();

	//空（背景画像）の読み込み
	sky_image = LoadGraph("Resource/Images/sora.png");

	//雲の（背景画像）読み込み
	cloud_image[0] = LoadGraph("Resource/Images/cloud1.png");
	cloud_image[1] = LoadGraph("Resource/Images/cloud2.png");
	cloud_image[2] = LoadGraph("Resource/Images/cloud3.png");
	cloud_image[3] = LoadGraph("Resource/Images/cloud4.png");
	cloud_image[4] = LoadGraph("Resource/Images/cloud5.png");
	cloud_image[5] = LoadGraph("Resource/Images/cloud6.png");
	
	//山（背景画像）の読み込み
	mountain_image[0] = LoadGraph("Resource/Images/mountain_up.png");
	mountain_image[1] = LoadGraph("Resource/Images/mountain_left.png");
	mountain_image[2] = LoadGraph("Resource/Images/mountain_surface.png");
	mountain_image[3] = LoadGraph("Resource/Images/mountain_surface1.png");
	mountain_image[4] = LoadGraph("Resource/Images/mountain_center.png");
	mountain_image[5] = LoadGraph("Resource/Images/mountain_right.png");

	//葉っぱ（背景画像）の読み込み
	leaf_image[0] = LoadGraph("Resource/Images/ha0.png");
	leaf_image[1] = LoadGraph("Resource/Images/ha1.png");
	leaf_image[2] = LoadGraph("Resource/Images/ha2.png");

	LoadStageMapCSV();
}

eSceneType InGameScene::Update(float delta_second)
{
	objm->HitCheck();

	InputManager* input = InputManager::GetInstance();

	if (p->Get_DeathCount() >= 1)
	{
		return eSceneType::eResult;
	}

	// タイマー更新処理
	time_counter += delta_second;  // フレームごとに経過時間を加算

	if (time_counter >= 1.0f)  // 1秒経過した場合
	{
		time_remaining -= 1;  // 1秒減らす
		time_counter = 0.0f;  // カウンターをリセット
	}

	// 残り時間が0になったら、必要な処理を追加
	if (time_remaining <= 0)
	{
		time_remaining = 0;
		// ゲームオーバーや別の処理を追加することも可能
	}

	__super::Update(delta_second);

	camera->Update();

	DeleteObject();

	Draw();




	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	DrawBackGroundCSV();

	

	LoadGraphScreen(88, 28, "Resource/Images/UI/name_mario.png", TRUE);
	int x, y;
	x = 96;
	y = 55;
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(x, y, 1.0, 0.0, num_image, TRUE);
		x += 16;
	}

	LoadGraphScreen(500, 28, "Resource/Images/UI/time.png", TRUE);
	int a, b;
	a = 520;
	b = 55;

	// 制限時間を500秒に設定
	LONGLONG time_set = time_remaining;
	int time_sec1 = time_set / 100;  // 百の位
	int time_sec2 = (time_set % 100) / 10;  // 十の位
	int time_sec3 = time_set % 10;  // 一の位

	// 各桁の数字を描画
	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[time_sec1], TRUE);  // 百の位
	a += 16;
	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[time_sec2], TRUE);  // 十の位
	a += 16;
	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[time_sec3], TRUE);  // 一の位

	LoadGraphScreen(360, 28, "Resource/Images/UI/world.png", TRUE);
	for (int i = 0; i < 3; i++)
	a = 400;

	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[1], TRUE);
	a += 16;
	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[10], TRUE);
	a += 16;
	DrawRotaGraphF(a, b, 1.0, 0.0, UI_num[1], TRUE);
	a += 16;

	__super::Draw();
}

void InGameScene::Finalize()
{

}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

void InGameScene::CheckCollision(GameObject* target, GameObject* partner)
{
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		tc.pivot += target->GetLocation();
		pc.pivot += partner->GetLocation();

		if (tc.IsCheckHitCollision(tc, pc))
		{
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}

}

void InGameScene::LoadStageMapCSV()
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/Stage_Object.csv";


	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;
	Ground* ground = nullptr;
	Cloud* cloud = nullptr;
	Kuribo* k = nullptr;
	Nokonoko* n = nullptr;
	Pipe* pipe = nullptr;
	GoalFlag* f = nullptr;

	// ファイル内の文字を確認していく
	while (true)
	{

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		//オブジェクトを生成する位置
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
	
		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		//抽出した文字が'P'ならPlayerを描画する
		else if (c == 'M')
		{
			p = objm->CreateGameObject<Player>(generate_location);
			camera->Set_Player(p);
			p->Set_Camera(camera);

			x++;
		}
		// 抽出した文字がGなら、地面を生成
		else if (c == 'G')
		{
			ground = objm->CreateGameObject<Ground>(generate_location);
			ground->Set_Camera(camera);
			x++;
		}
		//抽出した文字がKなら、クリボー（敵）を生成する
		else if (c == 'C')
		{
			k = objm->CreateGameObject<Kuribo>(generate_location);
			k->Set_Camera(camera);
			x++;
		}
		else if (c == 'N')
		{
			n = objm->CreateGameObject<Nokonoko>(generate_location);
			n->Set_Camera(camera);
			x++;
		}
		else if (c == 'B')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '?':
				c = fgetc(fp);
				switch (c)
				{
				case 'M':
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eMushroom);
					x++;
					break;

				case 'F':
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eFlower);
					x++;
					break;

				case 'C':
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eCoin);
					x++;
					break;

				case 'S':
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eStar);
					x++;
					break;

				case 'O':
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eOneup);
					x++;
					break;

				default:
					objm->CreateGameObject<Question>(generate_location)->SetItemType(eCoin);
					x++;
					break;
				}

				break;

			case '0':
				objm->CreateGameObject<Brick>(generate_location);
				x++;
				break;

			case '1':
				objm->CreateGameObject<HardBlock>(generate_location);
				x++;
				break;

			case 'H':
				x++;
				break;
			}
		}
		else if (c == 'P')
		{
			c = fgetc(fp);

			switch (c)
			{
			case '0':
				pipe = objm->CreateGameObject<Pipe>(generate_location);
				pipe->Set_Image(0);
				x++;
				break;

			case '1':
				pipe = objm->CreateGameObject<Pipe>(generate_location);
				pipe->Set_Image(1);
				x++;
				break;

			case '2':
				pipe = objm->CreateGameObject<Pipe>(generate_location);
				pipe->Set_Image(2);
				x++;
				break;

			case '3':
				pipe = objm->CreateGameObject<Pipe>(generate_location);
				pipe->Set_Image(3);
				x++;
				break;
			case 'E':

				objm->CreateGameObject<Pipeenter>(Vector2D((generate_location.x + 16.0f),generate_location.y + 8.0f));
				x++;
				break;
			}
		}
		else if (c == 'F')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				f = objm->CreateGameObject<GoalFlag>(generate_location);
				f->Set_Image(0);
				x++;
				break;

			case '1':
				f = objm->CreateGameObject<GoalFlag>(generate_location);
				f->Set_Image(1);
				x++;
				break;
			}
		}
		//抽出した文字が0なら何も生成せず、次の文字を見る
		else if (c == '0')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

		
		
	}

	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::DrawBackGroundCSV() const
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/BackGround.csv";
	
	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;
	Cloud* cloud = nullptr;

	// ファイル内の文字を確認していく
	while (true)
	{
		//描画位置設定
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
		
		//スクロースした時のx座標位置設定
		generate_location.x = generate_location.x - camera->Get_Offset().x;

		//カメラ右端の座標
		float Dx = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字がSなら空（背景）を生成する
		if (c == '0')
		{
			if (generate_location.x - OBJECT_SIZE / 2 < Dx)		//背景画像の座標がカメラ内だったら描画する
			{
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, sky_image, TRUE);
			}
			x++;
		}
		//抽出した文字がCなら雲（背景）を生成する
		else if (c == 'C')
		{
			c = fgetc(fp);
			if (c == '0')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[0], TRUE);
				}
				x++;
			}
			else if (c == '1')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[1], TRUE);
				}
				x++;
			}
			else if (c == '2')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[2], TRUE);
				}
				x++;
			}
			else if (c == '3')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[3], TRUE);
				}
				x++;
			}
			else if (c == '4')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[4], TRUE);
				}
				x++;
			}
			else if (c == '5')
			{
				if (generate_location.x - OBJECT_SIZE / 2 < Dx)
				{
					DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, cloud_image[5], TRUE);
				}
				x++;
			}

		}
		//抽出した文字がMだったら山（背景）を描画する
		else if (c == 'M')
		{
			c = fgetc(fp);

			switch (c)
			{
			case 't':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[0], TRUE);
				x++;
				break;

			case 'l':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[1], TRUE);
				x++;
				break;

			case 'r':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[5], TRUE);
				x++;
				break;

			case '0':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[2], TRUE);
				x++;
				break;

			case '1':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[3], TRUE);
				x++;
				break;

			case '2':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, mountain_image[4], TRUE);
				x++;
				break;
			}
		}
		//抽出した文字がLだったら葉っぱ（背景）を描画する
		else if (c == 'L')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, leaf_image[0], TRUE);
				x++;
				break;

			case '1':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, leaf_image[1], TRUE);
				x++;
				break;

			case '2':
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, leaf_image[2], TRUE);
				x++;
				break;
			}
		}
		//抽出した文字がドットなら何も生成せず、次の文字を見る
		else if (c == '.')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		

	}

	// 開いたファイルを閉じる
	fclose(fp);
}

void InGameScene::DeleteObject()
{
	float offset = camera->Get_Offset().x;
	std::vector<GameObject*> object_list = objm->GetObjectsList();
	
	if (!object_list.empty())
	{
		for (int i = 0; i < object_list.size(); i++)
		{
			int x = (object_list[i]->GetLocation().x + OBJECT_SIZE / 2) - offset;
			if (0 >= x)
			{
 				objm->DestroyGameObject(object_list[i]);

			}
		}

	}
}