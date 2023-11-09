#pragma once
#include "MyStruct.h"
#include <Novice.h>

class FlyingParticle
{
public:
	FlyingParticle(Vector2<float> centerPos);
	~FlyingParticle();

	void Update();
	void Draw();

	bool GetDelFlag(); // パーティクルが消えているかを取得する

private:
	int gh_ = Novice::LoadTexture("./flyingParticle.png");

	Vector2<float> pos_; // 中心座標

	Vector2<float> leftTop_;
	Vector2<float> rightTop_;
	Vector2<float> leftBottom_;
	Vector2<float> rightBottom_;

	Vector2<float> Velocity_ = { 8.0f,0.0f };
	float size_ = 42.0f;
	int alpha_ = 128;
	bool del_ = false;
};

