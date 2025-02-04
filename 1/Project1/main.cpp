// [1]Intrude Header
#include <stdio.h>
#include <conio.h>

// [2]Define Value

// [3]define queue value
enum
{
	MONSTER_PLAYER,
	MONSTER_SLIME,
	MONSTER_MAX
};
// [4]here for structure
typedef struct {
	int hp;
	int maxHp;
	int mp;
	int maxMp;
	char name[4 * 3 + 1];
	char aa[256];
} CHARACTER;

enum
{
	CHARACTER_PLAYER,
	CHARACTER_MONSTER,
	CHARACTER_MAX
};
	
// [5]define variable
CHARACTER monsters[MONSTER_MAX] =
{
	//MONSTER_PLAYER
	{
		15,
		15,
		15,
		15,
		"Warrior",
	},
	//MONSTER_SLIME
	{
		3,
		3,
		0,
		0,
		"Slime",
		"/TT|\n"
		"~~~~"
	},
};
//define integral

CHARACTER characters[CHARACTER_MAX];

// [6]Function

void Init()
{
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

void DrawBattleScreen()
{
	printf("%s\n", characters[CHARACTER_PLAYER].name);
	printf("HP: %d/%d MP:%d/%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);
	printf("\n");
	printf("%s", characters[CHARACTER_MONSTER].aa);
	printf("(HP: %d/%d)\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);
	printf("\n");
}

void Battle(int _monster)
{
	characters[CHARACTER_MONSTER] = monsters[_monster];

	DrawBattleScreen();

	printf("%s이[가] 나타났다!\n", characters[CHARACTER_MONSTER].name);
	_getch();
}

int main()
{
	//call for battle
	Init();
	Battle(MONSTER_SLIME);
}