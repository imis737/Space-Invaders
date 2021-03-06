//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: brick.h
// Description	: Brick declaration file, used for aliens
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz and francis.kir7286@mediadesign.school.nz
//
#pragma once

#if !defined(__BRICK_H__)
#define __BRICK_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "sprite.h"

// Types

// Constants

// Prototypes

class CBrick : public CEntity
{
	// Member Functions
public:
	CBrick();
	virtual ~CBrick();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

	void SetMystery(bool _b);
	bool IsMystery() const;

protected:

private:
	CBrick(const CBrick& _kr);
	CBrick& operator= (const CBrick& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;
	bool m_bMystery;

private:

};


#endif    // __BRICK_H__

