#include "./FirstSet.h"

#include<string.h>

void first(const Rule *pHead, SetList *pFirstSetList);
Set* get_set(SetList *pSetList, const char *pName)
{
    int i =0;
    for(i = 0 ; i < pSetList->nSetCnt; i++)
    {
        Set *currSet = pSetList->sets[i];
        if(0 == strcmp(currSet->Name, pName))
        {
            return currSet;
        }
    }
    return NULL;
}

// 添加一个 set 到 SetList
// pSetList，SetList指针
// pName，集合名称字符串指针
void add_one_set(SetList *pSetList, const char *pName)
{
    if(pSetList->nSetCnt == 32)
        return;
    
    Set *s = (Set*)malloc(sizeof(Set));
    strcpy(s->Name, pName);
    memset(s->Terminal,0,sizeof(s->Terminal));
    s->nTerminalCnt = 0;

    pSetList->sets[pSetList->nSetCnt] = s;
    pSetList->nSetCnt++;
}

// 添加一个终结符到set
// 成功返回：1，不成功返回：0
int add_terminal_to_set(Set *pSet, const char *pTerminal)
{
    if(pSet->nTerminalCnt == 32) return 0;
    strcpy(pSet[pSet->nTerminalCnt], pTerminal);
    pSet->nTerminalCnt++;
    return 1;
}

// 
int add_set_to_set(Set *pDestSet, const Set *pSrcSet);
int set_has_void(const Set *pSet);

