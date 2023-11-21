#pragma once
#include "BackGroundParticle.h"
#include <list>
#include "Util.h"

class BackGroundEmitter
{
public:
	BackGroundEmitter();
	~BackGroundEmitter();

	void Update(Vector2 playerPos);
	void Draw(int scroll);

	void Emit(Vector2 playerPos);

private:
	std::list<BackGroundParticle> particleList;

	int leftRangeX_ = 320;
	int rightRangeX_ = 960;

	int rangeY_ = 756;

	int timer_ = 0;
	int interval_ = 4;
};

