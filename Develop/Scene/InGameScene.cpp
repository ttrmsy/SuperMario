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
	UI_string = rm->GetImageResource("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);
	UI_time = rm->GetImageResource("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	num_image = UI_num[0];
	num_time = UI_num[5];
	num_world = UI_num[0];

	//BGM�̃��[�v�Đ�
	PlayMusic("Resource/Sounds/BGM_MarioGround.wav", DX_PLAYTYPE_LOOP);

	p = nullptr;
	objm = GameObjectManager::GetInstance();

	//��i�w�i�摜�j�̓ǂݍ���
	sky_image = LoadGraph("Resource/Images/sora.png");

	//�_�́i�w�i�摜�j�ǂݍ���
	cloud_image[0] = LoadGraph("Resource/Images/cloud1.png");
	cloud_image[1] = LoadGraph("Resource/Images/cloud2.png");
	cloud_image[2] = LoadGraph("Resource/Images/cloud3.png");
	cloud_image[3] = LoadGraph("Resource/Images/cloud4.png");
	cloud_image[4] = LoadGraph("Resource/Images/cloud5.png");
	cloud_image[5] = LoadGraph("Resource/Images/cloud6.png");

	//�R�i�w�i�摜�j�̓ǂݍ���
	mountain_image[0] = LoadGraph("Resource/Images/mountain_up.png");
	mountain_image[1] = LoadGraph("Resource/Images/mountain_left.png");
	mountain_image[2] = LoadGraph("Resource/Images/mountain_surface.png");
	mountain_image[3] = LoadGraph("Resource/Images/mountain_surface1.png");
	mountain_image[4] = LoadGraph("Resource/Images/mountain_center.png");
	mountain_image[5] = LoadGraph("Resource/Images/mountain_right.png");

	//�t���ρi�w�i�摜�j�̓ǂݍ���
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
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraphF(a, b, 1.0, 0.0, num_time, TRUE);
		a += 16;

	}

	LoadGraphScreen(360, 28, "Resource/Images/UI/world.png", TRUE);
	for (int i = 0; i < 3; i++)
	a = 400;
	b = 55;
	{
		DrawRotaGraphF(a, b, 1.0, 0.0, num_world, TRUE);
		a += 16;
	}

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


	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	Ground* ground = nullptr;
	Cloud* cloud = nullptr;
	Kuribo* k = nullptr;
	Nokonoko* n = nullptr;
	Pipe* pipe = nullptr;
	GoalFlag* f = nullptr;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		//�I�u�W�F�N�g�𐶐�����ʒu
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
	
		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		//���o����������'P'�Ȃ�Player��`�悷��
		else if (c == 'M')
		{
			p = objm->CreateGameObject<Player>(generate_location);
			camera->Set_Player(p);
			p->Set_Camera(camera);

			x++;
		}
		// ���o����������G�Ȃ�A�n�ʂ𐶐�
		else if (c == 'G')
		{
			ground = objm->CreateGameObject<Ground>(generate_location);
			ground->Set_Camera(camera);
			x++;
		}
		//���o����������K�Ȃ�A�N���{�[�i�G�j�𐶐�����
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
				objm->CreateGameObject<Question>(generate_location);
				x++;
				break;

			case '0':
				objm->CreateGameObject<Brick>(generate_location)->SetPlayerPointer(p);
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
		//���o����������0�Ȃ牽�����������A���̕���������
		else if (c == '0')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}

		
		
	}

	// �J�����t�@�C�������
	fclose(fp);
}

void InGameScene::DrawBackGroundCSV() const
{

	FILE* fp = NULL;

	std::string file_name = "Resource/Map/BackGround.csv";
	
	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;
	Cloud* cloud = nullptr;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		//�`��ʒu�ݒ�
		Vector2D generate_location = (Vector2D((float)x, (float)y) * OBJECT_SIZE) + (OBJECT_SIZE / 2);
		
		//�X�N���[�X��������x���W�ʒu�ݒ�
		generate_location.x = generate_location.x - camera->Get_Offset().x;

		//�J�����E�[�̍��W
		float Dx = camera->Get_CameraLocation().x + D_WIN_MAX_X / 2;

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o����������S�Ȃ��i�w�i�j�𐶐�����
		if (c == '0')
		{
			if (generate_location.x - OBJECT_SIZE / 2 < Dx)		//�w�i�摜�̍��W���J��������������`�悷��
			{
				DrawRotaGraphF(generate_location.x, generate_location.y, 1.0, 0, sky_image, TRUE);
			}
			x++;
		}
		//���o����������C�Ȃ�_�i�w�i�j�𐶐�����
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
		//���o����������M��������R�i�w�i�j��`�悷��
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
		//���o����������L��������t���ρi�w�i�j��`�悷��
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
		//���o�����������h�b�g�Ȃ牽�����������A���̕���������
		else if (c == '.')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		

	}

	// �J�����t�@�C�������
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