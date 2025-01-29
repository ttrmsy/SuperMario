#pragma once
#include "ItemBase.h"

class Coin : public ItemBase
{
private:

public:
	Coin();
	~Coin();

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	virtual void Update(float delta_seconde) override;

	//描画処理
	virtual void Draw(const Vector2D& screen_offset) const override;

	//終了時処理
	virtual void Finalize() override;

private:

	//アニメーション処理
	void AnimationControl(float delta_second);
};
