//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: backbuffer.cpp
// Description	: Backbuffer implementation file
// Author		: Isaac Missingham and Francis Kirkpatrick
// Mail			: isaac.mis6876@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This include
#include "BackBuffer.h"

// Static Variables

// Static Function Prototypes

// Implementation


/***********************
* Equals: Backbuffer Constructor
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: void
********************/
CBackBuffer::CBackBuffer()
: m_hWnd(0)
, m_hDC(0)
, m_hSurface(0)
, m_hOldObject(0)
, m_iWidth(0)
, m_iHeight(0)
{

}


/***********************
* Equals: Backbuffer destructor
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: void
********************/
CBackBuffer::~CBackBuffer()
{
    SelectObject(m_hDC, m_hOldObject);

    DeleteObject(m_hSurface);
    DeleteObject(m_hDC);
}


/***********************
* Equals: Initialises the backbuffer
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: HWND handle to main window, int width, and int height
* @return: bool
********************/
bool
CBackBuffer::Initialise(HWND _hWnd, int _iWidth, int _iHeight)
{
    m_hWnd = _hWnd;

    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    HDC hWindowDC = ::GetDC(m_hWnd);

    m_hDC = CreateCompatibleDC(hWindowDC);

    m_hSurface = CreateCompatibleBitmap(hWindowDC, m_iWidth, m_iHeight);

    ReleaseDC(m_hWnd, hWindowDC);

    m_hOldObject = static_cast<HBITMAP>(SelectObject(m_hDC, m_hSurface));

    HBRUSH brushWhite = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
    HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(m_hDC, brushWhite));

    Rectangle(m_hDC, 0, 0, m_iWidth, m_iHeight);

    SelectObject(m_hDC, oldBrush);

    return (true);
}


/***********************
* Equals: Clears the backbuffer
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: void
********************/
void
CBackBuffer::Clear()
{
    HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(GetBFDC(), GetStockObject(LTGRAY_BRUSH)));

    Rectangle(GetBFDC(), 0, 0, GetWidth(), GetHeight());

    SelectObject(GetBFDC(), hOldBrush);
}


/***********************
* Equals: Gets the HDC of the backbuffer
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: HDC
********************/
HDC
CBackBuffer::GetBFDC() const
{
    return (m_hDC);
}


/***********************
* Equals: Gets the HDC of the backbuffer
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: HDC
********************/
int 
CBackBuffer::GetWidth() const
{
    return (m_iWidth);
}


/***********************
* Equals: Returns the member variable height
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: int
********************/
int 
CBackBuffer::GetHeight() const
{
    return (m_iHeight);
}


/***********************
* Equals: Blts the backbuffer onto the display
* @author: Isaac Missingham & Francis Kirkpatrick
* @parameter: Nothing
* @return: void
********************/
void 
CBackBuffer::Present()
{
    HDC hWndDC = ::GetDC(m_hWnd);

    BitBlt(hWndDC, 0, 0, m_iWidth, m_iHeight, m_hDC, 0, 0, SRCCOPY);

    ReleaseDC(m_hWnd, hWndDC);
}

