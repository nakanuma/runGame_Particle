#include "PlayerReviveEmitter.h"

PlayerReviveEmitter::PlayerReviveEmitter()
{
}

PlayerReviveEmitter::~PlayerReviveEmitter()
{
}

void PlayerReviveEmitter::Update()
{
	// パーティクル全ての更新処理を呼ぶ
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlagがtrueだったら
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // eraseしなかった場合のみイテレーターをインクリメント
		}
	}
}

void PlayerReviveEmitter::Draw()
{
	// パーティクル全ての描画処理を呼ぶ
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void PlayerReviveEmitter::Emit(Vector2 centerPos)
{
	float angle_ = 11.25f * (float)M_PI / 180.f; // 一度で32個生成するため

	for (int i = 0; i < 32; i++) {
		float particleX = centerPos.x + radius_ * cosf(i * angle_);
		float particleY = centerPos.y + radius_ * sinf(i * angle_);

		float velocityX = 1 * cosf(i * angle_) - 0 * sinf(i * angle_);
		float velocityY = 1 * sinf(i * angle_) + 0 * cosf(i * angle_);

		PlayerReviveParticle newParticle = PlayerReviveParticle({ particleX,particleY }, { velocityX,velocityY });
		particleList.push_back(newParticle);
	}
}
