//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Bullet.cpp
// Description	: Bullet implementation file
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Includes
#include "Bullet.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBullet::CBullet()
	: m_fVelocityX(0.0f)
	, m_fVelocityY(0.0f)
{

}

CBullet::~CBullet()
{

}

bool
CBullet::Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY)
{
	VALIDATE(CEntity::Initialise(IDB_BALLSPRITE, IDB_BALLMASK));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = _fVelocityX;
	m_fVelocityY = _fVelocityY;

	m_bfromAlien = false;

	return (true);
}

void
CBullet::Draw()
{
	CEntity::Draw();
}

void
CBullet::Process(float _fDeltaTick)
{
	m_fX += m_fVelocityX * _fDeltaTick;
	m_fY += m_fVelocityY * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
}

float
CBullet::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CBullet::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CBullet::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CBullet::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

float
CBullet::GetRadius() const
{
	return (GetWidth() / 2.0f);
}

void
CBullet::SetFromAlien(bool _bFromAlien)
{
	m_bfromAlien = _bFromAlien;
}

bool
CBullet::GetFromAlien() const
{
	return (m_bfromAlien);
}
