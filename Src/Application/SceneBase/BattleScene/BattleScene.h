#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	//マウスの処理
	void ProcessMouse();

	//マニュマル発射
	void FirstShot();

	

	//マニュマルの場所の計算
	void CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale);	

	//移動するベクトルの向きの計算
	void CalculateManumalMoveVec(Math::Vector2& _vec, const float _ang);	

	//壁に当たっているか、また当たった後の計算
	const bool CalculateHitWall(Math::Vector2& _pos, float& _ang, const float& _scale);	

	//反射板に当たっているか、また当たった後の計算
	const bool CalculateHitReflector(Math::Vector2& _pos, float& _ang, const float& _scale);

	//反射板の位置の計算
	void CalculateReflectorPos();	

	//反射板の角度の計算
	void CalculateReflectorAng();	

	//反射板の行列の計算
	void CalculateReflectorMatrix();	

	//オブジェクトにぶつかっていたら、折り返した位置をもとめる
	void CalculateHitPos(float& _standardPos, const float& _objectPos);	

	//オブジェクトにぶつかっていたら、折り返した角度をもとめる
	void CalculateHitAng(float& _standardAng, const float& _objectAng);	

	//角度が浅すぎたときのための調節
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

	//矢印
	KdTexture* m_arrowTex;
	Math::Vector2 m_firstArrowPos;
	float m_arrowScale;
	const float m_arrowScaleMax = 20.0f;
	const float m_arrowScaleMin = 3.0f;

	//反射板
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

	//マウス関係
	POINT m_mousePos;
	POINT m_baseMousePos;

};
