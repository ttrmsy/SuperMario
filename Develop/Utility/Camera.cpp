#include "Camera.h"

Camera::Camera() : player(nullptr), camera_location(D_WIN_MAX_X / 2), offset(0)
{
	
}

Camera::~Camera()
{
	Finalize();
}

void Camera::Update()
{
	//Playerが画面中央よりも前にいるとカメラの位置を更新する
	if (player != nullptr)
	{
		if (player->GetLocation().x > camera_location.x)
		{
			//カメラのX座標更新
			camera_location.x = player->GetLocation().x;
			offset.x = player->GetLocation().x - (D_WIN_MAX_X / 2);

		}
	}
	

}

void Camera::Finalize()
{
	delete player;
}

Vector2D Camera::Get_Offset()
{
	return offset;
}

Vector2D Camera::Get_CameraLocation()
{
	return camera_location;
}

void Camera::Set_Player(Player* p)
{
	player = p;
}
