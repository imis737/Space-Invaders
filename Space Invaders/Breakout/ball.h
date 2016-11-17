//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: ball.h
// Description	: Ball declaration file, used for bullet 
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz and francis.kir7286@mediadesign.school.nz
//

#pragma once

#if !defined(__BALL_H__)
#define __BALL_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBall : public CEntity
{
    // Member Functions
public:
    CBall();
    virtual ~CBall();

    virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityX, float _fVelocityY);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    float GetVelocityX() const;
    float GetVelocityY() const;
    void SetVelocityX(float _fX);
    void SetVelocityY(float _fY);

    float GetRadius() const;

protected:

private:
    CBall(const CBall& _kr);
    CBall& operator= (const CBall& _kr);

    // Member Variables
public:

protected:
    float m_fVelocityX;
    float m_fVelocityY;

private:

};


#endif    // __BALL_H__
