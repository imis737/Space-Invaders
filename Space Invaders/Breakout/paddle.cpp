//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: paddle.cpp
// Description	: Implementation file for the player ship
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Paddle.h"
#include "Bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPaddle::CPaddle()
{

}

CPaddle::~CPaddle()
{

}

bool
CPaddle::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

	return (true);
}

void
CPaddle::Draw()
{
	CEntity::Draw();
}

void
CPaddle::Process(float _fDeltaTick)
{
	
	float fHalfPaddleW = m_pSprite->GetWidth() / 2.0;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 800.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 800.0f * _fDeltaTick;
	}
	//else if (GetAsyncKeyState(VK_UP) & 0x8000)
	//{
	//	
	//	CBullet* pBullet = new CBullet();
	//	pBullet->Initialise(m_fX, m_fY, 0, -0.1);	// Should there be a 'VALIDATE' call on this line? 
	//}												//	will require the function to be bool rather than void AFAIK
	if (m_fX - fHalfPaddleW <= 0)
	{
		m_fX = fHalfPaddleW;
	}
	else if (m_fX + fHalfPaddleW >= 785)
	{
		m_fX = 785-fHalfPaddleW;
	}
	
	CEntity::Process(_fDeltaTick);
}
