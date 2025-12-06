#ifndef MODEL_EQUIPMENT_H
#define MODEL_EQUIPMENT_H

// 장비 부위 enum
typedef enum {
    EQUIP_WEAPON = 1,   // 무기
    EQUIP_HELMET,       // 투구
    EQUIP_ARMOR,        // 상의
    EQUIP_PANTS,        // 하의
    EQUIP_GLOVES,       // 장갑
    EQUIP_BOOTS         // 신발
} EquipmentSlot;

// 장비 아이템 구조 (무기/방어구/장신구 등)
typedef struct {
    int id;                 // 고유 번호
    char name[32];          // 장비 이름

    EquipmentSlot slot;     // 문자열 대신 enum 사용

    int attack;             // 공격력 증가
    int defense;            // 방어력 증가

    char lore[128];         // 배경 설명
    int price;              // 상점 판매/구매 가격
} EquipmentData;

#endif