//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Game.h"
#include "Paddle.h"
#include "Brick.h"
#include "Bullet.h"
//#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

//#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPaddle(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
	while (m_vecBricks.size() > 0)
	{
		CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];

		m_vecBricks.pop_back();

		delete pBrick;
	}

	delete m_pPaddle;
	m_pPaddle = 0;

	//delete m_pBall;
	//m_pBall = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
	m_iWidth = _iWidth;
	m_iHeight = _iHeight;

	m_iAlienSpeed = 100;
	m_bReverseAliens = false;

	//const float fBallVelX = 200.0f;
	//const float fBallVelY = 75.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//m_pBall = new CBall();
	//VALIDATE(m_pBall->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f, fBallVelX, fBallVelY));

	m_pPaddle = new CPaddle();
	VALIDATE(m_pPaddle->Initialise());

	// Set the paddle's position to be centered on the x, 
	// and a little bit up from the bottom of the window.
	m_pPaddle->SetX(_iWidth / 2.0f);
	m_pPaddle->SetY(_iHeight - ( 1.5 * m_pPaddle->GetHeight()));

	const int kiNumBricks = 50;
	const int kiStartX = 150;
	const int kiGap = 10;

	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;

	for (int i = 0; i < kiNumBricks; ++i)
	{
		CBrick* pBrick = new CBrick();
		VALIDATE(pBrick->Initialise());

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

		if (iCurrentX > _iWidth-pBrick->GetWidth()-100)
		{
			iCurrentX = kiStartX;
			iCurrentY += 20;
		}

		m_vecBricks.push_back(pBrick);
	}

	SetBricksRemaining(kiNumBricks);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

	return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		m_vecBricks[i]->Draw();
	}

	for (unsigned int i = 0; i < m_vecAlienBullets.size(); ++i)
	{
		m_vecAlienBullets[i]->Draw();
	}
	if (m_pPlayerBullet != NULL)
		m_pPlayerBullet->Draw();

	m_pPaddle->Draw();
	//m_pBall->Draw();

	DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		AddPlayerBullet();
	}

	m_pBackground->Process(_fDeltaTick);
	//m_pBall->Process(_fDeltaTick);
	if (m_pPlayerBullet != NULL)
	{
		m_pPlayerBullet->Process(_fDeltaTick);
		if (m_pPlayerBullet->GetY() < 0)
		{
			delete m_pPlayerBullet;
			m_pPlayerBullet = NULL;
		}
	}
	m_pPaddle->Process(_fDeltaTick);
	//ProcessBallWallCollision();
	//ProcessPaddleWallCollison();
	//ProcessBallPaddleCollision();
	//ProcessBallBrickCollision();
	if (m_pPlayerBullet != NULL)
		ProcessBulletBrickCollision();

	ProcessCheckForWin();
	//ProcessBallBounds();

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (m_vecBricks[i]->IsHit())
			continue;
		m_vecBricks[i]->Process(_fDeltaTick);									
		m_vecBricks[i]->SetX(m_vecBricks[i]->GetX() + m_iAlienSpeed*_fDeltaTick);	//move aliens horizontally
		if (rand() % 100000 < 1)														// 0.001% chance of firing a projectile at the player this frame
			AddAlienBullet(m_vecBricks[i]->GetX(), m_vecBricks[i]->GetY());				// Creates a projectile on the current alien
		if (m_vecBricks[i]->GetX() > m_iWidth - m_vecBricks[i]->GetWidth() / 2)		// check if the aliens are too far to the right
			m_bReverseAliens = true;													// reverse aliens
		else if (m_vecBricks[i]->GetX() < m_vecBricks[i]->GetWidth() / 2)			// check if the aliens are too far to the left
			m_bReverseAliens = true;													// reverse aliens
	}
	if (m_bReverseAliens)
	{
		m_iAlienSpeed *= -1;
		m_bReverseAliens = false;
		for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
		{
			m_vecBricks[i]->SetY(m_vecBricks[i]->GetY() + 25);
			if (m_vecBricks[i]->GetY() > 725)
				CGame::GetInstance().GameOverLost();
			m_vecBricks[i]->SetX(m_vecBricks[i]->GetX() + m_iAlienSpeed*_fDeltaTick*5);
		}
	}
	for (unsigned int i = 0; i < m_vecAlienBullets.size(); ++i)
	{
		m_vecAlienBullets[i]->Process(_fDeltaTick);
		ProcessBulletPlayerCollision(m_vecAlienBullets[i]);
		if (m_vecAlienBullets[i]->GetY() > 800)
		{
			delete m_vecAlienBullets[i];
			m_vecAlienBullets.erase(m_vecAlienBullets.begin() + i);
		}
	}
   
	
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPaddle* 
CLevel::GetPaddle() const
{
	return (m_pPaddle);
}

