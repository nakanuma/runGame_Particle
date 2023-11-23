#pragma once
#include "nameParticle.h"
#include <list>

class nameEmitter
{
public:
	nameEmitter();
	~nameEmitter();

	void Update();
	void Draw();

	void Emit();

private:
	std::list<nameParticle> particleList;
};

