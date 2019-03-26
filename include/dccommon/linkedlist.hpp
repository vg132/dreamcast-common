#ifndef __E89DA9F5B45F9AFCED7CA__LINKEDLIST__HPP__
#define __E89DA9F5B45F9AFCED7CA__LINKEDLIST__HPP__

#include <kos.h>

class CListItem
{
private:
	void *m_Data;
	CListItem *m_Next;
public:
	void* GetData(){return(m_Data);};
	void SetData(void *data){m_Data=data;};
	void SetNext(CListItem *next){m_Next=next;};
	CListItem* GetNext(){return(m_Next);};
	~CListItem()
	{
		if(m_Next!=NULL)
			delete m_Next;
	};
	CListItem()
	{
		m_Data=NULL;
		m_Next=NULL;
	};
};

class CLinkedList
{
private:
	CListItem *m_First, *m_Last, *m_Current;
	int m_Items;
public:
	void AddItem(void *data);
	int GetItems(){return(m_Items);};
	CListItem* GetFirst(){return(m_First);};
	CLinkedList(void);
	~CLinkedList(void);
};

#endif // __E89DA9F5B45F9AFCED7CA__LINKEDLIST__HPP__
