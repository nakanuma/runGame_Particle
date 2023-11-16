#pragma once
#include "PlayerReviveParticle.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>

class PlayerReviveEmitter
{
public:
	PlayerReviveEmitter();
	~PlayerReviveEmitter();

	void Update();
	void Draw();

	void Emit(Vector2 centerPos);

private:
	std::list<PlayerReviveParticle> particleList;
	
	float radius_ = 150.0f; // プレイヤーの中心からの半径
};

