#pragma once
#include "ItemBase.h"

class Mushroom : public ItemBase
{
public:
	Mushroom();
	~Mushroom();

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	virtual void Update(float delta_seconde) override;

	//描画処理
	virtual void Draw(const Vector2D& screen_offset) const override;

	//終了時処理
	virtual void Finalize() override;

private:

};
