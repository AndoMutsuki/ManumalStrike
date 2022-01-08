#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	MouseProcess*				m_mouseProcess = nullptr;
	FirstShotProcess*			m_firstShotProcess = nullptr;
	ReflectorProcess*			m_reflectorProcess = nullptr;
	HitManumalwallProcess*		m_hitManumalwallProcess = nullptr;
	HitManumalReflectorProcess* m_hitManumalReflectorProcess = nullptr;
	std::vector<ManumalBase*>	m_manumalList;

	//�I�u�W�F�N�g�ɂԂ����Ă�����A�܂�Ԃ����p�x�����Ƃ߂�
	void CalculateHitAng(float& _standardAng, const float& _objectAng);	

	//�}�j���}�����m�̓����蔻��
	void ManumalMutualCollision();

	//�}�j���}���ƓG�̓����蔻��
	void ManumalEnemyCollision();

	//�G�t�F�N�g�̕`��
	void EffectDraw();

	float m_scale;
	float m_ang1;
	float m_power1;

	float m_ang2;
	float m_ang3;
	float m_power2;
	float m_power3;

	Math::Matrix m_mat1;
	Math::Matrix m_mat2;
	Math::Matrix m_mat3;

	Math::Vector2 m_pos1;
	Math::Vector2 m_pos2;
	Math::Vector2 m_pos3;

	Math::Vector2 m_moveVec1;
	Math::Rectangle m_rec1;
	Math::Color m_color1;

	Math::Vector2 m_moveVec2;
	Math::Vector2 m_moveVec3;

	//���
	KdTexture* m_arrowTex;
	bool m_arrowFlg;
	Math::Vector2 m_firstArrowPos;
	float m_arrowAng;
	Math::Matrix m_arrowMat;
	float m_arrowScale;
	const float m_arrowScaleFixed = 20.0f;
	const float m_arrowScaleMax = 20.0f;
	const float m_arrowScaleMin = 1.0f;

	//���˔�
	float m_reflectorLength;
	float m_reflectorAng;
	Math::Vector2 m_reflectorPos;
	Math::Matrix m_reflectorMat;

	KdTexture* m_tex = nullptr;
	KdTexture* m_reflectorTex = nullptr;

	Effekseer::EffectRef m_effect;
	Effekseer::Handle m_handle;
	bool m_effectFlg;

	//�}�E�X�֌W
	POINT m_mousePos;
	POINT m_baseMousePos;

};
