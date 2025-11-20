# 🌌 ECHOES OF VALOR  
### Text 기반으로 울려 퍼지는 용기의 메아리  
팀명: **1000110101**  
팀원: 임승우, 전예성

---

## 📘 프로젝트 소개

**Echoes of Valor**는 C 언어(C89 표준)로 제작된 **콘솔 기반 Text RPG**입니다.  
객체지향 없이 **파일 입출력만으로 모든 데이터를 관리**하며,  
전투·마을·던전·스탯·자동세이브·개발자모드까지 포함한 구조화된 RPG 시스템입니다.

본 프로젝트는 게임적인 재미뿐 아니라  
콘솔 환경에서의 **데이터 무결성 관리**, **상태 저장 구조**,  
**텍스트 UI 설계 능력**을 평가받기 위해 설계되었습니다.

---

## 🗂️ 프로젝트 구조
```plaintext
EchoesOfValor/
│
├── main.c
│
├── core/
│ ├── game.c / game.h
│ ├── scene_title.c / scene_title.h
│ ├── scene_menu.c / scene_menu.h
│ ├── scene_create.c / scene_create.h
│ ├── scene_town.c / scene_town.h
│ ├── scene_battle.c / scene_battle.h
│ ├── scene_admin.c / scene_admin.h
│
├── entity/
│ ├── player.c / player.h
│ ├── monster.c / monster.h
│ ├── battle_logic.c / battle_logic.h
│
├── system/
│ ├── fileio.c / fileio.h
│ ├── save.c / save.h
│ ├── utils.c / utils.h
│
├── data/
│ ├── player.txt
│ ├── monster_slime.txt
│ ├── monster_goblin.txt
│ ├── temp.txt
│ ├── log.txt
│
└── README.md
```


---

## ⚙️ 개발 환경

- **언어**: C (C89)
- **구동 방식**: 콘솔 기반 Text RPG  
- **컴파일러**: gcc / clang / MinGW 모두 지원  
- **데이터 관리**: 텍스트 파일 기반 (player.txt, monster.txt, temp.txt)

---

## 🎮 게임 기능

### 🗡️ 1. 캐릭터 생성  
- 직업 선택: 전사 / 마법사 / 궁수  
- 이름 입력 → 이름 확인 → 캐릭터 확정  
- 생성된 캐릭터는 `player.txt`에 저장

### 🌲 2. 마을 시스템  
- 훈련소 (스탯 상승)  
- 상점 (아이템 구매)  
- 휴식 (HP/MP 회복)  
- 장비 정비  
- 던전 출발  

### ⚔️ 3. 전투 시스템  
- 공격 / 스킬 / 방어 / 도망  
- 각 전투 정보는 실시간으로 `temp.txt`에 기록  
- 전투 로그는 `log.txt`에 기록  
- 승리 시 EXP/Gold 획득, 레벨업 진행

### 🧪 4. 개발자 모드 (숨겨진 기능)  
비밀코드 **1000110101** 입력 시 활성화  
- 몬스터 데이터 확인  
- 캐릭터 스탯 조정  
- 테스트 전투  
- 시스템 로그 열람  
- FPS 모니터링 (간단한 성능 확인용)

---

## 💾 세이브 & 로드 시스템

### ✔ 자동 세이브  
- 씬 이동 시 & 전투 종료 시 자동 저장  
- 데이터 손상 대비 temp 파일을 통한 무결성 보장

### ✔ 로드 시스템  
- `player.txt`를 기반으로 캐릭터 상태 복구  
- 저장 파일이 손상되었을 경우 자동 복구 로직 실행

---

## 📄 데이터 파일 구조 (예시)

### 📌 player.txt
name:Sia
job:mage
level:3
hp:120
mp:40
gold:270
exp:55


### 📌 monster_slime.txt
name:Slime
hp:70
attack:12
exp:25
gold:10


### 📌 temp.txt
battle_state=running
player_hp=95
monster_hp=38


---

## 🖥️ UI Mockup (목업 일부 예시)

=================================================
ECHOES OF VALOR
[ 1 ] 새로 시작하기
[ 2 ] 불러오기
[ 3 ] 설정
[ 4 ] 게임 종료
개발자 모드 ▸ 1000110101

=================================================
[ 마을 : 평온의 숲 ]
[ 1 ] 훈련소
[ 2 ] 상점
[ 3 ] 휴식
[ 4 ] 장비 정비
[ 5 ] 던전으로 출발
현재 상태: LV.3 | HP 120/120 | MP 40/40 | Gold 270


---

## 🔧 빌드 & 실행 방법

### 🔹 Linux / macOS
```bash
gcc main.c core/*.c entity/*.c system/*.c -o valor
./valor


gcc main.c core/*.c entity/*.c system/*.c -o valor.exe
valor.exe

향후 확장 기능

텍스트 타이핑 연출(한 글자씩 출력)

난이도 시스템 (쉬움/보통/어려움)

직업별 고유 스킬 추가

로그 분석 시스템 고도화

라이선스

본 프로젝트는 학습 및 교육 목적으로 제작되었으며,
배포 및 상업적 이용은 허용되지 않습니다.