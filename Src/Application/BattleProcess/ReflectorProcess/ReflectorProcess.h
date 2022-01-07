#pragma once

class ReflectorProcess
{
public: 

	ReflectorProcess();

	~ReflectorProcess();

	void Update(const bool _shotPrepareFlg);

	void Draw()const;

	const float GetLength()const;

	const float GetAng()const;

	const Math::Vector2& GetPos()const;

private:

	//位置の計算
	void CalculatePos();

	//右に動く処理
	void MoveRight();

	//左に動く処理
	void MoveLeft();

	//角度の計算
	void CalculateAng();

	//右端が傾く処理
	void LeanRight();

	//左端が傾く処理
	void LeanLeft();

	//行列の合成
	void CalculateMatrix();

	float			m_length;			//長さ
	float			m_ang;				//角度
	Math::Vector2	m_pos;				//位置
	Math::Matrix	m_mat;				//行列
	const float		m_moveSpeed = 15.0f;//動くスピード
	const float		m_angSpeed = 3.0f;	//傾けるスピード
	KdTexture*		m_tex = nullptr;	//画像
};