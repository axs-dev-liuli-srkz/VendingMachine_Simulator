#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MONEY_KIND 5
#define ITEM_KIND 6
#define MIN_PRICE 110

// ���i�\����
typedef struct {
	int no;
	char name[20];
	int price;
	int num;
} item;

item tomato = { 1, "�g�}�g", 150, 10 };
item apple = { 2, "�����S", 140, 10 };
item greenTea = { 3, "�Β�", 130, 10 };
item cola = { 4, "�R�[��", 120, 10 };
item water = { 5, "��", 110, 10 };

item items[ITEM_KIND] = { { 0, "�T���v��", 0, 0 }, { 1, "�g�}�g", 150, 10 }, { 2,
		"�����S", 140, 10 }, { 3, "�Β�", 130, 10 }, { 4, "�R�[��", 120, 10 }, { 5, "��",
		110, 10 } };

// �����\����
typedef struct {
	int no;
	char name[20];
	int price;
	int num;
} money;

money currency[MONEY_KIND] = { { 1, "1000", 1000, 10 }, { 2, "500", 500, 10 }, {
		3, "100", 100, 10 }, { 4, "50", 50, 10 }, { 5, "10", 10, 10 } };

money payment[MONEY_KIND] = { { 1, "1000", 1000, 0 }, { 2, "500", 500, 0 }, { 3,
		"100", 100, 0 }, { 4, "50", 50, 0 }, { 5, "10", 10, 0 } };

money change[MONEY_KIND] = { { 1, "1000", 1000, 0 }, { 2, "500", 500, 0 }, { 3,
		"100", 100, 0 }, { 4, "50", 50, 0 }, { 5, "10", 10, 0 } };

// ���㍇�v
int earnings;
// �����z���v
int amountOfPayment = 0;
// ����
int earning = 0;
// �ނ�K���v
int amoutOfChange = 0;
// �I���R�}���h
const char end[] = "end";

int main(void) {

	displayInitialScreen();

	main();

	return 0;
}

/*
 * ������ʕ\�����܂��B
 * ���i����\��������A
 * ���[�U�[�ɃR�}���h�̓��͂𑣂��܂��B
 * 1.[buy]���p�ҍw�����[�h
 * 2.[end]�L�����Z��
 * 3.[admin]�Ǘ��҃��[�h
 */
void displayInitialScreen() {
	//	1.�c���i�Ɖ��i��\��
	printf("��������Ⴂ�܂�!!\n");

	displayItemInfo();

	printf("���i���w����������[buy]����͂��Ă�������\n");
	printf("�w�����L�����Z������ꍇ��[end]����͂��Ă�������\n");

	char command[8] = "end";
	scanf("%s", command);
	// �ubuy�v�ŗ��p�ҍw�����[�h
	if (strcmp(command, "buy") == 0) {
		// �ނ�K�s���̊m�F
		if (checkCountOfCharge() == 1) {
			returnCurrency(7);
		}
		// ����
		pay();
		// ���i�I��
		selectItems();

	}
	//	d.�I���R�}���h�uend�v�ŏ�����ʕ\��
	else if (strcmp(command, "end") == 0) {
		returnCurrency(1);
		displayInitialScreen();
	}
	// c.�Ǘ��҃��[�h�R�}���h�uadmin�v�ŊǗ��҃��[�h�Ɉڍs
	else if (strcmp(command, "admin") == 0) {
		displayAdmin();
	} else {
		returnCurrency(5);
		displayInitialScreen();
	}

}

/*
 * ���i���̕\�������܂��B���i�ԍ��A���i���A���i�A�c����\��
 */
void displayItemInfo() {
	printf("-----------------------------\n");
	printf("| No | ���i�� | ���i | �c�� |\n");
	printf("-----------------------------\n");
	for (int i = 1; i < ITEM_KIND; ++i) {
		printf("| %2d | %6s |  %3d | %3d  |\n", items[i].no, items[i].name,
				items[i].price, items[i].num);
	}
	printf("-----------------------------\n");
}

/*
 * �ނ�K������Ă��邩�m�F���܂�
 * ����Ă��Ȃ��ꍇ 1
 * ����Ă���ꍇ 0
 */
