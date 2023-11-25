#include "ModeChangeParticle2.h"

ModeChangeParticle2::ModeChangeParticle2(Vector2 pos)
{
	pos_.x = pos.x;
	pos_.y = pos.y;
}

ModeChangeParticle2::~ModeChangeParticle2()
{
}

void ModeChangeParticle2::Update(Vector2 moveAmount)
{
	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新
	pos_.x += moveAmount.x;
	pos_.y += moveAmount.y;

	// サイズを大きくする
	size_ += 1;

	// 透明にする
	alpha_ -= 15;

	//　透明になったら消える
	if (alpha_ <= 0) {
		del_ = true;
	}
}

void ModeChangeParticle2::Draw(int scroll)
{
	if (del_ == false) {
		Novice::DrawQuad(
			static_cast<int>(leftTop_.x) - scroll, static_cast<int>(leftTop_.y),
			static_cast<int>(rightTop_.x) - scroll, static_cast<int>(rightTop_.y),
			static_cast<int>(leftBottom_.x) - scroll, static_cast<int>(leftBottom_.y),
			static_cast<int>(rightBottom_.x) - scroll, static_cast<int>(rightBottom_.y),
			0, 0,
			42, 42,
			gh_,
			0xFFFFFF00 + alpha_
		);
	}
}

bool ModeChangeParticle2::GetDelFlag()
{
	return false;
}
