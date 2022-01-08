#pragma once

using namespace ManumalStrikeNamespace;

class ManumalBase
{
public:

	ManumalBase();

	virtual ~ManumalBase();

	virtual void Draw();

	//�s��̌v�Z
	virtual void CalculateMatrix();

	//�ړ�����x�N�g���̌v�Z
	virtual void CalculateMoveVec();

	//���ۂɈړ����鏈��
	virtual void MoveProcess();

	//�}�j���}���̃f�[�^��h���N���X�œ���
	void SetManumalData(const manumalData& _manumalData);

	//�}�j���}���̃f�[�^�̃Q�b�^�[
	virtual const manumalData& GetManumalData()const;

	//�}�j���}���̃f�[�^�̃Q�b�^�[(�ύX�\)
	virtual manumalData& GetManumalDataKinetic();

	//�摜�f�[�^��h���N���X�œ���
	void SetTexData(const manumalTextureData& _texData);

	//�ʒu�̃Z�b�^�[
	virtual void SetPos(const Math::Vector2& _pos);

private:

	//�摜�̊g�嗦���Z�o
	const float CalculateTexMagnification();

	manumalData			m_manumalData;
	manumalTextureData	m_texData;

};