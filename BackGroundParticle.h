#pragma once
#include<Vector2.h>
#include<Novice.h>

class BackGroundParticle
{
public:
	BackGroundParticle(Vector2 pos, Vector2 velocity);
	~BackGroundParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/backGroundParticle.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	Vector2 velocity_;
	float size_ = 8;
	int alpha_ = 192;
	bool del_ = false;
};

