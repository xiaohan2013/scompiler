#include "./T2P.h"

#include <string.h>


typedef struct __AddressEntry {
    AddrKind Kind;
    const char *Content;
}AddressEntry;

typedef struct __TCodeEntry 
{
    TOpKind Kind;
    AddressEntry Addr1, Addr2, Addr3
}TCodeEntry;


static const TCodeEntry TCodeTable[] = {
    {t_rd, {string, "x"} },
    {t_mul, {string, "x"}, {intconst, "2"}, {string, "t1"} },
    {t_asn, {string, "t1"}, {string, "x"} },
    {t_if_f, {string, "x"}, {string, "L1"} },
    {t_wri, {string, "x"} },
    {t_lab, {string, "L1"} },
    {t_halt},
};

// 将三地址码转化为 P-代码
// TCodeList，三地址码列表指针
// PCodeList，P—代码列表指针
void T2P(TCode *TCodeList, PCode *PCodeList)
{
    int TIndex = 0; // 三地址码列表游标
    int PIndex = 0; // P-代码列表游标

    int size = sizeof(TCodeList) / sizeof(TCodeList[0]);

    int i;
    for(i = 0 ; i < size; i++)
    {
        
    }
}


// 初始化地址
// pEntry, 初始化地址结构体
// pAddr,  地址指针
void init_address(const AddressEntry *pEntry, Address *pAddr)
{
    pAddr->Kind = pEntry->Kind;
    switch (pAddr->Kind)
    {
    case empty:
        break;

    case intconst:
        pAddr->Value = atoi(pEntry->Content);
        break;

    case string:
        strcpy(pAddr->Name, pEntry->Content);
        break;
    }
}

// 初始化三地址码列表
void init_tcode_list(TCode *pTCodeList)
{
    int i;
    int EntryCount = sizeof(TCodeTable) / sizeof(TCodeTable[0]);

    for(i = 0; i < EntryCount; i++)
    {
        pTCodeList[i].Kind = TCodeTable[i].Kind;

        init_address(&TCodeTable[i].Addr1, &pTCodeList[i].Addr1);
        init_address(&TCodeTable[i].Addr2, &pTCodeList[i].Addr2);
        init_address(&TCodeTable[i].Addr3, &pTCodeList[i].Addr3);
    }
}

int main(int argc, char **argv)
{
    TCode TCodeList[MAX_CODE_COUNT];  // 三地址码列表
    PCode PCodeList[MAX_CODE_COUNT]; // P-代码列表

    // 将三地址码列表和P-代码列表的内容清空
    memset(TCodeList, 0, sizeof(TCodeList));
    memset(PCodeList, 0, sizeof(PCodeList));

    // 初始化三地址码列表
    init_tcode_list(TCodeList);

    // 将三地址码转化为 P-代码
    T2P(TCodeList, PCodeList);

    return 0;
}