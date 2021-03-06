
#pragma once

class QLinkArray
{
	class QLinkNode
	{
	public:
		int nPrev;
		int	nNext;
	public:
		QLinkNode() { nPrev = nNext = 0; }
	};
private:
	QLinkNode*	pNode;
	int			m_nCount;
	int			m_nSize;
public:
	QLinkArray() { pNode = NULL; m_nCount = 0; m_nSize = 0;}
	~QLinkArray();
	int GetCount() { return m_nCount; }
	bool			Init(int nSize);
	void			Clear();

	void			Remove(int nIdx);
	void			Insert(int nIdx);
	void			RemoveAll();
	void			InsertAll();
	
	inline int		GetNext(int nIdx) const 
	{ 
		if (nIdx < 0 || nIdx >= m_nSize)
			return 0;

		if(pNode) 
			return pNode[nIdx].nNext; 
		else 
			return 0;
	}

	inline int		GetPrev(int nIdx) const 
	{ 
		if (nIdx < 0 || nIdx >= m_nSize)
			return 0;

		if(pNode) 
			return pNode[nIdx].nPrev; 
		else 
			return 0;
	}
};

inline QLinkArray::~QLinkArray()
{
	Clear();
}

inline void QLinkArray::Clear()
{
	if (pNode) 
	{
		m_nCount = 0;
		m_nSize = 0;
		delete [] pNode;
		pNode = NULL;
	}
}

inline bool QLinkArray::Init(int nSize)
{
	if (nSize == m_nSize)
	{
		RemoveAll();
	}
	else
	{
		Clear();
		pNode = new QLinkNode[nSize];
		if (pNode)
			m_nSize = nSize;
	}
	return (pNode != NULL);
}

inline void QLinkArray::Remove(int nIdx)
{
	if (nIdx <= 0 || nIdx >= m_nSize)
	{
		g_DebugLog("[error]Remove invalid node: index %d, size %d", nIdx, m_nSize);
		return;
	}

	if ((pNode[nIdx].nNext == 0 && pNode[0].nPrev != nIdx) || (pNode[nIdx].nPrev == 0 && pNode[0].nNext != nIdx))
	{
		g_DebugLog("[error]Node:%d Remove twice", nIdx);
		return;
	}

	pNode[pNode[nIdx].nPrev].nNext = pNode[nIdx].nNext;
	pNode[pNode[nIdx].nNext].nPrev = pNode[nIdx].nPrev;
	pNode[nIdx].nNext = 0;
	pNode[nIdx].nPrev = 0;
	m_nCount--;
}

inline void QLinkArray::Insert(int nIdx)
{
	if (nIdx <= 0 || nIdx >= m_nSize)
	{
		g_DebugLog("[error]Insert invalid node: index %d, size %d", nIdx, m_nSize);
		return;
	}

	if (pNode[nIdx].nNext != 0 || pNode[nIdx].nPrev != 0)
	{
		g_DebugLog("[error]Node:%d Insert twice", nIdx);
		return;
	}

	pNode[nIdx].nNext = pNode[0].nNext;
	pNode[pNode[0].nNext].nPrev = nIdx;
	pNode[0].nNext = nIdx;
	pNode[nIdx].nPrev = 0;
	m_nCount++;
}

inline void QLinkArray::InsertAll()
{
	if (m_nSize != m_nCount)
	{
		for (int i = 0; i < m_nSize; i++)
		{
			pNode[i].nNext = i + 1;
			pNode[i].nPrev = i - 1;
		}
		pNode[0].nPrev = 0;
		pNode[m_nSize - 1].nNext = 0;
		m_nCount = m_nSize;
	}
}

inline void QLinkArray::RemoveAll()
{
	if (m_nCount)
	{
		int nNext = pNode[0].nNext;
		while(m_nCount > 0)
		{
			int nNextNext = pNode[nNext].nNext;
			pNode[nNext].nNext = 0;
			pNode[nNext].nPrev = 0;
			nNext = nNextNext;
			m_nCount --;
		}
		pNode[0].nNext = 0;
		pNode[0].nPrev = 0;
	}
}


