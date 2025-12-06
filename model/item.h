#ifndef MODEL_ITEM_H
#define MODEL_ITEM_H

// 소비 / 재료 / 판매만 되는 아이템 구조
typedef struct {
    int id;                 // 고유 번호
    char name[32];          // 이름
    char description[128];  // 설명 
    int price;              // 구매/판매 가격 (상점에서 사용)
    int heal;               // 회복 수치 (소모품이 아닐 경우 0)
} ItemData;

#endif