#include "nameParticle.h"

nameParticle::nameParticle()
{
}

nameParticle::~nameParticle()
{
}

void nameParticle::Update()
{
	// 4�_�̍��W���X�V
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };
}

void nameParticle::Draw()
{
}

bool nameParticle::GetDelFlag()
{
	return del_;
}
