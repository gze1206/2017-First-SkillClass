#pragma once
class cMainGame
{
private:
	ST_PC_VERTEX	m_aVertex[3];
	D3DXVECTOR3		m_vPos;
	float			m_fAngle;
	float			m_fScaleFactor;
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
};

