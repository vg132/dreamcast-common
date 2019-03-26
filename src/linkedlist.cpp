#include "dccommon/linkedlist.hpp"

CLinkedList::CLinkedList(void)
{
	m_First=NULL;
	m_Last=NULL;
	m_Items=0;
}

CLinkedList::~CLinkedList(void)
{
	if(m_First!=NULL)
		delete m_First;
}

void CLinkedList::AddItem(void *data)
{
	CListItem *li=new CListItem();
	li->SetData(data);
	if(m_First==NULL)
		m_First=li;
	else
		m_Last->SetNext(li);
	m_Items++;
	m_Last=li;
}