//void 
//CLevel::ProcessBallWallCollision()
//{
//	float fBallX = m_pBall->GetX();
//	float fBallY = m_pBall->GetY();
//	float fBallW = m_pBall->GetWidth();
//	float fBallH = m_pBall->GetHeight();
//
//	float fHalfBallW = fBallW / 2;
//	float fHalfBallH = fBallH / 2;
//
//	if (fBallX < fHalfBallW) //represents the situation when the ball has hit the left wall
//	{
//		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //reverse the ball's x velocity
//	}
//	else if (fBallX > m_iWidth - fHalfBallW) //represents the situation when the ball has hit the right wall
//	{
//		m_pBall->SetVelocityX(m_pBall->GetVelocityX() * -1); //reverse the ball's x velocity direction
//	}
//
//	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
//	{
//		m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //reverse the ball's y velocity
//	}

//#ifdef CHEAT_BOUNCE_ON_BACK_WALL
//	if (fBallY  > m_iHeight - fHalfBallH)  //represents the situation when the ball has hit the bottom wall
//	{
//		m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //reverse the ball's y velocity
//	}
//#endif //CHEAT_BOUNCE_ON_BACK_WALL
//}




//void
//CLevel::ProcessBallPaddleCollision()
//{
//	float fBallR = m_pBall->GetRadius();
//
//	float fBallX = m_pBall->GetX();
//	float fBallY = m_pBall->GetY(); 
//
//	float fPaddleX = m_pPaddle->GetX();
//	float fPaddleY = m_pPaddle->GetY();
//
//	float fPaddleH = m_pPaddle->GetHeight();
//	float fPaddleW = m_pPaddle->GetWidth();
//
//	if ((fBallX + fBallR > fPaddleX - fPaddleW / 2) && //ball.right > paddle.left
//		(fBallX - fBallR < fPaddleX + fPaddleW / 2) && //ball.left < paddle.right
//		(fBallY + fBallR > fPaddleY - fPaddleH / 2) && //ball.bottom > paddle.top
//		(fBallY - fBallR < fPaddleY + fPaddleH / 2))  //ball.top < paddle.bottom
//	{
//		m_pBall->SetY((fPaddleY - fPaddleH / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
//		m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1); //Reverse ball's Y direction
//	}
//}

//void
//CLevel::ProcessBallBrickCollision()
//{
//	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
//	{
//		if (!m_vecBricks[i]->IsHit())
//		{
//			float fBallR = m_pBall->GetRadius();
//
//			float fBallX = m_pBall->GetX();
//			float fBallY = m_pBall->GetY(); 
//
//			float fBrickX = m_vecBricks[i]->GetX();
//			float fBrickY = m_vecBricks[i]->GetY();
//
//			float fBrickH = m_vecBricks[i]->GetHeight();
//			float fBrickW = m_vecBricks[i]->GetWidth();
//
//			if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
//				(fBallX - fBallR < fBrickX + fBrickW / 2) &&
//				(fBallY + fBallR > fBrickY - fBrickH / 2) &&
//				(fBallY - fBallR < fBrickY + fBrickH / 2))
//			{
//				//Hit the front side of the brick...
//				m_pBall->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
//				m_pBall->SetVelocityY(m_pBall->GetVelocityY() * -1);
//				m_vecBricks[i]->SetHit(true);
//
//				SetBricksRemaining(GetBricksRemaining() - 1);
//			}
//		}
//	}
//}

