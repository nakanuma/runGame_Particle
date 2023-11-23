#pragma once
#include<Vector2.h>
#include<Novice.h>

class nameParticle
{
public:
	nameParticle();
	~nameParticle();

	void Update();
	void Draw();

	bool GetDelFlag();

private:
	/*int gh_ = Novice::LoadTexture("./images/nameParticle.png");*/

	Vector2 pos_; // íÜêSç¿ïW

	Vector2 leftTop_;
	Vector2 rightTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;

	float size_;
	bool del_ = false;
};

