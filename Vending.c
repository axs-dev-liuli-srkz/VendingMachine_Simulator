#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MONEY_KIND 5
#define ITEM_KIND 6
#define MIN_PRICE 110

void returnCurrency(int reason);
void displayInitialScreen();
void displayItemInfo();
void displayFinanceInfo();
void pay();
void selectItems();
void calcChangeCurrency();
void initializePayment();
void displayAdmin();
int checkCountOfCharge();

typedef struct {
	int no;
	char name[20];
	int price;
	int num;
} item;

item tomato = { 1, "トマト", 150, 10 };
item apple = { 2, "リンゴ", 140, 10 };
item greenTea = { 3, "緑茶", 130, 10 };
item cola = { 4, "コーラ", 120, 10 };
item water = { 5, "水", 110, 10 };

item items[ITEM_KIND] = { { 0, "サンプル", 0, 0 }, { 1, "トマト", 150, 10 }, { 2,
		"リンゴ", 140, 10 }, { 3, "緑茶", 130, 10 }, { 4, "コーラ", 120, 10 }, { 5, "水",
		110, 10 } };

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

// 売上合計
int earnings;
// 入金額合計
int amountOfPayment = 0;
// 売上
int earning = 0;
// 釣り銭合計
int amoutOfChange = 0;
// 終了コマンド
const char end[] = "end";

int main(void) {

	displayInitialScreen();

	main();

	return 0;
}

/*
 * 初期画面表示します。
 * 商品情報を表示した後、
 * ユーザーにコマンドの入力を促します。
 * 1.[buy]利用者購入モード
 * 2.[end]キャンセル
 * 3.[admin]管理者モード
 */
void displayInitialScreen() {
	//	1.残商品と価格を表示
	printf("いらっしゃいませ!!\n");

	displayItemInfo();

	printf("商品を購入される方は[buy]を入力してください\n");
	printf("購入をキャンセルする場合は[end]を入力してください\n");

	char command[8] = "end";
	scanf("%s", command);
	// 「buy」で利用者購入モード
	if (strcmp(command, "buy") == 0) {
		// 釣り銭不足の確認
		if (checkCountOfCharge() == 1) {
			returnCurrency(7);
		}
		// 入金
		pay();
		// 商品選択
		selectItems();

	}
	//	d.終了コマンド「end」で初期画面表示
	else if (strcmp(command, "end") == 0) {
		returnCurrency(1);
		displayInitialScreen();
	}
	// c.管理者モードコマンド「admin」で管理者モードに移行
	else if (strcmp(command, "admin") == 0) {
		displayAdmin();
	} else {
		returnCurrency(5);
		displayInitialScreen();
	}

}

/*
 * 商品情報の表示をします。商品番号、商品名、価格、残数を表示
 */
void displayItemInfo() {
	printf("-----------------------------\n");
	printf("| No | 商品名 | 価格 | 残数 |\n");
	printf("-----------------------------\n");
	for (int i = 1; i < ITEM_KIND; ++i) {
		printf("| %2d | %6s |  %3d | %3d  |\n", items[i].no, items[i].name,
				items[i].price, items[i].num);
	}
	printf("-----------------------------\n");
}

/*
 * 釣り銭が足りているか確認します
 * 足りていない場合 1
 * 足りている場合 0
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
 * 利用者が金額を投入した際の処理をします。
 */
void pay() {
	printf("お金を投入してください \n※返金する場合は[end]と入力してください\n");

	//	入金入力待ち[通貨種類分(1000,500,100,50,10)5回Loop]
	for (int i = 0; i < MONEY_KIND; ++i) {
		//	投入金額が上限1990円に以上の場合返金
		if (amountOfPayment >= 1990) {
			returnCurrency(2);
			break;
		}
		printf("%d円 >>", payment[i].price);
		int count = 0;
		scanf("%d", &count);
		// 入金なしの場合
		if (count == 0) {
			printf("| 金額:%d | 枚数:%d | 入金額:%d |\n", payment[i].price, count,
					payment[i].price * count);
			continue;
		}
		// 正常入金の場合
		if (count != 0) {
			printf("| 金額:%d | 枚数:%d | 入金額:%d |\n", payment[i].price, count,
					payment[i].price * count);
			amountOfPayment = amountOfPayment + payment[i].price * count;
			payment[i].num = count;
		} else {
			continue;
		}
		printf("合計入金額:%d\n", amountOfPayment);
	}

	// 投入金額が商品の最小金額より少ない場合
	if (amountOfPayment < MIN_PRICE) {
		returnCurrency(3);
		displayInitialScreen();
	}
	return;
}

/*
 * 利用者が商品を選択する際の処理をします。
 */
