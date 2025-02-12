// [1]헤더를 인클루드하는 곳
#include <stdio.h> //[1-1]표준 입출력 헤더를 인클루드한다
#include <stdlib.h>//[1-2]표준 라이브러리 헤더를 인클루드한다
#include <string.h>//[1-3]문자열 조작 헤더를 인클루드한다.
#include <time.h> //[1-4]시간 관리 헤더를 인클루드한다.
#include <conio.h> //[1-5]콘솔 입출력 헤더를 인클루드한다.

// [2]상수를 정의함.

// [3]열거 상수를 정의하는 곳

// [3-2] 캐릭터의 종류를 정의한다.
enum
{
	MONSTER_PLAYER,
	MONSTER_SLIME,
	MONSTER_MAX
};
// [3-3] 명령의 종류를 정의한다.
enum
{
	COMMAND_FIGHT,
	COMMAND_SPELL,
	COMMAND_RUN,
	COMMAND_MAX
};
// [4]구조체를 선언하는 곳

// [4-1] 캐릭터의 구조체를 선언한다.
typedef struct {
	int hp;                 // [4-1-1]HP
	int maxHp;              // [4-1-2]최대 HP
	int mp;                 // [4-1-3]MP
	int maxMp;              // [4-1-4]최대 MP
	int attack;             // [4-1-5]공격력
	char name[4 * 3 + 1];   // [4-1-6]이름
	char aa[256];           // [4-1-7]아스키아트
	int command;            // [4-1-8]명령
	int target;             // [4-1-9]공격 대상
} CHARACTER;

enum
{
	CHARACTER_PLAYER,
	CHARACTER_MONSTER,
	CHARACTER_MAX
};
	
// [5[]define variable] 변수를 선언하는 곳

// [5-1] 몬스터 상태의 배열을 선언한다.
CHARACTER monsters[MONSTER_MAX] =
{
	//MONSTER_PLAYER
	{
		15,
		15,
		15,
		15,
		3,
		"Warrior",
	},
	//MONSTER_SLIME
	{
		3,
		3,
		0,
		0,
		2,
		"Slime",
		"/TT|\n"
		"~~~~"
	},
};

// [5-2] 캐릭터의 배열을 선언한다.
CHARACTER characters[CHARACTER_MAX];

// [5-3] 명령의 이름을 선언한다.
char commandNames[COMMAND_MAX][4 * 3 + 1] = {
	"싸운다",
	"주문",
	"도망친다"
};

// [6]함수를 선언하는 곳

