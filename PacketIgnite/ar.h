#ifndef __AR_H__
#define __AR_H__

#pragma once

#include "HeapMng.h"

typedef	struct	tagPLAY_ACCOUNT
{
	TCHAR	lpszAccount[36];
	SYSTEMTIME	m_stLogin;
	TCHAR	lpAddr[16];
}
PLAY_ACCOUNT;


class CAr
{
public:
	CAr(void *lpBuf = NULL, unsigned int nBufSize = 0);
	~CAr();

	// Flag values
	enum { store = 0, load = 1 };
	enum { nGrowSize = 16384 };

	static CHeapMng*	m_pHeapMng;


	// Attributes
	BOOL	IsLoading()	const;
	BOOL	IsStoring()	const;

	// Operations
	void	Read(void* lpBuf, unsigned int nSize);
	void	Write(const void* lpBuf, unsigned int nSize);
	void	CheckBuf(unsigned int nSize);
	void	Reserve(unsigned int nSize);
	void	Flush(void);
	void	ReelIn(unsigned int uOffset);

	// reading and writing strings
	void WriteString(LPCTSTR lpsz);
	LPTSTR ReadString(LPTSTR lpsz);
	LPTSTR ReadString(LPTSTR lpsz, int nBufSize);

	LPBYTE	GetBuffer(int* pnBufSize);
	unsigned long	GetOffset(void);
	/*
	void	Copy( CAr & ar );
	CAr& operator = ( CAr & ar );
	*/
	// insertion operations
	CAr& operator<<(BYTE by);
	CAr& operator<<(WORD w);
	CAr& operator<<(LONG l);
	CAr& operator<<(DWORD dw);
	CAr& operator<<(float f);
	CAr& operator<<(double d);

	CAr& operator<<(int i);
	CAr& operator<<(short w);
	CAr& operator<<(char ch);
	CAr& operator<<(unsigned u);

	// extraction operations
	CAr& operator>>(BYTE& by);
	CAr& operator>>(WORD& w);
	CAr& operator>>(DWORD& dw);
	CAr& operator>>(LONG& l);
	CAr& operator>>(float& f);
	CAr& operator>>(double& d);

	CAr& operator>>(int& i);
	CAr& operator>>(short& w);
	CAr& operator>>(char& ch);
	CAr& operator>>(unsigned& u);

#ifdef __CLIENT
#ifdef _DEBUG
	static	DWORD	s_dwHdrPrev;
	static	DWORD	s_dwHdrCur;
#endif	// _DEBUG
#endif	// __CLIENT

protected:
	BYTE	m_nMode;	// read or write
	unsigned int	m_nBufSize;
	LPBYTE	m_lpBufCur;
	LPBYTE	m_lpBufMax;
	LPBYTE	m_lpBufStart;
	BYTE	m_lpBuf[nGrowSize];
};
/*
inline void CAr::Copy( CAr & ar )
{	ASSERT( IsLoading() );	ASSERT( ar.IsStoring() );	ar.Write( (void*)m_lpBufStart, (unsigned int)( m_lpBufMax - m_lpBufStart ) );	}
inline CAr& CAr::operator = ( CAr & ar )
{	ar.Copy( *this );	return *this;	}
*/
inline BOOL CAr::IsLoading() const
{
	return (m_nMode & CAr::load) != 0;
}
inline BOOL CAr::IsStoring() const
{
	return (m_nMode & CAr::load) == 0;
}