void selectItems() {
	int itemNo = 0;
	int buyNum = 0;
	displayItemInfo();

	printf("ご希望の商品のNoを選択してください >> \n");
	scanf("%d", &itemNo);

	// 存在しない商品が選択された場合返金
	if (itemNo < 1 || itemNo > 5) {
		returnCurrency(4);
	}
	// 売り切れの商品が選択された場合返金
	else if (items[itemNo].num == 0) {
		returnCurrency(6);
	}
	printf("\n");
	printf("ご希望の本数を選択してください >> \n");
	scanf("%d", &buyNum);
	printf("\n");

	// 選択した商品の価格が投入金額を上回る場合返金
	if (amountOfPayment < items[itemNo].price * buyNum) {
		returnCurrency(3);
	}
	// 選択された商品が購入数量に対して不足してる場合返金
	else if (items[itemNo].num < buyNum) {
		returnCurrency(6);
	}

	// 購入結果の「商品数」データ更新
	items[itemNo].num = items[itemNo].num - buyNum;
	//「釣り銭枚数」データ更新
	for (int i = 0; i < MONEY_KIND; ++i) {
		currency[i].num = currency[i].num + payment[i].num;
	}
	// 売上計算
	earning = items[itemNo].price * buyNum;
	earnings = earnings + earning;
	// 釣り銭計算
	calcChangeCurrency();

	printf("購入された商品は「%s」が%d本です\n", items[itemNo].name, buyNum);
	printf("釣り銭の合計は%d円です\n", amoutOfChange);
	printf("- 領収証  -\n");
	printf("|  商品  | 本数 | 金額 | 釣り銭 |\n");
	printf("-------------------------------\n");
	printf("|  %6s  | %2d  |  %3d | %3d  |\n", items[itemNo].name, buyNum,
			earning, amoutOfChange);
	printf("-------------------------------\n");
	printf("- 釣り銭詳細  -\n");
	printf("---------------\n");
	printf("| 通貨 | 枚数 |\n");
	printf("---------------\n");
	for (int i = 0; i < MONEY_KIND; ++i) {
		printf("| %4s | %4d |\n", change[i].name, change[i].num);
	}
	printf("---------------\n");
	printf("ありがとうございました!!\n");

	// 投入金額の初期化
	initializePayment();
	displayInitialScreen();
}

/*
 * 釣り銭の計算します。
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
 * 処理を中断し返金します。
 */
void returnCurrency(int reason) {
	switch (reason) {
	case 1:
		printf("[end]を押されたので\n");
		break;
	case 2:
		printf("投入金額上限の1990円以上入金されたので\n");
		break;
	case 3:
		printf("投入金額が不足しているので\n");
		break;
	case 4:
		printf("存在していない商品が選択されているので\n");
		break;
	case 5:
		printf("存在していないコマンドが選択されているので\n");
		break;
	case 6:
		printf("選択された商品が不足しているので\n");
		break;
	case 7:
		printf("釣り銭が不足しているので\n");
		break;
	default:
		break;
	}
	printf("返金処理します\n");
	// 投入金額の初期化
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
 * 管理者モードを表示します
 * ユーザーにコマンドの入力を促します。
 * 1.[ci]商品補充モード
 * 2.[cc]釣り銭補充モード
 * 3.[end]初期画面表示
 */
void displayAdmin() {
	printf("管理者モードです\n");
	displayFinanceInfo();
	displayItemInfo();

	printf("商品を補充する場合は[ci]を入力してください\n");
	printf("釣り銭を補充する場合は[cc]を入力してください\n");
	printf("初期画面に移動する場合は[end]を入力してください\n");

	char command[8] = "end";
	scanf("%s", command);
	// 商品補充
	if (strcmp(command, "ci") == 0) {
		for (int i = 1; i < ITEM_KIND; ++i) {
			int num;
			printf("%sを補充する数量を入力してください >>\n", items[i].name);
			scanf("%d", &num);
			items[i].num = items[i].num + num;
			printf("%sを%d本補充しました\n", items[i].name, num);
		}
		printf("--- 補充結果 ---\n");
		displayItemInfo();
	}
	// 釣り銭補充
	else if (strcmp(command, "cc") == 0) {
		for (int i = 0; i < MONEY_KIND; ++i) {
			int num;
			printf("%s円を補充する数量を入力してください >>\n", currency[i].name);
			scanf("%d", &num);
			currency[i].num = currency[i].num + num;
			printf("%s円を%d枚補充しました\n", currency[i].name, num);
		}
		printf("--- 補充結果 ---\n");
		displayFinanceInfo();
	}
	// 初期画面表示
	else if (strcmp(command, "end") == 0) {
		displayInitialScreen();
	} else {
		displayAdmin();
	}
	displayAdmin();
}

/*
 * 金銭情報を表示します
 */
void displayFinanceInfo() {
	printf("---------------\n");
	printf("  売上 : %d円\n", earnings);
	printf("---------------\n");
	printf("--釣り銭残数---\n");
	printf("---------------\n");
	printf("| 通貨 | 残数 |\n");
	printf("---------------\n");
	for (int i = 0; i < MONEY_KIND; ++i) {
		printf("| %4s | %4d |\n", currency[i].name, currency[i].num);
	}
}
