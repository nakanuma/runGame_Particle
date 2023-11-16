#pragma once
#include <Novice.h>
#include "Vector2.h"

class PlayerReviveParticle
{
public:
	PlayerReviveParticle(Vector2 pos,Vector2 velocity);
	~PlayerReviveParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/playerRevive.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float speed_ = 6.0f;
	bool del_ = false;
	int size_ = 8;
	int timer_ = 0;
	int delTime_ = 27;
	int alpha_ = 40;
};

