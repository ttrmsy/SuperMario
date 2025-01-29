#pragma once
#include "SceneBase.h"
#include "../Object/GameObjectManager.h"



class InGameScene : public SceneBase
{
private:
	class GameObjectManager* objm;
	int sky_image;	//��̔w�i�摜
	int leaf_image[3];	//���̔w�i�摜�i�\�z��
	int cloud_image[6];
	int mountain_image[6];
	Player* p;
	

public:
	virtual void Initialize() override;
	virtual eSceneType Update(float delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	virtual eSceneType GetNowSceneType() const override;
	virtual void CheckCollision(GameObject* target, GameObject* partner) override;

private:
	 void LoadStageMapCSV();
	 void DrawBackGroundCSV() const;
	 void DeleteObject();
};

