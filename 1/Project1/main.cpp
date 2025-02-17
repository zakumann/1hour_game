// [1]����� ��Ŭ����ϴ� ��
#include <stdio.h> //[1-1]ǥ�� ����� ����� ��Ŭ����Ѵ�
#include <stdlib.h>//[1-2]ǥ�� ���̺귯�� ����� ��Ŭ����Ѵ�
#include <string.h>//[1-3]���ڿ� ���� ����� ��Ŭ����Ѵ�.
#include <time.h> //[1-4]�ð� ���� ����� ��Ŭ����Ѵ�.
#include <conio.h> //[1-5]�ܼ� ����� ����� ��Ŭ����Ѵ�.

// [2]����� ������.
#define SPELL_COST (3)	//[2-1] �ֹ��� �Һ� MP�� �����Ѵ�
// [3]���� ����� �����ϴ� ��

// [3-1] ������ ������ �����Ѵ�.
enum
{
	MONSTER_PLAYER, // [3-1-1]�÷��̾�
	MONSTER_SLIME,  // [3-1-2]������
	MONSTER_BOSS,   // [3-1-3]����
	MONSTER_MAX		// [3-1-4]���� ������ ��
};
// [3-2] ĳ������ ������ �����Ѵ�.
enum
{
	CHARACTER_PLAYER,	// [3-2-1]�÷��̾�
	CHARACTER_MONSTER,	// [3-2-2]����
	CHARACTER_MAX		// [3-2-3]ĳ���� ������ ��
};
// [3-3] ����� ������ �����Ѵ�.
enum
{
	COMMAND_FIGHT,	// [3-3-1]�ο��
	COMMAND_SPELL,	// [3-3-2]�ֹ�
	COMMAND_RUN,	// [3-3-3]����ģ��
	COMMAND_MAX		// [3-3-4]����� ���� ��
};
// [4]����ü�� �����ϴ� ��

// [4-1] ĳ������ ����ü�� �����Ѵ�.
typedef struct {
	int hp;                 // [4-1-1]HP
	int maxHp;              // [4-1-2]�ִ� HP
	int mp;                 // [4-1-3]MP
	int maxMp;              // [4-1-4]�ִ� MP
	int attack;             // [4-1-5]���ݷ�
	char name[4 * 3 + 1];   // [4-1-6]�̸�
	char aa[256];           // [4-1-7]�ƽ�Ű��Ʈ
	int command;            // [4-1-8]���
	int target;             // [4-1-9]���� ���
} CHARACTER;
	
// [5] ������ �����ϴ� ��

// [5-1]���� ������ �迭�� �����Ѵ�
CHARACTER monsters[MONSTER_MAX] =
{
	// [5-1-1]MONSTER_PLAYER    �÷��̾�
	{
		100,
		100,
		15,
		15,
		40,
		"Warrior",
	},
	// [5-1-8]MONSTER_SLIME ������
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
	// [5-1-16]MONSTER_BOSS ����
	{
		255,        // [5-1-17]int hp               HP
		255,        // [5-1-18]int maxHp            �ִ� HP
		0,          // [5-1-19]int mp               MP
		0,          // [5-1-20]int maxMp            �ִ� MP
		50,         // [5-1-21]int attack           ���ݷ�
		"����",     // [5-1-22]char name[4 * 3 + 1] �̸�

		// [5-1-23]char aa[256] �ƽ�Ű��Ʈ
		 "����������\n"
		"������٩�壩��"
	}
};

// [5-2] ĳ������ �迭�� �����Ѵ�.
CHARACTER characters[CHARACTER_MAX];

// [5-3] ����� �̸��� �����Ѵ�.
char commandNames[COMMAND_MAX][4 * 3 + 1] = {
	"�ο��",
	"�ֹ�",
	"����ģ��"
};

// [6]�Լ��� �����ϴ� ��

// [6-1] ������ �ʱ�ȭ�ϴ� �Լ��� �����Ѵ�.
void Init()
{
	//[6-1-1] �÷��̾��� ���¸� �ʱ�ȭ�Ѵ�.
	characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//[6-2]���� ����� ȭ���� �׸��� �Լ��� �����Ѵ�.
void DrawBattleScreen()
{
	// [6-2-1]ȭ���� Ŭ�����Ѵ�.
	system("cls");
	//[6-2-2]�÷��̾��� �̸��� ǥ���Ѵ�.
	printf("%s\n", characters[CHARACTER_PLAYER].name);

	// [6-2-3]�÷��̾��� ���¸� ǥ���Ѵ�.
	printf("HP: %d/%d MP:%d/%d\n",
		characters[CHARACTER_PLAYER].hp,
		characters[CHARACTER_PLAYER].maxHp,
		characters[CHARACTER_PLAYER].mp,
		characters[CHARACTER_PLAYER].maxMp);

	// [6-2-4] 1�� ����
	printf("\n");

	// [6-2-5] ������ �ƽ�Ű��Ʈ�� �׸���
	printf("%s", characters[CHARACTER_MONSTER].aa);

	// [6-2-6] �����Ǹ� ǥ���Ѵ�.
	printf("(HP: %d/%d)\n",
		characters[CHARACTER_MONSTER].hp,
		characters[CHARACTER_MONSTER].maxHp);

	//[6-2-7]1�� ����
	printf("\n");
}
//[6-3]����� �����ϴ� �Լ�
void SelectCommand()
{
	// [6-3-1] �÷��̾��� ����� �ʱ�ȭ�Ѵ�
	characters[CHARACTER_PLAYER].command = COMMAND_FIGHT;
	// [6-3-2]����� ������ ������ ����
	while (1)
	{
		// [6-3-3]���� ȭ���� �׸��� �Լ��� ȣ���Ѵ�.
		DrawBattleScreen();
		// [6-3-4] ��� ����� ǥ���Ѵ�.
		for (int i = 0; i < COMMAND_MAX; i++)
		{
			//[6-3-5]�������� ����Ͻ�
			if (i == characters[CHARACTER_PLAYER].command)
			{
				// [6-3-6]Ŀ���� �׸���.
				printf(">");
			}
			// [6-3-7] �������� ����� �ƴҰ��
			else
			{
				printf(" ");
			}
			//[6-3-9] ����� �̸��� ǥ���Ѵ�.
			printf("%s\n", commandNames[i]);
		}

		//[6-3-10]�Էµ� Ű�� ���� �б�ȴ�
		switch (_getch())
		{
		case 'w': //[6-3-11]wŰ�� ������
			//[6-3-12]���� ������� �ٲ۴�
			characters[CHARACTER_PLAYER].command--;

			break;
		case 's': //[6-3-13]sŰ�� ������
			//[6-3-14]�Ʒ��� ������� �ٲ۴�.
			characters[CHARACTER_PLAYER].command++;

			break;

		default:	//[6-3-15]��� �̿��� Ű�� ������
			return; //[6-3-16]�Լ��� �������´�.
		}

		//[6-3-17]Ŀ���� ���Ϸ� ������Ų��
		characters[CHARACTER_PLAYER].command = (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
	}
}

// [6-4] ���� ����� �Լ��� �����Ѵ�.
void Battle(int _monster)
{
	//[6-4-1]������ ���¸� �ʱ�ȭ�Ѵ�.
	characters[CHARACTER_MONSTER] = monsters[_monster];

	//[6-4-2]�÷��̾��� ���� ����� ���ͷ� �����Ѵ�.
	characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;

	//[6-4-3]������ ���� ����� �÷��̾�� �����Ѵ�.
	characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

	//[6-4-5]���� ����� ù �޽����� ǥ���Ѵ�.
	printf("%s��[��] ��Ÿ����!\n", characters[CHARACTER_MONSTER].name);

	//[6-4-6]Ű���� �Է��� ��ٸ���.
	_getch();

	//[6-4-7] ������ ���� ������ �����Ѵ�.
	while (1)
	{
		//[6-4-8]����� �����ϴ� �Լ��� ȣ���Ѵ�.
		SelectCommand();

		//[6-4-9]�� ĳ���͸� �ݺ��Ѵ�.
		for (int i = 0; i < CHARACTER_MAX; i++)
		{
			// [6-4-10]���� ����� ȭ���� �׸��� �Լ��� ȣ���Ѵ�.
			DrawBattleScreen();

			// [6-4-11]���õ� ��ɿ� ���� �б��Ѵ�.
			switch (characters[i].command)
			{
			case COMMAND_FIGHT: // [6-4-12]�ο��
			{
				// [6-4-13]������ �ϴ� �޽����� ǥ���Ѵ�
				printf("%s�� ����!\n", characters[i].name);

				// [6-4-14]Ű���� �Է��� ��ٸ���
				_getch();

				//[6-4-15] ������ �ִ� �������� (����Ѵ�.
				int damage = 1 + rand() % characters[i].attack;

				//[6-4-16] ������ ������� �ش�
				characters[characters[i].target].hp -= damage;

				//[6-4-17]���� HP�� ���� ���� �Ǿ������� �����Ѵ�.
				if (characters[characters[i].target].hp < 0)
				{
					//[6-4-18] ���� Hp�� 0���� �Ѵ�.
					characters[characters[i].target].hp = 0;
				}

				//[6-4-19] ���� ����� ȭ���� �ٽ� �׸��� �Լ��� ȣ���Ѵ�
				DrawBattleScreen();

				//[6-4-20] ������ ������� �־����� �޽����� ǥ���Ѵ�.
				printf("%s���� %d�� ������!\n",
					characters[characters[i].target].name,
					damage);
				//[6-4-21] Ű���� �Է��� ��ٸ���.
				_getch();

				break;
			}
			case COMMAND_SPELL: // [6-4-22] �ֹ�

				//[6-4-23] MP�� ������� �����Ѵ�
				if (characters[i].mp < SPELL_COST)
				{
					// [6-4-24]MP�� �����ϴٴ� �޽����� ǥ���Ѵ�.
					printf("MP�� �����ϴ�.\n");

					//[6-4-25] Ű���� �Է��� ��ٸ���.
					_getch();

					//[6-4-26] �ֹ��� �ܿ�� ó������ �������´�.
					break;
				}

				//[6-4-27] MP�� �Ҹ��Ų��.
				characters[i].mp -= SPELL_COST;

				//[6-4-28] ȭ���� �ٽñ׸���.
				DrawBattleScreen();

				//[6-4-29] �ֹ��� �ܿ� �޽����� ǥ���Ѵ�.
				printf("%s��(��) �ֹ��� �ܿ���;!\n", characters[i].name);

				// [6-4-30] Ű���� �Է��� ��ٸ���.
				_getch();

				// [6-4-31] HP�� ȸ����Ų��.
				characters[i].hp = characters[i].maxHp;

				//[6-4-32] ���� ����� ȭ���� �ٽ� �׸���.
				DrawBattleScreen();

				//[6-4-33] HP�� ȸ���� �޽����� ǥ���Ѵ�.
				printf("%s�� ��ó�� ȸ���Ǿ���.\n", characters[i].name);

				// [6-4-34] Ű���� �Է��� ��ٸ���.
				_getch();

				break;

			case COMMAND_RUN:	// Run away

				// [6-4-36]�����ƴٴ� �޽����� ǥ���Ѵ�.
				printf("%s��(��) �����ƴ�.\n", characters[i].name);

				// [6-4-37]Ű���� �Է��� ��ٸ���
				_getch();

				// [6-4-38]���� ó���� ����������.
				return;

				break;
			}
			
			// [6-4-39] ���� ����� �����߷ȴ��� �����Ѵ�.
			if (characters[characters[i].target].hp <= 0)
			{
				// [6-4-40] ���� ��� ���� ó���� �б��Ų��.
				switch (characters[i].target)
				{
					// [6-4-41] �÷��̾���
				case CHARACTER_PLAYER:

					//[6-4-42] �÷��̾ ����ߴٴ� �޽����� ǥ���Ѵ�
					printf("����� ����߽��ϴ�.");
					break;

					//[6-4-43] ���Ͷ��
				case CHARACTER_MONSTER:

					//[6-4-44] ������ �ƽ�Ű��Ʈ�� �ƹ��͵� ǥ������ �ʰ� �ٽ� �ۼ��Ѵ�.
					strcpy_s(characters[characters[i].target].aa, "\n");

					//[6-4-45] ���� ����� ȭ���� �ٽ� �׸��� �Լ��� ȣ���Ѵ�.
					DrawBattleScreen();

					// [6-4-46]���͸� �����߸� �޽����� ǥ���Ѵ�
					printf("%s��(��) �����߷ȴ�!\n", characters[characters[i].target].name);

					break;
				}

				// [6-4-47] Ű���� �Է��� ��ٸ���
				_getch();

				//[6-4-48] ���� ����� �Լ��� ����������.
				return;
			}
		}
	}
}

//[6-6] ���α׷��� ���� �������� �����Ѵ�.
int main()
{
	//[6-6-1]������ �ִ´�.
	srand((unsigned int)time(NULL));
	Init();
	Battle(MONSTER_BOSS);
}