int checkCountOfCharge() {
	if (currency[1].num < 1 || currency[2].num < 4 || currency[3].num < 1
			|| currency[4].num < 4) {
		return 1;
	} else {
		return 0;
	}
}

/*
 * ���p�҂����z�𓊓������ۂ̏��������܂��B
 */
void pay() {
	printf("�����𓊓����Ă������� \n���ԋ�����ꍇ��[end]�Ɠ��͂��Ă�������\n");

	//	�������͑҂�[�ʉݎ�ޕ�(1000,500,100,50,10)5��Loop]
	for (int i = 0; i < MONEY_KIND; ++i) {
		//	�������z�����1990�~�Ɉȏ�̏ꍇ�ԋ�
		if (amountOfPayment >= 1990) {
			returnCurrency(2);
			break;
		}
		printf("%d�~ >>", payment[i].price);
		int count = 0;
		scanf("%d", &count);
		// �����Ȃ��̏ꍇ
		if (count == 0) {
			printf("| ���z:%d | ����:%d | �����z:%d |\n", payment[i].price, count,
					payment[i].price * count);
			continue;
		}
		// ��������̏ꍇ
		if (count != 0) {
			printf("| ���z:%d | ����:%d | �����z:%d |\n", payment[i].price, count,
					payment[i].price * count);
			amountOfPayment = amountOfPayment + payment[i].price * count;
			payment[i].num = count;
		} else {
			continue;
		}
		printf("���v�����z:%d\n", amountOfPayment);
	}

	// �������z�����i�̍ŏ����z��菭�Ȃ��ꍇ
	if (amountOfPayment < MIN_PRICE) {
		returnCurrency(3);
		displayInitialScreen();
	}
	return;
}

/*
 * ���p�҂����i��I������ۂ̏��������܂��B
 */
void selectItems() {
	int itemNo = 0;
	int buyNum = 0;
	displayItemInfo();

	printf("����]�̏��i��No��I�����Ă������� >> \n");
	scanf("%d", &itemNo);

	// ���݂��Ȃ����i���I�����ꂽ�ꍇ�ԋ�
	if (itemNo < 1 || itemNo > 5) {
		returnCurrency(4);
	}
	// ����؂�̏��i���I�����ꂽ�ꍇ�ԋ�
	else if (items[itemNo].num == 0) {
		returnCurrency(6);
	}
	printf("\n");
	printf("����]�̖{����I�����Ă������� >> \n");
	scanf("%d", &buyNum);
	printf("\n");

	// �I���������i�̉��i���������z������ꍇ�ԋ�
	if (amountOfPayment < items[itemNo].price * buyNum) {
		returnCurrency(3);
	}
	// �I�����ꂽ���i���w�����ʂɑ΂��ĕs�����Ă�ꍇ�ԋ�
	else if (items[itemNo].num < buyNum) {
		returnCurrency(6);
	}

	// �w�����ʂ́u���i���v�f�[�^�X�V
	items[itemNo].num = items[itemNo].num - buyNum;
	//�u�ނ�K�����v�f�[�^�X�V
	for (int i = 0; i < MONEY_KIND; ++i) {
		currency[i].num = currency[i].num + payment[i].num;
	}
	// ����v�Z
	earning = items[itemNo].price * buyNum;
	earnings = earnings + earning;
	// �ނ�K�v�Z
	calcChangeCurrency();

	printf("�w�����ꂽ���i�́u%s�v��%d�{�ł�\n", items[itemNo].name, buyNum);
	printf("�ނ�K�̍��v��%d�~�ł�\n", amoutOfChange);
	printf("- �̎���  -\n");
	printf("|  ���i  | �{�� | ���z | �ނ�K |\n");
	printf("-------------------------------\n");
	printf("|  %6s  | %2d  |  %3d | %3d  |\n", items[itemNo].name, buyNum,
			earning, amoutOfChange);
	printf("-------------------------------\n");
	printf("- �ނ�K�ڍ�  -\n");
	printf("---------------\n");
	printf("| �ʉ� | ���� |\n");
	printf("---------------\n");
	for (int i = 0; i < MONEY_KIND; ++i) {
		printf("| %4s | %4d |\n", change[i].name, change[i].num);
	}
	printf("---------------\n");
	printf("���肪�Ƃ��������܂���!!\n");

	// �������z�̏�����
	initializePayment();
	displayInitialScreen();
}

