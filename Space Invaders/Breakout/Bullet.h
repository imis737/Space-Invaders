//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: Bullet.h
// Description	: Bullet declaration file
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz and francis.kir7286@mediadesign.school.nz
//

#pragma once

#if !defined(__BULLET_H__)
#define __BULLET_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBullet : public CEntity
{
	// Member Functions
public:
	CBullet();
	virtual ~CBullet();

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float _fX);
	void SetVelocityY(float _fY);

	float GetRadius() const;
	bool GetFromAlien() const;
	void SetFromAlien(bool _bFromAlien);

protected:

private:
	CBullet(const CBullet& _kr);
	CBullet& operator= (const CBullet& _kr);

	// Member Variables
public:

protected:
	float m_fVelocityX;
	float m_fVelocityY;
	bool m_bfromAlien;

private:

};


#endif    // __Bullet_H__
