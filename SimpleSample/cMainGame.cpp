#include "DXUT.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	: m_vPos(0, 0, 0)
	, m_fAngle(0.0f)
	, m_fScaleFactor(1.0f)
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Setup()
{
	m_aVertex[0].p = D3DXVECTOR3(0, 0, 0);
	m_aVertex[0].c = D3DCOLOR_XRGB(255, 0, 0);
	m_aVertex[1].p = D3DXVECTOR3(0, 1, 0);
	m_aVertex[1].c = D3DCOLOR_XRGB(0, 255, 0);
	m_aVertex[2].p = D3DXVECTOR3(1, 0, 0);
	m_aVertex[2].c = D3DCOLOR_XRGB(0, 0, 255);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	D3DXMATRIX matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS); // 단위행렬
	D3DXMatrixIdentity(&matR); // 단위행렬
	D3DXMatrixIdentity(&matT); // 단위행렬

	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_fScaleFactor += 0.1f;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_fScaleFactor -= 0.1f;
	}
	D3DXMatrixScaling(&matS, m_fScaleFactor, m_fScaleFactor, m_fScaleFactor);
	
	//m_fAngle += 0.1f;
	D3DXMatrixRotationY(&matR, m_fAngle);
	
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_vPos.x -= 0.1f;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_vPos.x += 0.1f;
	}
	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	
	//D3DXMatrixIdentity(&matWorld); // 단위행렬\

	matWorld = matS * matR * matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld); // 디바이스에게 월드매트릭스 전달
	
	D3DXVECTOR3 vEye(0, 0, -5); 
	D3DXVECTOR3 vAt(0, 0, 0);
	D3DXVECTOR3 vUp(0, 1, 0);

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp); // 뷰 매트릭스 생성 함수
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView); // 디바이스에게 뷰매트릭스 전달

	RECT rc;
	GetClientRect(DXUTGetHWND(), &rc);
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cMainGame::Render()
{
	g_pD3DDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, m_aVertex, sizeof(ST_PC_VERTEX));
	//D3DPT_LINELIST 선
}