/*
 * �ނ�K�̌v�Z���܂��B
 */
void calcChangeCurrency() {
	amoutOfChange = amountOfPayment - earning;
	int remainder = 0;
	for (int i = 0; i < MONEY_KIND; ++i) {
		if (i == 0) {
			change[0].num = amoutOfChange / currency[0].price;
			remainder = amoutOfChange % currency[0].price;
			currency[0].num = currency[0].num - change[0].num;
		} else {
			change[i].num = remainder / currency[i].price;
			remainder = remainder % currency[i].price;
			currency[i].num = currency[i].num - change[i].num;
		}
	}
}

/*
 * �����𒆒f���ԋ����܂��B
 */
void returnCurrency(int reason) {
	switch (reason) {
	case 1:
		printf("[end]�������ꂽ�̂�\n");
		break;
	case 2:
		printf("�������z�����1990�~�ȏ�������ꂽ�̂�\n");
		break;
	case 3:
		printf("�������z���s�����Ă���̂�\n");
		break;
	case 4:
		printf("���݂��Ă��Ȃ����i���I������Ă���̂�\n");
		break;
	case 5:
		printf("���݂��Ă��Ȃ��R�}���h���I������Ă���̂�\n");
		break;
	case 6:
		printf("�I�����ꂽ���i���s�����Ă���̂�\n");
		break;
	case 7:
		printf("�ނ�K���s�����Ă���̂�\n");
		break;
	default:
		break;
	}
	printf("�ԋ��������܂�\n");
	// �������z�̏�����
	initializePayment();
	displayInitialScreen();
}

void initializePayment() {
	for (int i = 0; i < MONEY_KIND; ++i) {
		payment[i].num = 0;
	}
	amountOfPayment = 0;
}

/*
 * �Ǘ��҃��[�h��\�����܂�
 * ���[�U�[�ɃR�}���h�̓��͂𑣂��܂��B
 * 1.[ci]���i��[���[�h
 * 2.[cc]�ނ�K��[���[�h
 * 3.[end]������ʕ\��
 */
void displayAdmin() {
	printf("�Ǘ��҃��[�h�ł�\n");
	displayFinanceInfo();
	displayItemInfo();

	printf("���i���[����ꍇ��[ci]����͂��Ă�������\n");
	printf("�ނ�K���[����ꍇ��[cc]����͂��Ă�������\n");
	printf("������ʂɈړ�����ꍇ��[end]����͂��Ă�������\n");

	char command[8] = "end";
	scanf("%s", command);
	// ���i��[
	if (strcmp(command, "ci") == 0) {
		for (int i = 1; i < ITEM_KIND; ++i) {
			int num;
			printf("%s���[���鐔�ʂ���͂��Ă������� >>\n", items[i].name);
			scanf("%d", &num);
			items[i].num = items[i].num + num;
			printf("%s��%d�{��[���܂���\n", items[i].name, num);
		}
		printf("--- ��[���� ---\n");
		displayItemInfo();
	}
	// �ނ�K��[
	else if (strcmp(command, "cc") == 0) {
		for (int i = 0; i < MONEY_KIND; ++i) {
			int num;
			printf("%s�~���[���鐔�ʂ���͂��Ă������� >>\n", currency[i].name);
			scanf("%d", &num);
			currency[i].num = currency[i].num + num;
			printf("%s�~��%d����[���܂���\n", currency[i].name, num);
		}
		printf("--- ��[���� ---\n");
		displayFinanceInfo();
	}
	// ������ʕ\��
	else if (strcmp(command, "end") == 0) {
		displayInitialScreen();
	} else {
		displayAdmin();
	}
	displayAdmin();
}

/*
 * ���K����\�����܂�
 */
void displayFinanceInfo() {
	printf("---------------\n");
	printf("  ���� : %d�~\n", earnings);
	printf("---------------\n");
	printf("--�ނ�K�c��---\n");
	printf("---------------\n");
	printf("| �ʉ� | �c�� |\n");
	printf("---------------\n");
	for (int i = 0; i < MONEY_KIND; ++i) {
		printf("| %4s | %4d |\n", currency[i].name, currency[i].num);
	}
}
