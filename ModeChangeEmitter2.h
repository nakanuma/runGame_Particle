#pragma once
#include "ModeChangeParticle2.h"
#include <list>

class ModeChangeEmitter2
{
public:
	ModeChangeEmitter2();
	~ModeChangeEmitter2();

	void Update(Vector2 moveAmount);
	void Draw(int scroll);

	void Emit(Vector2 centerPos);

private:
	std::list<ModeChangeParticle2> particleList;

	int range_ = 150; // 出現範囲
};

