#include "ModeChangeEmitter2.h"
#include "Util.h"

ModeChangeEmitter2::ModeChangeEmitter2()
{
}

ModeChangeEmitter2::~ModeChangeEmitter2()
{
}

void ModeChangeEmitter2::Update(Vector2 moveAmount)
{
	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update(moveAmount);

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void ModeChangeEmitter2::Draw(int scroll)
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw(scroll);
	}
}

void ModeChangeEmitter2::Emit(Vector2 centerPos)
{
	float particleX = static_cast<float>(Random((int)centerPos.x - range_, (int)centerPos.x + range_));
	float particleY = static_cast<float>(Random((int)centerPos.y - range_, (int)centerPos.y + range_));

	ModeChangeParticle2 newParticle = ModeChangeParticle2({ particleX,particleY });
	particleList.push_back(newParticle);
}