void
CLevel::ProcessBulletBrickCollision()
{
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!m_vecBricks[i]->IsHit())
		{
			float fBulletR = m_pPlayerBullet->GetRadius();

			float fBulletX = m_pPlayerBullet->GetX();
			float fBulletY = m_pPlayerBullet->GetY();

			float fBrickX = m_vecBricks[i]->GetX();
			float fBrickY = m_vecBricks[i]->GetY();

			float fBrickH = m_vecBricks[i]->GetHeight();
			float fBrickW = m_vecBricks[i]->GetWidth();

			if ((fBulletX + fBulletR > fBrickX - fBrickW / 2) &&
				(fBulletX - fBulletR < fBrickX + fBrickW / 2) &&
				(fBulletY + fBulletR > fBrickY - fBrickH / 2) &&
				(fBulletY - fBulletR < fBrickY + fBrickH / 2))
			{
				//Hit the front side of the brick...
				delete m_pPlayerBullet;
				m_pPlayerBullet = 0;
				m_vecBricks[i]->SetHit(true);

				SetBricksRemaining(GetBricksRemaining() - 1);
				return;
			}
		}
	}
}

void
CLevel::ProcessBulletPlayerCollision(CBullet* _pBullet)
{
	float fBulletR = _pBullet->GetRadius();

	float fBulletX = _pBullet->GetX();
	float fBulletY = _pBullet->GetY();

	float fPaddleX = m_pPaddle->GetX();
	float fPaddleY = m_pPaddle->GetY();

	float fPaddleH = m_pPaddle->GetHeight();
	float fPaddleW = m_pPaddle->GetWidth();

	if ((fBulletX + fBulletR > fPaddleX - fPaddleW / 2) && //bullet.right > paddle.left
		(fBulletX - fBulletR < fPaddleX + fPaddleW / 2) && //bullet.left < paddle.right
		(fBulletY + fBulletR > fPaddleY - fPaddleH / 2) && //bullet.bottom > paddle.top
		(fBulletY - fBulletR < fPaddleY + fPaddleH / 2))  //bullet.top < paddle.bottom
	{
		CGame::GetInstance().GameOverLost();
	}
}

void
CLevel::ProcessCheckForWin()
{
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!m_vecBricks[i]->IsHit())
		{
			return;
		}
	}

	CGame::GetInstance().GameOverWon();
}

//void
//CLevel::ProcessBallBounds()
//{
//	if (m_pBall->GetX() < 0)
//	{
//		m_pBall->SetX(0);
//	}
//	else if (m_pBall->GetX() > m_iWidth)
//	{
//		m_pBall->SetX(static_cast<float>(m_iWidth));
//	}
//
//	if (m_pBall->GetY() < 0)
//	{
//		m_pBall->SetY(0.0f);
//	}
//	else if (m_pBall->GetY() > m_iHeight)
//	{
//		CGame::GetInstance().GameOverLost();
//		//m_pBall->SetY(static_cast<float>(m_iHeight));
//	}
//}

int 
CLevel::GetBricksRemaining() const
{
	return (m_iBricksRemaining);
}

void 
CLevel::SetBricksRemaining(int _i)
{
	m_iBricksRemaining = _i;
	UpdateScoreText();
}

void
CLevel::DrawScore()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

	const int kiX = 0;
	const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
	
	TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
	m_strScore = "Bricks Remaining: ";

	m_strScore += ToString(GetBricksRemaining());
}


void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}

bool
CLevel::AddPlayerBullet()
{
	if (m_pPlayerBullet == NULL)
	{
		m_pPlayerBullet = new CBullet();
		VALIDATE(m_pPlayerBullet->Initialise(m_pPaddle->GetX(), m_pPaddle->GetY(), 0, -500));
	}
}

bool
CLevel::AddAlienBullet(float _fX, float _fY)
{
	m_vecAlienBullets.push_back(new CBullet());
	m_vecAlienBullets.back()->SetFromAlien(true);
	VALIDATE(m_vecAlienBullets.back()->Initialise(_fX, _fY, 0, 100));
	
}