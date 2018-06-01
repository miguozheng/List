#ifndef LIST_H_
#define LIST_H_
typedef unsigned char   UINT8;  /*unsigned 8 bit definition */
typedef unsigned short  UINT16; /*unsigned 16 bit definition*/
typedef unsigned long   UINT32; /*unsigned 32 bit definition*/
typedef signed char     INT8;   /*signed 8 bit definition */
typedef short           INT16;  /*signed 16 bit definition*/
typedef long int        INT32;  /*signed 32 bit definition*/
#define NULL    ((void *)0)
typedef struct node
{
	void *Data;
	UINT8 MemIterm;
	struct node *Previous;
	struct node *Next;
}Node;
typedef struct  
{  
	Node *Head;     /*ָ��ͷ�ڵ�*/  
	Node *Tail;     /*ָ��β�ڵ�*/  
    UINT8 Size;  	/*�����С*/ 
    UINT8 MaxSize;  /*��󳤶�*/ 
}DList; 

void listInit(DList *dlist,UINT8 maxsize);
void *listNodeGetData(Node *pnode);
Node *listGetHead(DList *pdlist);
Node *listGetTial(DList *pdlist);
UINT8 listIsEmpty(DList *plist); 
UINT8 listGetSize(DList *plist); 
Node *listGetNext(Node *pnode);
Node *listGetPrevious(Node *pnode);
void listNodeRemove(DList *pdlist,Node *pnode);
void listNodeInsertBefore(DList *pdlist,Node *posnode,Node *pnodein);
void listNodeInsertAfter(DList *pdlist,Node *posnode,Node *pnodein);
Node *listNodeMake(void *pdata);
void listNodeInsertQueue(DList *pdlist,Node *pnodein);
#endif