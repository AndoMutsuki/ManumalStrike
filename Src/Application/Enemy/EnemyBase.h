#pragma once

class EnemyBase
{
public:

	EnemyBase();

	virtual ~EnemyBase();

	virtual void Draw();

	//�G�̈ʒu���Z�b�g
	void SetEnemyPos(const Math::Vector2& _pos);

	//�_���[�W�����炤
	void SetDamage(const int _damage);

	//�����Ă��邩�̃t���O
	const bool GetAliveFlg();

	//�G�̃f�[�^��h���N���X�œ���
	void SetEnemyData(const enemyData& _enemyData);

	//�G�̃f�[�^�̃Q�b�^�[
	virtual const enemyData& GetEnemyData()const;

	//�G�̃f�[�^�̃Q�b�^�[(�ύX�\)
	virtual enemyData& GetEnemyDataKinetic();

	//�摜�f�[�^��h���N���X�œ���
	void SetTexData(const textureData& _texData);

private:

	//�摜�̊g�嗦���Z�o
	const float CalculateTexMagnification();

	enemyData	m_enemyData;
	textureData	m_texData;
};