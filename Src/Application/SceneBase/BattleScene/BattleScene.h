#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	//�}�E�X�̏���
	void ProcessMouse();

	//�}�j���}������
	void FirstShot();

	

	//�}�j���}���̏ꏊ�̌v�Z
	void CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale);	

	//�ړ�����x�N�g���̌����̌v�Z
	void CalculateManumalMoveVec(Math::Vector2& _vec, const float _ang);	

	//�ǂɓ������Ă��邩�A�܂�����������̌v�Z
	const bool CalculateHitWall(Math::Vector2& _pos, float& _ang, const float& _scale);	

	//���˔ɓ������Ă��邩�A�܂�����������̌v�Z
	const bool CalculateHitReflector(Math::Vector2& _pos, float& _ang, const float& _scale);

	//���˔̈ʒu�̌v�Z
	void CalculateReflectorPos();	

	//���˔̊p�x�̌v�Z
	void CalculateReflectorAng();	

	//���˔̍s��̌v�Z
	void CalculateReflectorMatrix();	

	//�I�u�W�F�N�g�ɂԂ����Ă�����A�܂�Ԃ����ʒu�����Ƃ߂�
	void CalculateHitPos(float& _standardPos, const float& _objectPos);	

	//�I�u�W�F�N�g�ɂԂ����Ă�����A�܂�Ԃ����p�x�����Ƃ߂�
	void CalculateHitAng(float& _standardAng, const float& _objectAng);	

	//�p�x���󂷂����Ƃ��̂��߂̒���
	void AdjustmentHitAng(float& _standardAng);

	float m_scale;
	float m_ang1;
	float m_power1;

	Math::Matrix m_mat1;
	Math::Matrix m_mat2;

	Math::Vector2 m_pos1;
	Math::Vector2 m_pos2;

	Math::Vector2 m_moveVec1;
	Math::Rectangle m_rec1;
	Math::Color m_color1;

	//���
	KdTexture* m_arrowTex;
	Math::Vector2 m_firstArrowPos;
	float m_arrowScale;
	const float m_arrowScaleMax = 20.0f;
	const float m_arrowScaleMin = 3.0f;

	//���˔�
	const float m_moveSpeed = 15.0f;
	const float m_angSpeed = 1.0f;
	float m_reflectorScale;
	float m_reflectorAng;
	Math::Vector2 m_reflectorPos;
	Math::Matrix m_reflectorMat;
	int m_reflectedMoveTime;
	static const int m_reflectedMoveTimeMax = 10;

	KdTexture* m_tex = nullptr;
	KdTexture* m_reflectorTex = nullptr;

	//�}�E�X�֌W
	POINT m_mousePos;
	POINT m_baseMousePos;

};
