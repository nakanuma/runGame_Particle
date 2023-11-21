#include "BackGroundParticle.h"

BackGroundParticle::BackGroundParticle(Vector2 pos, Vector2 velocity)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;
}

BackGroundParticle::~BackGroundParticle()
{
}

void BackGroundParticle::Update()
{
	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新（y方向のみ）
	pos_.y += velocity_.y;

	// 徐々に透明にする
	if (alpha_ > 0) {
		alpha_ -= 4;
	}

	// サイズを小さくする
	if (size_ >= 0) {
		size_ -= 0.6f;
	}

	// サイズが0になったら削除
	if (size_ < 0) {
		del_ = true;
	}
}

void BackGroundParticle::Draw(int scroll)
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x) - scroll, static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x) - scroll, static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x) - scroll, static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x) - scroll, static_cast<int>(rightBottom_.y),
		0, 0,
		1, 1,
		gh_,
		0xFFFFFF00 + alpha_
	);
}

bool BackGroundParticle::GetDelFlag()
{
	return del_;
}
