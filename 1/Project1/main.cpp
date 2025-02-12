// [1]����� ��Ŭ����ϴ� ��
#include <stdio.h> //[1-1]ǥ�� ����� ����� ��Ŭ����Ѵ�
#include <stdlib.h>//[1-2]ǥ�� ���̺귯�� ����� ��Ŭ����Ѵ�
#include <string.h>//[1-3]���ڿ� ���� ����� ��Ŭ����Ѵ�.
#include <time.h> //[1-4]�ð� ���� ����� ��Ŭ����Ѵ�.
#include <conio.h> //[1-5]�ܼ� ����� ����� ��Ŭ����Ѵ�.

// [2]����� ������.

// [3]���� ����� �����ϴ� ��

// [3-2] ĳ������ ������ �����Ѵ�.
enum
{
	MONSTER_PLAYER,
	MONSTER_SLIME,
	MONSTER_MAX
};
// [3-3] ����� ������ �����Ѵ�.
enum
{
	COMMAND_FIGHT,
	COMMAND_SPELL,
	COMMAND_RUN,
	COMMAND_MAX
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

enum
{
	CHARACTER_PLAYER,
	CHARACTER_MONSTER,
	CHARACTER_MAX
};
	
// [5[]define variable] ������ �����ϴ� ��

// [5-1] ���� ������ �迭�� �����Ѵ�.
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
			case COMMAND_SPELL: // Spell the magic
				break;
			case COMMAND_RUN:	// Run away
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
	Battle(MONSTER_SLIME);
}