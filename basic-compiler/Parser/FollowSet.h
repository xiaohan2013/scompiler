#ifndef __FOLLOW_SET_H__
#define __FOLLOW_SET_H__

#include "./Common.h"

void first(const Rule *pHead, SetList *pFirstSetList);
void follow(const Rule *pHead, SetList *pFollowSetList, SetList *pFirstSetList);
Set* get_set(SetList *pSetList, const char *pName);
void add_one_set(SetList *pSetList, const char *pName);
int add_terminal_to_set(Set *pSet, const char *pTerminal);
int add_set_to_set(Set *pDestSet, const Set *pSrcSet);
int set_has_void(const Set *pSet);


#endif /* __FOLLOW_SET_H__ */
