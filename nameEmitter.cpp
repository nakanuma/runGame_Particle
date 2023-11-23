#include "nameEmitter.h"

nameEmitter::nameEmitter()
{
}

nameEmitter::~nameEmitter()
{
}

void nameEmitter::Update()
{
	// �p�[�e�B�N���S�Ă̍X�V�������Ă�
	for (auto itr = particleList.begin(); itr != particleList.end();) {
		itr->Update();

		// DelFlag��true��������
		if (itr->GetDelFlag()) {
			itr = particleList.erase(itr);
		} else {
			itr++; // erase���Ȃ������ꍇ�̂݃C�e���[�^�[���C���N�������g
		}
	}
}

void nameEmitter::Draw()
{
	// �p�[�e�B�N���S�Ă̕`�揈�����Ă�
	for (auto& particle : particleList) {
		particle.Draw();
	}
}

void nameEmitter::Emit()
{
}
