#pragma once
#include "ItemBase.h"

class Flower : public ItemBase
{
private:

public:
	Flower();
	~Flower();

	//����������
	virtual void Initialize() override;

	//�X�V����
	virtual void Update(float delta_seconde) override;

	//�`�揈��
	virtual void Draw(const Vector2D& screen_offset) const override;

	//�I��������
	virtual void Finalize() override;

private:

	//�A�j���[�V��������
	void AnimationControl(float delta_second);
};
