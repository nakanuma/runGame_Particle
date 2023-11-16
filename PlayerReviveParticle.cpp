#include "PlayerReviveParticle.h"

PlayerReviveParticle::PlayerReviveParticle(Vector2 pos, Vector2 velocity)
{
	pos_.x = pos.x;
	pos_.y = pos.y;

	velocity_.x = velocity.x;
	velocity_.y = velocity.y;
}

PlayerReviveParticle::~PlayerReviveParticle()
{
}

void PlayerReviveParticle::Update()
{
	// タイマーを進める
	timer_++;

	// 4点の座標を更新
	leftTop_ = { pos_.x - (size_ / 2),pos_.y - (size_ / 2) };
	rightTop_ = { pos_.x + (size_ / 2),pos_.y - (size_ / 2) };
	leftBottom_ = { pos_.x - (size_ / 2),pos_.y + (size_ / 2) };
	rightBottom_ = { pos_.x + (size_ / 2),pos_.y + (size_ / 2) };

	// 座標を更新
	pos_.x -= velocity_.x * speed_;
	pos_.y -= velocity_.y * speed_;

	// 色を付けていく
	alpha_ += 8;

	// タイマーが指定時間に到達したらパーティクルを削除
	if (timer_ == delTime_) {
		del_ = true;
	}
}

void PlayerReviveParticle::Draw()
{
	Novice::DrawQuad(
		static_cast<int>(leftTop_.x), static_cast<int>(leftTop_.y),
		static_cast<int>(rightTop_.x), static_cast<int>(rightTop_.y),
		static_cast<int>(leftBottom_.x), static_cast<int>(leftBottom_.y),
		static_cast<int>(rightBottom_.x), static_cast<int>(rightBottom_.y),
		0, 0,
		1, 1,
		gh_,
		0xFFFFFF00 + alpha_
	);
}

bool PlayerReviveParticle::GetDelFlag()
{
	return del_;
}
