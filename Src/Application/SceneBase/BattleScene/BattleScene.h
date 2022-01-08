#pragma once

class BattleScene :public SceneBase
{
public:

	BattleScene();

	~BattleScene();

	void Update() override;

	void Draw2D() override;

private:

	MouseProcess*				m_mouseProcess;
	FirstShotProcess*			m_firstShotProcess;
	ReflectorProcess*			m_reflectorProcess;
	std::vector<ManumalBase*>	m_manumalList;

	//マニュマルの場所の計算
	void CalculateManumlPos(Math::Vector2& _pos, Math::Vector2& _vec, float& _ang, float& _power, const float& _scale);	

	//壁に当たっているか、また当たった後の計算
	const bool CalculateHitWall(Math::Vector2& _pos, float& _ang, const float& _scale);	

	//反射板に当たっているか、また当たった後の計算
	const bool CalculateHitReflector(Math::Vector2& _pos, float& _ang, const float& _scale);

	//オブジェクトにぶつかっていたら、折り返した位置をもとめる
	void CalculateHitPos(float& _standardPos, const float& _objectPos);	

	//オブジェクトにぶつかっていたら、折り返した角度をもとめる
	void CalculateHitAng(float& _standardAng, const float& _objectAng);	

	//マニュマル同士の当たり判定
	void ManumalMutualCollision();

	//マニュマルと敵の当たり判定
	void ManumalEnemyCollision();

	//エフェクトの描画
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

	//矢印
	KdTexture* m_arrowTex;
	bool m_arrowFlg;
	Math::Vector2 m_firstArrowPos;
	float m_arrowAng;
	Math::Matrix m_arrowMat;
	float m_arrowScale;
	const float m_arrowScaleFixed = 20.0f;
	const float m_arrowScaleMax = 20.0f;
	const float m_arrowScaleMin = 1.0f;

	//反射板
	float m_reflectorLength;
	float m_reflectorAng;
	Math::Vector2 m_reflectorPos;
	Math::Matrix m_reflectorMat;

	KdTexture* m_tex = nullptr;
	KdTexture* m_reflectorTex = nullptr;

	Effekseer::EffectRef m_effect;
	Effekseer::Handle m_handle;
	bool m_effectFlg;

	//マウス関係
	POINT m_mousePos;
	POINT m_baseMousePos;

};