// [6-1] 게임을 초기화하는 함수를 선언한다.
void Init()
{
	//[6-1-1] 플레이어의 상태를 초기화한다.
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//[6-2]전투 장면의 화면을 그리는 함수를 선언한다.
void DrawBattleScreen()
{
	// [6-2-1]화면을 클리어한다.
	system("cls");
	//[6-2-2]플레이어의 이름을 표시한다.
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	// [6-2-3]플레이어의 상태를 표시한다.
	printf("HP: %d/%d MP:%d/%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);

	// [6-2-4] 1행 비운다
	printf("\n");

	// [6-2-5] 몬스터의 아스키아트를 그린다
	printf("%s", characters[CHARACTER_MONSTER].aa);

	// [6-2-6] 몬스터의를 표시한다.
	printf("(HP: %d/%d)\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);

	//[6-2-7]1행 비운다
	printf("\n");
}
//[6-3]명령을 선택하는 함수
void SelectCommand()
{
	// [6-3-2]명령을 결정할 때까지 루프
	while (1)
	{
		// [6-3-3]전투 화면을 그리는 함수를 호출한다.
		DrawBattleScreen();
		// [6-3-4] 명령 목록을 표시한다.
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			//[6-3-5]선택중인 명령일시
			if (i == characters[CHARACTER_PLAYER].command)
			{
				// [6-3-6]커서를 그린다.
				printf(">");
			}
			// [6-3-7] 선택중인 명령이 아닐경우
			else
			{
				printf(" ");
			}
			//[6-3-9] 명령의 이름을 표시한다.
			printf("%s\n", commandNames[i]);
		}

		//[6-3-10]입력된 키에 따라 분기된다
		switch (_getch())
		{
		case 'w': //[6-3-11]w키를 누르면
			//[6-3-12]위의 명령으로 바꾼다
			characters[CHARACTER_PLAYER].command--;

			break;
		case 's': //[6-3-13]s키를 누르면
			//[6-3-14]아래의 명령으로 바꾼다.
			characters[CHARACTER_PLAYER].command++;

			break;

		default:	//[6-3-15]상기 이외의 키를 누르면
			return; //[6-3-16]함수를 빠져나온다.
		}

		//[6-3-17]커서를 상하로 루프시킨다
		characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
	}
}

// [6-4] 전투 장면의 함수를 선언한다.
void Battle(int _monster)
{
	//[6-4-1]몬스터의 상태를 초기화한다.
	characters[CHARACTER_MONSTER] = monsters[_monster];

	//[6-4-2]플레이어의 공격 대상을 몬스터로 서정한다.
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

	//[6-4-3]몬스터의 공격 대상을 플레이어로 설정한다.
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	//[6-4-5]전투 장면의 첫 메시지를 표시한다.
	printf("%s이[가] 나타났다!\n", characters[CHARACTER_MONSTER].name);

	//[6-4-6]키보드 입력을 기다린다.
	_getch();

	//[6-4-7] 전투가 끝날 때까지 루프한다.
	while (1)
	{
		//[6-4-8]명령을 선택하는 함수를 호출한다.
		SelectCommand();

		//[6-4-9]각 캐릭터를 반복한다.
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10]전투 장면의 화면을 그리는 함수를 호출한다.
			DrawBattleScreen();

			// [6-4-11]선택된 명령에 따라 분기한다.
			switch (characters[i].command)
			{
			case COMMAND_FIGHT: // [6-4-12]싸운다
			{
				// [6-4-13]공격을 하는 메시지를 표시한다
				printf("%s의 공격!\n", characters[i].name);

				// [6-4-14]키보드 입력을 기다린다
				_getch();

				//[6-4-15] 적에게 주는 데미지를 (계산한다.
				int damage = 1 + rand() % characters[i].attack;

				//[6-4-16] 적에게 대미지를 준다
				characters[characters[i].target].hp -= damage;

				//[6-4-17]적의 HP가 음의 값이 되었는지를 판정한다.
				if (characters[characters[i].target].hp < 0)
				{
					//[6-4-18] 적의 Hp를 0으로 한다.
					characters[characters[i].target].hp = 0;
				}

				//[6-4-19] 전투 장면의 화면을 다시 그리는 함수를 호출한다
				DrawBattleScreen();

				//[6-4-20] 적에게 대미지를 주었따는 메시지를 표시한다.
				printf("%s에게 %d의 데미지!\n",
					characters[characters[i].target].name,
					damage);
				//[6-4-21] 키보드 입력을 기다린다.
				_getch();
				break;
			}
			case COMMAND_SPELL: // Spell the magic
				break;
			case COMMAND_RUN:	// Run away
				break;
			}
			
			// [6-4-39] 공격 대상을 쓰러뜨렸는지 판정한다.
			if (characters[characters[i].target].hp <= 0)
			{
				// [6-4-40] 공격 대상에 따라 처리를 분기시킨다.
				switch (characters[i].target)
				{
					// [6-4-41] 플레이어라면
				case CHARACTER_PLAYER:
					break;

					//[6-4-43] 몬스터라면
				case CHARACTER_MONSTER:

					//[6-4-44] 몬스터의 아스키아트를 아무것도 표시하지 않게 다시 작성한다.
					strcpy_s(characters[characters[i].target].aa, "\n");

					//[6-4-45] 전투 장면의 화면을 다시 그리는 함수를 호출한다.
					DrawBattleScreen();

					// [6-4-46]몬스터를 쓰러뜨린 메시지를 표시한다
					printf("%s을(를) 쓰러뜨렸다!\n", characters[characters[i].target].name);

					break;
				}

				// [6-4-47] 키보드 입력을 기다린다
				_getch();

				//[6-4-48] 전투 장면의 함수를 빠져나간다.
				return;
			}
		}
	}
}

//[6-6] 프로그램의 실행 시작점을 선언한다.
int main()
{
	//[6-6-1]난수를 넣는다.
	srand((unsigned int)time(NULL));
	Init();
	Battle(MONSTER_SLIME);
}