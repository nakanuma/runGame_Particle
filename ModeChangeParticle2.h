#pragma once
#include<Vector2.h>
#include<Novice.h>

class ModeChangeParticle2
{
public:
	ModeChangeParticle2(Vector2 pos);
	~ModeChangeParticle2();

	void Update(Vector2 moveAmount);
	void Draw(int scroll);

	bool GetDelFlag();

private:
	int gh_ = Novice::LoadTexture("./images/ModeChangeParticle2.png");

	Vector2 pos_; // 中心座標

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	float size_ = 30.0f;
	int alpha_ = 255;
	bool del_ = false;
};



