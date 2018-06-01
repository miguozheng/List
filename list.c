#include "list.h"
#define SOUND_LIST_END 30
Node SoundListMem[SOUND_LIST_END+1];
UINT8 ListMenMan[SOUND_LIST_END+1];


/*�ڴ�����*/  
Node *listMallocMem(void)
{
	UINT8 i,length = SOUND_LIST_END+1;
	Node *pnoderet = NULL;
	
	for(i = 0;i< SOUND_LIST_END+1;i++){
		if(0 == ListMenMan[i]){
			ListMenMan[i] = 1;
			pnoderet = &SoundListMem[i];
			pnoderet->MemIterm = i;
			break;
		}
	}
	
	return pnoderet;
}
/*��ȡ����ͷ*/  
Node *listGetHead(DList *pdlist)
{
	DList *tempdlist = pdlist;
	Node *pnode = NULL;
	
	if(NULL != tempdlist){
		pnode = tempdlist->Head;
	}
	
	return pnode;
}
/*��ȡ����β*/  
Node *listGetTial(DList *pdlist)
{
	DList *tempdlist = pdlist;
	Node *pnode = NULL;
	
	if(NULL != tempdlist){
		pnode = tempdlist->Tail;
	}
	
	return pnode;
}
/*��ȡ������*/  
UINT8 listGetSize(DList *plist)  
{  
    return plist->Size;  
}  
/*��ȡ�����Ƿ�Ϊ��*/  
UINT8 listIsEmpty(DList *plist)  
{  
    if((listGetSize(plist) == 0) && (listGetTial(plist) == listGetHead(plist))){
    	return 1;  
    }else{  
        return 0;  
    }
} 
/*��ȡ�ڵ�Next*/  
Node *listGetNext(Node *pnode)
{
	return pnode->Next;
}
/*��ȡ�ڵ�Previous*/  
Node *listGetPrevious(Node *pnode)
{
	return pnode->Previous;
}
/*��ȡ�ڵ�����*/ 
void *listNodeGetData(Node *pnode)
{
	return pnode->Data;
}
/*ɾ�������нڵ�*/ 
void listNodeRemove(DList *pdlist,Node *pnode)
{
	DList *tempdlist = pdlist;
	Node *pnodetemp = pnode,*pnext = NULL,*pprev = NULL;
	
	if((NULL != tempdlist) && (NULL != pnodetemp)){
		if(tempdlist->Size){
			pnext = pnodetemp->Next;
			pprev = pnodetemp->Previous;
			if(NULL != pprev){
				pprev->Next = pnext;
			}else{
				tempdlist->Head = pnext;
				if(NULL != pnext){
					pnext->Previous = NULL;
				}
			}
			if(NULL != pnext){
				pnext->Previous = pprev;
			}else{
				tempdlist->Tail = pprev;
				pprev->Next = NULL;
			}
			pnodetemp->Data = NULL;
			pnodetemp->Previous = NULL;
			pnodetemp->Next = NULL;
			if(0xFF != pnodetemp->MemIterm){
				ListMenMan[pnodetemp->MemIterm] = 0;
			}
			pnodetemp->MemIterm = 0xFF;
			tempdlist->Size--;
		}
	}
}
/*�ڵ�ǰ����ڵ�*/ 
void listNodeInsertBefore(DList *pdlist,Node *posnode,Node *pnodein)
{
	DList *tempdlist = pdlist;
	Node *pposnode = posnode,*pprev = NULL,*pnodeintemp = pnodein;
	
	if(NULL != tempdlist){
		pprev = pposnode->Previous;
	
		if(NULL != pprev){
			pprev->Next = pnodeintemp;
		}else{
			if(pposnode == tempdlist->Head){
				tempdlist->Head = pnodeintemp;
			}
		}
		pnodeintemp->Previous = pprev;
		pnodeintemp->Next = pposnode;
		posnode->Previous = pnodeintemp;
		tempdlist->Size++;
	}
}
/*�ڵ�����ڵ�*/ 
void listNodeInsertAfter(DList *pdlist,Node *posnode,Node *pnodein)
{
	DList *tempdlist = pdlist;
	Node *pposnode = posnode,*pnext = NULL,*pnodeintemp = pnodein;
	
	if(NULL != tempdlist){
		pnext = pposnode->Next;
		pposnode->Next = pnodeintemp;
		if(NULL != pnext){
			pnext->Previous = pnodeintemp;
		}else{
			if(pposnode == tempdlist->Tail){
				tempdlist->Tail = pnodeintemp;
			}
		}
		pnodeintemp->Previous = pposnode;
		pnodeintemp->Next = pnext;
		tempdlist->Size++;
	}
}
/*�������ڵ�*/ 
void listNodeInsertQueue(DList *pdlist,Node *pnodein)
{
	DList *tempdlist = pdlist;
	Node *pnodeintemp = pnodein,*nodetail = NULL;
	
	if(listIsEmpty(tempdlist)){
		tempdlist->Tail = pnodeintemp;
		tempdlist->Head->Next = pnodeintemp;
		pnodeintemp->Previous = tempdlist->Head;
		pdlist->Size++;
	}else{
		nodetail = listGetTial(tempdlist);
		if(NULL != nodetail){
			listNodeInsertAfter(tempdlist,nodetail,pnodeintemp);
		}
	}
}
/*�����ڵ�*/ 
Node *listNodeMake(void *pdata)
{
	Node *pnoderet = NULL,*nodetemp = NULL;
	
	nodetemp = listMallocMem();
	if(NULL != nodetemp){
		nodetemp->Data = pdata;
		nodetemp->Previous = NULL;
		nodetemp->Next = NULL;
	}
	pnoderet = nodetemp;
	
	return pnoderet;
}
/*�����ʼ��*/ 
void listInit(DList *dlist,UINT8 maxsize)
{
	DList *plist = dlist;
	Node *nodehead = NULL;
	
	nodehead = listNodeMake(NULL);
	if(NULL != nodehead){
		plist->Head = nodehead;
		plist->Tail = nodehead;
		plist->Size = 0;
		plist->MaxSize = maxsize;
	}
}