inline CAr& CAr::operator<<(int i)
{
	return CAr::operator<<((LONG)i);
}
inline CAr& CAr::operator<<(unsigned u)
{
	return CAr::operator<<((LONG)u);
}
inline CAr& CAr::operator<<(short w)
{
	return CAr::operator<<((WORD)w);
}
inline CAr& CAr::operator<<(char ch)
{
	return CAr::operator<<((BYTE)ch);
}
inline CAr& CAr::operator<<(BYTE by)
{
	CheckBuf(sizeof(BYTE));
	*(UNALIGNED BYTE*)m_lpBufCur = by; m_lpBufCur += sizeof(BYTE); return *this;
}
inline CAr& CAr::operator<<(WORD w)
{
	CheckBuf(sizeof(WORD));
	*(UNALIGNED WORD*)m_lpBufCur = w; m_lpBufCur += sizeof(WORD); return *this;
}
inline CAr& CAr::operator<<(LONG l)
{
	CheckBuf(sizeof(LONG));
	*(UNALIGNED LONG*)m_lpBufCur = l; m_lpBufCur += sizeof(LONG); return *this;
}
inline CAr& CAr::operator<<(DWORD dw)
{
	CheckBuf(sizeof(DWORD));
	*(UNALIGNED DWORD*)m_lpBufCur = dw; m_lpBufCur += sizeof(DWORD); return *this;
}
inline CAr& CAr::operator<<(float f)
{
	CheckBuf(sizeof(float));
	*(UNALIGNED FLOAT*)m_lpBufCur = *(FLOAT*)&f; m_lpBufCur += sizeof(float); return *this;
}
inline CAr& CAr::operator<<(double d)
{
	CheckBuf(sizeof(double));
	*(UNALIGNED double*)m_lpBufCur = *(double*)&d; m_lpBufCur += sizeof(double); return *this;
}

inline CAr& CAr::operator>>(int& i)
{
	return CAr::operator>>((LONG&)i);
}
inline CAr& CAr::operator>>(unsigned& u)
{
	return CAr::operator>>((LONG&)u);
}
inline CAr& CAr::operator>>(short& w)
{
	return CAr::operator>>((WORD&)w);
}
inline CAr& CAr::operator>>(char& ch)
{
	return CAr::operator>>((BYTE&)ch);
}

#define	CAR_SAFE_READ( type, value )	\
	if( m_lpBufCur + sizeof(type) <= m_lpBufMax )	\
		{	value	= *(UNALIGNED type*)m_lpBufCur;	m_lpBufCur += sizeof(type);	}	\
	else	\
		{	value	= (type)0;	m_lpBufCur	= m_lpBufMax;	}	\
	return *this

inline CAr& CAr::operator>>(BYTE& by)
{
	CAR_SAFE_READ(BYTE, by);
}
inline CAr& CAr::operator>>(WORD& w)
{
	CAR_SAFE_READ(WORD, w);
}
inline CAr& CAr::operator>>(DWORD& dw)
{
	CAR_SAFE_READ(DWORD, dw);
}
inline CAr& CAr::operator>>(float& f)
{
	CAR_SAFE_READ(float, f);
}
inline CAr& CAr::operator>>(double& d)
{
	CAR_SAFE_READ(double, d);
}
inline CAr& CAr::operator>>(LONG& l)
{
	CAR_SAFE_READ(LONG, l);
}

inline CAr& operator<<(CAr & ar, __int64 i)
{
	ar.Write(&i, sizeof(__int64));	return ar;
}

inline CAr& operator>>(CAr & ar, __int64& i)
{
	ar.Read(&i, sizeof(__int64));	return ar;
}

/*
inline CAr& operator<<(CAr & ar, CRect rect)
{	ar.Write( &rect, sizeof(CRect) );	return ar;	}

inline CAr& operator>>(CAr & ar, CRect & rect)
{	ar.Read( &rect, sizeof(CRect) );	return ar;	}
*/

inline CAr& operator<<(CAr & ar, RECT rect)
{
	ar.Write(&rect, sizeof(RECT));	return ar;
}

inline CAr& operator>>(CAr & ar, RECT & rect)
{
	ar.Read(&rect, sizeof(RECT));	return ar;
}

inline CAr& operator<<(CAr & ar, PLAY_ACCOUNT pa)
{
	ar.Write(&pa, sizeof(PLAY_ACCOUNT));	return ar;
}

inline CAr& operator>>(CAr & ar, PLAY_ACCOUNT& pa)
{
	ar.Read(&pa, sizeof(PLAY_ACCOUNT));	return ar;
}

inline unsigned long CAr::GetOffset(void)
{
	return(m_lpBufCur - m_lpBufStart);
}

#endif //__AR_H__
