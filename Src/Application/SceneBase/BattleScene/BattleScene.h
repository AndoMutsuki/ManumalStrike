#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	void CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power);	//マニュマルの場所の計算

	void CalculateManumalMoveVec(Math::Vector2& _vec, const float _ang);	//移動するベクトルの向きの計算

	const bool CalculateHitWall(Math::Vector2& _pos, float& _ang);	//壁に当たっているか、また当たった後の計算

	void CalculateReflectorAng();	//反射板の角度の計算

	float m_scale;
	float m_ang1;
	float m_power1;

	float m_reflectorAng;	//反射板の角度

	Math::Matrix m_mat1;
	Math::Matrix m_mat2;

	Math::Vector2 m_pos1;
	Math::Vector2 m_pos2;

	Math::Vector2 m_moveVec1;
	Math::Rectangle m_rec1;
	Math::Color m_color1;

	KdTexture* m_tex = nullptr;

};
