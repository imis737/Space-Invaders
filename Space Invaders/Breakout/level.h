//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: level.h
// Description	: Level declaration file
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
//class CBall;
class CPaddle;
class CBrick;
class CBullet;
class CFPSCounter;
class CBackGround;

class CLevel
{
	// Member Functions
public:
	CLevel();
	virtual ~CLevel();

	virtual bool Initialise(int _iWidth, int _iHeight);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	CPaddle* GetPaddle() const;

	int GetBricksRemaining() const;

	bool AddPlayerBullet();
	bool AddAlienBullet(float _fX, float _fY);

protected:
  //  void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
 //   void ProcessBallPaddleCollision();
 //   void ProcessBallBrickCollision();
	void ProcessBulletBrickCollision();
	void ProcessBulletPlayerCollision(CBullet* _pBullet);

	void ProcessCheckForWin();

  //  void ProcessBallBounds();

	void UpdateScoreText();
	void DrawScore();
	void DrawFPS();

	void SetBricksRemaining(int _i);

private:
	CLevel(const CLevel& _kr);
	CLevel& operator= (const CLevel& _kr);

	// Member Variables
public:

protected:
	CBackGround* m_pBackground;
 //   CBall* m_pBall;
	CPaddle* m_pPaddle;
	std::vector<CBrick*> m_vecBricks;
	std::vector<CBullet*> m_vecAlienBullets;
	CBullet* m_pPlayerBullet;
	CFPSCounter* m_fpsCounter;

	int m_iWidth;
	int m_iHeight;

	int m_iBricksRemaining;

	int m_iAlienSpeed;
	bool m_bReverseAliens;

	std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
