//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: brick.cpp
// Description	: Implementation file for the aliens
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "Brick.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBrick::CBrick()
	: m_bHit(false)
	, m_bMystery(false)
{

}

CBrick::~CBrick()
{

}

bool
CBrick::Initialise()
{
	if (!m_bMystery)
	{
		VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));
	}
	else
	{
		VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK)); // TODO: Change IDB_BRICKSPRITE and IDB_BRICKMASK to the mystery images
	}
	
	
	return (true);
}

void
CBrick::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CBrick::Process(float _fDeltaTick)
{

	//float fHalfBrick = m_pSprite->GetWidth() / 2;

	//iCurrentX = 30;


	//if (iCurrentX > _iWidth - pBrick->GetWidth())
	//{
	//	iCurrentX = kiStartX;
	//	iCurrentY += 20;
	//}

	////So when the position of the bricks is less than the 



	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void
CBrick::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CBrick::IsHit() const
{
	return (m_bHit);
}

void
CBrick::SetMystery(bool _b)
{
	m_bMystery = _b;
}

bool
CBrick::IsMystery() const
{
	return (m_bMystery);
}
