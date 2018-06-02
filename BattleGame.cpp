#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#define ShopNum 9
#define BatMoney 10
int huihe;
//参考值：100 30 20 10 15
typedef struct commodity {
	char name[100];
	int price;
	int number;
}commodity;

typedef struct Shop {
	commodity num[ShopNum];
}Shop;

typedef struct batman {
	int max;
	int BatNum = 10;
	int blood = 10;//100--200
	int attack = 3, defense = 1;//25 10
}batman;

typedef struct general {
	int blood;//100--200
	int attack, defense;//50--80  20--50
	int intelligence;//20--50
	batman command;
	int times = 3;
	int money = 100;
	int storepower = 0;
	Shop shop;
	int situation = 0;//总攻击 1;暴击 2;
	int escape_times = 0;//逃跑次数 
}general;

void game_profile() {
	system("cls");
	FILE *fp = fopen("RuleOfGame.txt","r");
	if (fp == NULL) {
		printf("Cannot open the file!\n");
		return;
	}
	char buffer[60];
	while(!feof(fp)) { //判断是否到文件尾 
		fread(buffer,6,10,fp); 
		printf("%s",buffer);
	}
	printf("\nPlease click the 'Enter' key to return the main menu!\n\n");
	fclose(fp);
	system("pause"); system("cls");
}

void p_change(general &m, int i) {
	printf("你购买了%d号商品：%s\n", i + 1, m.shop.num[i].name);
	m.money -= m.shop.num[i].price;
	m.shop.num[i].number--;
	printf("你剩余金钱为：%d\n",m.money);
}

int purchase_two(general &m, int label) {
	if (label == 0) return 0;
	if (m.shop.num[label - 1].number == 0)
	 {
	 	printf("该商品已经卖光啦!\n"); system("pause"); return 0;
	}
	if (m.money<m.shop.num[label - 1].price) { printf("很抱歉，您的金钱不足！\n"); system("pause"); return 0; }
	else {
		switch (label) {
		case 1: m.blood = 100; p_change(m, label - 1); return 1; break;
		case 2: m.blood += 100; p_change(m, label - 1); return 1; break;
		case 3: m.attack += 25; p_change(m, label - 1); return 1; break;
		case 4: m.attack += 15; p_change(m, label - 1); return 1; break;
		case 5: m.defense += 25; p_change(m, label - 1); return 1; break;
		case 6: m.defense += 15; p_change(m, label - 1); return 1; break;
		case 7: m.situation = 1; p_change(m, label - 1); return 1; break;
		case 8: m.situation = 2; p_change(m, label - 1); return 1; break;
		case 9: printf("你想买多少组小兵?\n");
			int n; scanf("%d", &n);
			if (m.money<n*m.shop.num[label - 1].price) { printf("很抱歉，您的金钱不足！\n"); system("pause"); return 0; }
			else  m.money -= n*m.shop.num[label - 1].price;
			m.shop.num[label - 1].number--;
			printf("你购买了%d号商品：%s\n你剩余金钱为：%d\n", label, m.shop.num[label - 1].name,m.money);
			if (m.command.max<m.command.BatNum + 3 * n)  m.command.BatNum = m.command.max;
			else  m.command.BatNum += n * 3;
			printf("现在您小兵的总数量为: %d\n", m.command.BatNum); return 1; break;
		default: printf("输入错误！\n");
		}
	}
}

int purchase_one(general &m, int label) {
	if (label == 0) return 0;
	if (m.shop.num[label - 1].number == 0) { printf("该商品已经卖光啦!\n"); return 0; }//system("pause");
	if (m.money<m.shop.num[label - 1].price) { printf("很抱歉，您的金钱不足！\n"); return 0; /*system("pause"); */ }
	else {
		switch (label) {
		case 1: m.blood = 100; p_change(m, label - 1); return 1; break;
		case 2: m.blood += 100; p_change(m, label - 1); return 1; break;
		case 3: m.attack += 25; p_change(m, label - 1); return 1; break;
		case 4: m.attack += 15; p_change(m, label - 1); return 1; break;
		case 5: m.defense += 25; p_change(m, label - 1); return 1; break;
		case 6: m.defense += 15; p_change(m, label - 1); return 1; break;
		case 7: m.situation = 1; p_change(m, label - 1); return 1; break;
		case 8: m.situation = 2; p_change(m, label - 1); return 1; break;
		case 9: //printf("你想买多少组小兵?\n");
			int n; n = (m.command.max - m.command.BatNum) / 3 + 1;
			while (n--) {
				if (m.money<n*m.shop.num[label - 1].price) { /*printf("很抱歉，您的金钱不足！\n"); */continue; }
				else  m.money -= n*m.shop.num[label - 1].price;
				m.shop.num[label - 1].number--;
				//printf("你购买了%d号商品：%s\n", label, m.shop.num[label - 1].name);
				if (m.command.max<m.command.BatNum + 3 * n)  m.command.BatNum = m.command.max;
				else  m.command.BatNum += n * 3;
				//printf("现在您小兵的总数量为: %d\n", m.command.BatNum); return 1;
			}return 1; break;
		default: printf("输入错误！\n");
		}
	}
}

void value_shop(Shop &s) {
	int i;
	for (i = 0; i<ShopNum; i++) {
		switch (i + 1) {
		case 1:strcpy(s.num[i].name, "灵桃(回满血)(0)                    "); s.num[i].price = 80; s.num[i].number = 5; break;
		case 2:strcpy(s.num[i].name, "灵药(加100滴血)(0)                 "); s.num[i].price = 120; s.num[i].number = 4; break;
		case 3:strcpy(s.num[i].name, "宝剑(攻击力+25)                    "); s.num[i].price = 250; s.num[i].number = 1; break;
		case 4:strcpy(s.num[i].name, "铁剑(攻击力+15)                    "); s.num[i].price = 175; s.num[i].number = 1; break;
		case 5:strcpy(s.num[i].name, "铠甲(防御力+25)                    "); s.num[i].price = 235; s.num[i].number = 1; break;
		case 6:strcpy(s.num[i].name, "战衣(防御力+15)                    "); s.num[i].price = 165; s.num[i].number = 1; break;
		case 7:strcpy(s.num[i].name, "金钟罩(对方总攻击在三回合内无效)(0)"); s.num[i].price = 80; s.num[i].number = 5; break;
		case 8:strcpy(s.num[i].name, "铁钟罩(对方暴击在三回合无效)(0)    "); s.num[i].price = 55; s.num[i].number = 6; break;
		case 9:strcpy(s.num[i].name, "小兵(小兵以组为单位，每组3人)      "); s.num[i].price = 45; s.num[i].number = 10; break;
		}
	}
}

void print_shop(Shop s) {
	int i;
	printf("\n------------------------------- 商店 ------------------------------------\n");
	printf("\n商品序号    商品名(作用)(0:一次性物品)            价格        剩余数量\n");
	for (i = 0; i<ShopNum; i++) {
		printf("   %d        %s      %-14.d%d\n", i + 1, s.num[i].name, s.num[i].price, s.num[i].number);
	}
	printf("\n 选择‘0’退出商店！");
	printf("\n-------------------------------------------------------------------------\n");
}

int increase(int x, int t) {
	int d, m = sqrt(2 * (x + t) / t);
	d = rand() % (m);
	if (d <= m / 2) return d + (m + 1) / 3 + rand() % ((x + t) / (6 + t) + 1) - 1;
	else return d + rand() % ((x + t) / (6 + t) + 1) - 1;
}

int HurtBlood(general x, general y, int storepower) {
	int hurt_blood;//the blood of x attack y.
	if (storepower == 0) {
		hurt_blood = x.attack*(100 + x.intelligence) / (100 + sqrt(3 * huihe + y.intelligence)) - y.defense*(100 + y.intelligence + 2 * sqrt(huihe)) / 100 + rand() % (x.intelligence / y.intelligence + 1) - rand() % (y.intelligence / x.intelligence + 1);
		if (hurt_blood>(x.attack - y.defense) * 6 / 5) hurt_blood = (x.attack - y.defense) * 6 / 5 + sqrt(hurt_blood) / 2 - 1;
		if (hurt_blood<3) {
			if (y.defense - x.attack > 15 || y.intelligence - x.intelligence > 12) hurt_blood = 1;
			else if (y.defense - x.attack >= 10 || y.intelligence - x.intelligence >= 8) hurt_blood = 2;
			     else hurt_blood = 3;
		}
	}
	else {
		int h;
		h = (storepower + 1)*(x.attack - sqrt(2 * huihe) - sqrt(y.intelligence / 3) - (storepower + 1) * 2 + sqrt(2 * x.intelligence / 5) - sqrt(y.defense / 2)) - y.defense*(1 + y.intelligence / (100 + huihe));
		hurt_blood = (h - rand() % (y.intelligence / 6 + 1) + storepower*storepower - storepower + 1);
		if (hurt_blood<5) hurt_blood = 2 + 3 * storepower;
	}
	return hurt_blood;
}

void harm_general(general &x, general &y, int hurt_way) {//x attack y
	int hurt_blood; //hurt_way 为1时，普通攻击；为2时，暴击 
	if (hurt_way == 2) {
		x.blood -= (x.storepower*x.storepower + 1);// 1 2 5 10
		printf("\n你因暴击而自损了 %d 滴血。\n", x.storepower*x.storepower + 1);
		if (y.situation == 1) hurt_blood = 0;
		else {
			if (y.situation == 2) hurt_blood = HurtBlood(x, y, 0);
			else hurt_blood = HurtBlood(x, y, x.storepower);
		}
		x.storepower = 0;
	}
	else {
		printf("\n");
		if (y.situation == 1) hurt_blood = 0;
		else hurt_blood = HurtBlood(x, y, 0);
	}
	y.blood -= hurt_blood;
	printf("你伤害了敌人 %d 滴血。现在敌人的血量为: %d.\n", hurt_blood, y.blood);
}

void harm_batman(general &x, general &y) {
	int hurt_blood, hurt_batman;
	hurt_blood = x.attack*(1 + x.intelligence / (80 + huihe)) - y.command.defense*y.command.BatNum;
	hurt_batman = hurt_blood / y.command.blood;
	if (y.command.BatNum<hurt_batman) hurt_batman = y.command.BatNum;
	y.command.BatNum -= hurt_batman; x.money += (hurt_batman*BatMoney);
	printf("你伤害了敌人 %d 个小兵。现在敌人小兵的总数量为: %d\n", hurt_batman, y.command.BatNum);
	printf("你获得了 %d 金钱.", hurt_batman*BatMoney);
}
/*
己方小兵先打对方小兵，若对方小兵已无，再去攻击对方将领
己方将领可选择攻打对方小兵或者将领，但攻打对方小兵会有金钱奖励，攻击敌方小兵数目越多，金钱越多
*/
int computer_attack_way(general A, general B) {
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	int hurt_blood, r;
	hurt_blood = HurtBlood(A, B, A.storepower);
	r = rand() % 10;
	if (hurt_blood>B.blood - 15) {
		if (A.storepower >= 1) return 2;
		else return 1;
	}
	if (B.command.BatNum > 2 && (r >= 3)) return 3;
	if (A.command.BatNum <= 2 && B.command.BatNum > 0) return 3;
	else return 1;
}

void general_attack_way_two(general &A, general &B) {
	int a, b;
	printf("\n--------------------------  现在是 A 攻击 B  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack B'batmen        4:Attack B'batmen by using store_power\n");
	scanf("%d", &a);
	if (a == 3) harm_batman(A, B);
	else  harm_general(A, B, a);
	printf("\n------------------------------------------------------------------------\n");
	printf("\n--------------------------  现在是 B 攻击 A  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack A'batmen        4:Attack A'batmen by using store_power\n");
	scanf("%d", &b);
	if (b == 3) harm_batman(B, A);
	else  harm_general(B, A, b);
	printf("\n------------------------------------------------------------------------\n");
}

void general_attack_way_one(general &A, general &B) {
	int a, b;
	printf("\n--------------------------  现在是 你 攻击 电脑  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack B'batmen        4:Attack B'batmen by using store_power\n");
	scanf("%d", &a);
	if (a == 3) harm_batman(A, B);
	else  harm_general(A, B, a);
	printf("\n------------------------------------------------------------------------\n");
	printf("\n--------------------------  现在是 电脑 攻击 你  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack A'batmen        4:Attack A'batmen by using store_power\n");
	b = computer_attack_way(B, A);
	printf("电脑选择了 %d .\n", b);
	if (b == 3) harm_batman(B, A);
	else  harm_general(B, A, b);
	printf("\n------------------------------------------------------------------------\n");
}

void general_attack_way_text(general &A, general &B) {
	int a, b;
	printf("\n--------------------------  现在是 A 攻击 B  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack B'batmen        4:Attack B'batmen by using store_power\n");
	a = computer_attack_way(A, B);
	printf("电脑B选择了 %d .\n", a);
	if (a == 3) harm_batman(A, B);
	else  harm_general(A, B, a);
	printf("\n------------------------------------------------------------------------\n");
	printf("\n--------------------------  现在是 B 攻击 A  ---------------------------\n");
	printf("\n1:普通攻击敌方将领           2:暴击敌方将领          3:普通攻击敌方小兵\n");
	//printf("3:Attack A'batmen        4:Attack A'batmen by using store_power\n");
	b = computer_attack_way(B, A);
	printf("电脑B选择了 %d .\n", b);
	if (b == 3) harm_batman(B, A);
	else  harm_general(B, A, b);
	printf("\n------------------------------------------------------------------------\n");
}

void bat_hurt_bat(general &x, general &y, char c1, char c2) {
	int hurt_blood, hurt_batman;
	hurt_blood = x.command.attack*x.command.BatNum*(1 + x.intelligence / (70 + huihe)) - y.command.defense*y.command.BatNum;
	hurt_batman = hurt_blood / y.command.blood;
	if (y.command.BatNum<hurt_batman) hurt_batman = y.command.BatNum;
	if (hurt_batman<0) hurt_batman = 0;
	y.command.BatNum -= hurt_batman; x.money += (hurt_batman*BatMoney);
	printf("\n %c的小兵攻击了%c %d 个小兵。现在%c小兵数量为: %d 。", c1, c2, hurt_batman, c2, y.command.BatNum);
	printf(" %c 获得了 %d 金钱.\n", c1, hurt_batman*BatMoney);
}

void bat_hurt_gen(general &x, general &y, char c1, char c2) {
	int hurt_blood;
	hurt_blood = x.command.attack*x.command.BatNum*(1 + x.intelligence / (90 + huihe)) - y.defense*(1 + y.intelligence / (80 + huihe));
	if (hurt_blood<1) hurt_blood = 2; else if (hurt_blood <= 3) hurt_blood = 3;
	else if (hurt_blood<x.command.BatNum / 2) hurt_blood += rand() % (x.intelligence / 100 + 1);
	y.blood -= hurt_blood;
	printf("\n %c的小兵攻击了%c方将领 %d 滴血. 现在%c方将领血量为: %d 。\n", c1, c2, hurt_blood, c2, y.blood);
}

void batman_attack_way(general &A, general &B, char c1, char c2) {
	if (A.command.BatNum == 0) printf(" 很遗憾，%c的小兵已经死光了！\n", c1);
	else if (B.command.BatNum>0) bat_hurt_bat(A, B, c1, c2);
	else
		bat_hurt_gen(A, B, c1, c2);
}

void value(general &m) {
	printf("血量值、攻击力、防御力、智力值、统率力:");
	scanf("%d %d %d %d %d", &m.blood, &m.attack, &m.defense, &m.intelligence, &m.command.max);
}

void print(general A_player, general B_player) {
	printf("\n****************** 第 %d 次回合结果 ********************\n", huihe++);
	printf(" A 将领:\n");
	printf(" 血  量: %-6.1d攻击力: %-6.d防御力: %-6.d智力值: %d\n", A_player.blood, A_player.attack, A_player.defense, A_player.intelligence);
	printf(" 统率力: %-6.d总兵数: %-6.1d金  钱: %-6.1d蓄力值: %d\n", A_player.command.max, A_player.command.BatNum, A_player.money, A_player.storepower);
	printf(" B 将领:\n");
	printf(" 血  量: %-6.1d攻击力: %-6.d防御力: %-6.d智力值: %d\n", B_player.blood, B_player.attack, B_player.defense, B_player.intelligence);
	printf(" 统率力: %-6.d总兵数: %-6.1d金  钱: %-6.1d蓄力值: %d\n", B_player.command.max, B_player.command.BatNum, B_player.money, B_player.storepower);
	printf("*******************************************************\n");
}

//蓄力最多三次，且最好连续蓄力，否则蓄力次数便会减一直至为零 
int strategyin(general &m, general &e, char character) {
	int up, c;
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	m.situation = 0;//情况置为 0 
	while (1) {
		system("cls");
		printf("\n------------------ 现在是 %c 进行操作 -------------------\n", character);
		printf("\n 你要选择哪种策略?\n");
		printf(" 1:增加血量         2:增加智力         3:增加攻击力\n");
		printf(" 4:增加防御力       5:增加统率力       6:蓄力\n");
		printf(" 7:赚钱             8:打开商店         9:偷对方金钱\n");
		scanf("%d", &c);
		printf("你选择了: %d\n", c);
		switch (c) {
		case 1:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 28 + increase(m.intelligence, 3) + sqrt(2 * (huihe + 1) - 2 * m.times / 5); m.blood += up;
				 printf("血量增加了 %d.现在你的血量为:%d.\n", up, m.blood); return 1; break;
		case 2:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 3 + increase(m.intelligence, 2 * m.times++) - m.intelligence / 25; if (up<3) up = 3; m.intelligence += up;
				 printf("智力增加了 %d.现在你的智力为:%d.\n", up, m.intelligence); return 1; break;
		case 3:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 4 + increase(m.intelligence, 3); m.attack += up;
				 printf("攻击力增加了 %d.现在你的攻击力为:%d.\n", up, m.attack); return 1; break;
		case 4:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 5 + increase(m.intelligence, 3); m.defense += up;
				 printf("防御力增加了 %d.现在你的防御力为:%d.\n", up, m.defense); return 1; break;
		case 5:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 6 + increase(m.intelligence, 3); m.command.max += up;
				 printf("统率力增加了 %d.现在你的统率力为:%d.\n", up, m.command.max); return 1; break;
		case 6:  if (m.storepower<3)  m.storepower++; printf("现在你的蓄力值为: %d\n", m.storepower); return 1; break;
		case 7:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 up = 100 + rand() % ((m.intelligence + huihe) / 4 + 1) + (m.intelligence + huihe) / 4 + (m.intelligence - e.intelligence) / 3; m.money += up;
				 printf("金钱增加了 %d.现在你的金钱为: %d.\n", up, m.money); return 1; break;
		case 8:  if (m.storepower >= 1) { m.storepower--; printf("现在你的蓄力值为: %d\n", m.storepower); }
				 print_shop(m.shop); int label;
				 while (1) {
					 printf("\n你当前的金钱为: %d\n", m.money);
					 printf("你想购买哪件商品?(请输入序号)\n"); scanf("%d", &label);
					 if (purchase_two(m, label)) return 1;
					 else break;
				 }
				 break;
		case 9:  int steal_money, cm, oe; steal_money = e.money / 2;
			cm = (steal_money / 2 * (60 + (m.intelligence - e.intelligence)) / (60 + sqrt(huihe) + m.times));
			oe = (steal_money*(60 - e.intelligence) / (60 + huihe + e.times));
			if (cm<12) cm = 12; else if (cm >= oe) cm = oe - oe / 50;
			if (oe<18) oe = 18; else if (oe >= e.money) oe = e.money - oe / 50;
			m.money += cm; e.money -= oe;
			printf("你偷了敌方 %d 金钱.对方损失了 %d 金钱.现在你的金钱为: %d.\n", cm, oe, m.money);
			return 1; break;
		default: printf("输入错误！请重新输入！\n");
		}
	}
}

int com_choose_easy(general play, general computer, int &shop_choose) {
	int p_hurt_c_blood, c_hurt_p_blood, r;
	p_hurt_c_blood = HurtBlood(play, computer, play.storepower); c_hurt_p_blood = HurtBlood(computer, play, computer.storepower);
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	rand(); r = rand() % 10;
	if (p_hurt_c_blood>(computer.blood - 2 * sqrt(huihe))) {//加血 
		if ((computer.shop.num[0].number>0) && (computer.money >= computer.shop.num[0].price) && (computer.blood<15)) { shop_choose = 1; return 8; }//买灵桃 
		if (r>5) {
			if ((computer.shop.num[1].number>0) && (computer.money >= computer.shop.num[1].price)) { shop_choose = 2; return 8; }//买灵药 
			else return 1;//加血 
		}
		return 1;
	}
	while (1) {
		int i=1;
		srand((unsigned)time((time_t*)NULL) * 13 + huihe +i);
		r = rand() % 9; //printf("%d ", r);
		switch (r) {
		case 0: return 2; break;
		case 1: return 3; break;
		case 2: return 4; break;
		case 3: if (computer.command.max<=25) return 5; break;
		case 4: if ((HurtBlood(computer, play, computer.storepower)<play.blood - 2 * sqrt(huihe)) && (HurtBlood(computer, play, computer.storepower + 1)>play.blood - huihe))
			return 6;  break;
		case 5: if (computer.money <= computer.shop.num[2].price) return 7; break;
		case 6: if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[2].price&&rand()%9 >= 2&&computer.shop.num[2].number>0) 
                 { shop_choose = 3; return 8; }//买宝剑 
			if (computer.money >= computer.shop.num[4].price&&rand()%11 >= 3&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[3].price&&rand()%9 >= 2&&computer.shop.num[3].number>0) 
				 { shop_choose = 4; return 8; }//买铁剑 
			if (computer.money >= computer.shop.num[2].price&&rand()%11 >= 3&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			shop_choose = 9; return 8;//买小兵 
		} break;
		case 7: if (play.money >= computer.shop.num[0].price) return 9; break;
		case 8: if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[2].price&&rand()%9 >= 2&&computer.shop.num[2].number>0) 
                 { shop_choose = 3; return 8; }//买宝剑 
			if (computer.money >= computer.shop.num[4].price&&rand()%11 >= 3&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[3].price&&rand()%9 >= 2&&computer.shop.num[3].number>0) 
				 { shop_choose = 4; return 8; }//买铁剑 
			if (computer.money >= computer.shop.num[2].price&&rand()%11 >= 3&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			if ((computer.shop.num[7].number>0) && (computer.money >= computer.shop.num[7].price) && (play.storepower>0)) 
			     { shop_choose = 8; return 8; }//买铁钟罩
			if ((computer.shop.num[6].number>0) && (computer.money >= computer.shop.num[6].price) && ((computer.defense + play.intelligence)<(play.attack + play.intelligence - 10)))
			     { shop_choose = 7; return 8; }//买金钟罩
		} break;
		}
		i++;
	}
}

int com_choose_medium(general play, general computer, int &shop_choose) {
	int p_hurt_c_blood, c_hurt_p_blood, r;
	p_hurt_c_blood = HurtBlood(play, computer, play.storepower); c_hurt_p_blood = HurtBlood(computer, play, computer.storepower);
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	rand(); r = rand() % 10;
	if (p_hurt_c_blood>(computer.blood - 2 * sqrt(huihe))) {//加血 
		if ((computer.shop.num[0].number>1) && (computer.money >= computer.shop.num[0].price) && (computer.blood<15)) { shop_choose = 1; return 8; }//买灵桃 
		if (r>5) {
			if ((computer.shop.num[1].number>0) && (computer.money >= computer.shop.num[1].price)) { shop_choose = 2; return 8; }//买灵药 
			else return 1;//加血 
		}
		if ((computer.shop.num[7].number>0) && (computer.money >= computer.shop.num[7].price) && (play.storepower>0)) { shop_choose = 8; return 8; }//买铁钟罩
		if ((computer.shop.num[6].number>0) && (computer.money >= computer.shop.num[6].price) && ((computer.defense + play.intelligence)<(play.attack + play.intelligence - 10)))
		{
			shop_choose = 7; return 8;//买金钟罩
		}
		return 1;
	}
	if ((play.blood - c_hurt_p_blood)<(2 * sqrt(huihe))) {
		if (r >= 4) return 3;
		else return 6;
	}
	if ((play.money >= play.shop.num[3].price) && (rand()%12 >= 5) && (play.shop.num[3].number > 0)) return 9;
	if ((play.money >= play.shop.num[2].price) && (rand()%13 >= 5) && (play.shop.num[2].number > 0)) return 9;
	if ((computer.money < computer.shop.num[0].price) && (r >= 5)) return 7;
	if (computer.command.BatNum <= 2 && play.command.BatNum>computer.command.BatNum&&(computer.money >= 2*computer.shop.num[8].price)&&r <= 6) { shop_choose = 9; return 8; }//买小兵 
	while (1) {
		int i=1;
		srand((unsigned)time((time_t*)NULL) * 13 + huihe + i);
		r = rand() % 10; //printf("%d ", r);
		switch (r) {
		case 0: return 2; break;
		case 1: if (computer.intelligence>20) return 3; if (rand() % 10 >= 7) return 3; break;
		case 2: if (computer.intelligence>20) return 4; if (rand() % 10 >= 7) return 4; break;
		case 3: if (computer.intelligence >= 15) return 5; if (rand() % 10 >= 5) return 5; if (computer.command.max<23) return 5; break;
		case 4: if ((HurtBlood(computer, play, computer.storepower)<play.blood - 2 * sqrt(huihe)) && (HurtBlood(computer, play, computer.storepower + 1)>play.blood - huihe))
			return 6;  break;
		case 5: if (computer.money <= computer.shop.num[2].price) return 7; break;
		case 6: if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[2].price&&rand()%11 >= 2&&computer.shop.num[2].number>0) 
                 { shop_choose = 3; return 8; }//买宝剑 
			if (computer.money >= computer.shop.num[4].price&&rand()%13 >= 3&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[3].price&&rand()%11 >= 2&&computer.shop.num[3].number>0) 
				 { shop_choose = 4; return 8; }//买铁剑 
			if (computer.money >= computer.shop.num[2].price&&rand()%13 >= 3&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			shop_choose = 9; return 8;//买小兵 
		} break;
		case 7: if (play.money > 125) return 9; break;
		case 8: return 2; break;
		case 9: if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[2].price&&rand()%11 >= 2&&computer.shop.num[2].number>0) 
                 { shop_choose = 3; return 8; }//买宝剑 
			if (computer.money >= computer.shop.num[4].price&&rand()%13 >= 3&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[3].price&&rand()%11 >= 2&&computer.shop.num[3].number>0) 
				 { shop_choose = 4; return 8; }//买铁剑 
			if (computer.money >= computer.shop.num[2].price&&rand()%13 >= 3&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			//shop_choose=9;return 8;//买小兵 
		} break;
		}
		i++;
	}
}

int com_choose_hard(general play, general computer, int &shop_choose) {
	int p_hurt_c_blood, c_hurt_p_blood, r;
	p_hurt_c_blood = HurtBlood(play, computer, play.storepower); c_hurt_p_blood = HurtBlood(computer, play, computer.storepower);
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	rand(); r = rand() % 10;
	if (p_hurt_c_blood>(computer.blood - 2 * sqrt(huihe))) {//加血
		if ((computer.shop.num[7].number > 0) && (computer.money >= computer.shop.num[7].price) && (play.storepower > 1) && (computer.blood>HurtBlood(play,computer,0))) { shop_choose = 8; return 8; }//买铁钟罩
		if ((computer.shop.num[0].number>0) && (computer.money >= computer.shop.num[0].price) && (computer.blood<15)) { shop_choose = 1; return 8; }//买灵桃 
		if (r >= 5) {
			if ((computer.shop.num[1].number > 0) && (computer.money >= computer.shop.num[1].price)) { shop_choose = 2; return 8; }//买灵药 
			else if (r >= 8) return 1;//加血 
		}
		if ((computer.shop.num[7].number > 0) && (computer.money >= computer.shop.num[7].price) && (play.storepower > 0) && (r > 3)) { shop_choose = 8; return 8; }//买铁钟罩
		if ((computer.shop.num[6].number>0) && (computer.money >= computer.shop.num[6].price) && ((computer.defense + play.intelligence)<(play.attack + play.intelligence - 10)))
		{shop_choose = 7; return 8;}//买金钟罩
		return 1;
	}
	if ((computer.storepower < 3) && (rand() % huihe > huihe/2 - 1)) 
        if (play.blood - HurtBlood(computer, play, computer.storepower + 1) < (3 * sqrt(huihe))&&rand()%13 > 3) return 6;
	if (computer.money >= computer.shop.num[3].price) {
		if (computer.money >= computer.shop.num[2].price)
			if (computer.shop.num[2].number>0) { shop_choose = 3; return 8; }//买宝剑 
		if (computer.shop.num[3].number>0) { shop_choose = 4; return 8; }//买铁剑 
	}
	if ((play.blood - c_hurt_p_blood) <= (2 * sqrt(huihe))) {
		if (r > 3) return 3;
		else return 6;
	}
	if ((play.money >= play.shop.num[3].price) && (rand()%12 > 3) && (play.shop.num[3].number > 0)) return 9;
	if ((play.money >= play.shop.num[2].price) && (rand()%13 > 3) && (play.shop.num[2].number > 0)) return 9;
	if (computer.money < computer.shop.num[2].price && computer.shop.num[2].number > 0 && (rand()%12 >= 3)) return 7;
	if (computer.money < computer.shop.num[3].price && computer.shop.num[3].number > 0 && (rand()%13 >= 3)) return 7;
	if (computer.attack > play.attack && computer.command.BatNum <= 2 && play.command.BatNum > computer.command.BatNum && (computer.money >= 2*computer.shop.num[8].price)) 
	    { shop_choose = 9; return 8; }//买小兵 
	while (1) {
		int i=1;
		srand((unsigned)time((time_t*)NULL) * 13 + huihe + i);
		r = rand() % 11; //printf("%d ", r);
		switch (r) {
		case 0: return 2; break;
		case 1: if ((computer.attack <= play.defense + 15 || computer.intelligence > 20) && huihe > 5) return 3; break;
		case 2: if (rand() % 17 > 5 && computer.intelligence > 20 && (computer.defense < play.attack)) return 4; break;
		case 3: if (computer.intelligence >= 18 && huihe >= 8 && computer.command.max < 20) return 5; 
			if ((computer.blood >= play.blood || computer.blood >= 50) && (computer.attack > play.attack && computer.defense > play.defense && computer.intelligence >= play.intelligence)) 
			    return 5; break;
		case 4: if ((HurtBlood(computer, play, computer.storepower)<play.blood - 2 * sqrt(huihe)) && (HurtBlood(computer, play, computer.storepower + 1)>play.blood - huihe))
			return 6;  break;
		case 5: if (computer.money <= computer.shop.num[2].price) {
			if (computer.money <= computer.shop.num[2].price && computer.shop.num[4].number > 0) return 7;
			if (computer.money <= computer.shop.num[2].price)
				if (computer.shop.num[5].number > 0 || computer.shop.num[3].number > 0) return 7;
			if (computer.blood < 50 && computer.money < computer.shop.num[0].price && computer.shop.num[0].number>0) return 7;
			if (computer.money < computer.shop.num[8].price && (rand() % 15 > 5)) return 7;
		}break;
		case 6: if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[4].price&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[2].price&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			shop_choose = 9; return 8;//买小兵 
		} break;
		case 7: if (play.money > 125) return 9; break;
		case 8: return 2; break;
		case 9:  if (computer.money >= computer.shop.num[8].price) {
			if (computer.money >= computer.shop.num[4].price&&rand()%14 >= 3&&computer.shop.num[4].number>0) 
			     { shop_choose = 5; return 8; }//买铠甲
			if (computer.money >= computer.shop.num[2].price&&rand()%15 >= 3&&computer.shop.num[2].number>0)
			     { shop_choose = 6; return 8; }//买战衣 
			if (computer.money > computer.shop.num[0].price && computer.shop.num[0].number > 0 && computer.blood < 15) 
			   { shop_choose = 1; return 8; }//买灵桃
		} break;
		case 10: if (computer.money <= computer.shop.num[2].price) {
			if (computer.money <= computer.shop.num[2].price && computer.shop.num[4].number > 0) return 7;
			if (computer.money <= computer.shop.num[2].price)
				if (computer.shop.num[5].number > 0 || computer.shop.num[3].number > 0) return 7;
			if (computer.blood < 50 && computer.money < computer.shop.num[0].price && computer.shop.num[0].number>0) return 7;
			if (computer.money < computer.shop.num[8].price && (rand() % 15 > 5)) return 7;
		}break;
		}
		i++;
	}
}

int com_strategyin(general &m, general &e, char character,int r) {
	int up, c, shop_choose = 0;
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	m.situation = 0;//情况置为 0 
	while (1) {
		system("cls");
		printf("\n------------------ 现在是 %c 进行操作 -------------------\n", character);
		printf("\n 电脑选择以下哪种策略?\n");
		printf(" 1:增加血量         2:增加智力         3:增加攻击力\n");
		printf(" 4:增加防御力       5:增加统率力       6:蓄力\n");
		printf(" 7:赚钱             8:打开商店         9:偷对方金钱\n");
		if(r==1) c = com_choose_easy(e, m, shop_choose);
		else if(r==2) c = com_choose_medium(e, m, shop_choose);
		else c = com_choose_hard(e, m, shop_choose);
		//printf("电脑选择了: %d\n", c);
		switch (c) {
		case 1:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower); */}
				 up = 28 + increase(m.intelligence, 3) + sqrt(2 * (huihe + 1) - 2 * m.times / 5); m.blood += up;
				 /*printf("血量增加了 %d.现在你的血量为:%d.\n", up, m.blood);*/ return 1; break;
		case 2:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 up = 3 + increase(m.intelligence, 2 * m.times++) - m.intelligence / 25; if (up<3) up = 3; m.intelligence += up;
				 /*printf("智力增加了 %d.现在你的智力为:%d.\n", up, m.intelligence);*/ return 1; break;
		case 3:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 up = 4 + increase(m.intelligence, 3); m.attack += up;
				 /*printf("攻击力增加了 %d.现在你的攻击力为:%d.\n", up, m.attack);*/ return 1; break;
		case 4:  if (m.storepower >= 1) { m.storepower--;/* printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 up = 5 + increase(m.intelligence, 3); m.defense += up;
				 /*printf("防御力增加了 %d.现在你的防御力为:%d.\n", up, m.defense);*/ return 1; break;
		case 5:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 up = 6 + increase(m.intelligence, 3); m.command.max += up;
				 /*printf("统率力增加了 %d.现在你的统率力为:%d.\n", up, m.command.max); */return 1; break;
		case 6:  if (m.storepower<3)  m.storepower++; /*printf("现在你的蓄力值为: %d\n", m.storepower); */return 1; break;
		case 7:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 up = 100 + rand() % ((m.intelligence + huihe) / 4 + 1) + (m.intelligence + huihe) / 4 + (m.intelligence - e.intelligence) / 3; m.money += up;
				 /*printf("金钱增加了 %d.现在你的金钱为: %d.\n", up, m.money);*/ return 1; break;
		case 8:  if (m.storepower >= 1) { m.storepower--; /*printf("现在你的蓄力值为: %d\n", m.storepower);*/ }
				 print_shop(m.shop);
				 while (1) {
					 //printf("\n你当前的金钱为: %d\n", m.money); printf("你想购买哪件商品?(请输入序号)\n");
					 if (purchase_one(m, shop_choose)) return 1;
					 else break;
				 }
				 break;
		case 9:  int steal_money, cm, oe; steal_money = e.money / 2;
			cm = (steal_money / 2 * (60 + (m.intelligence - e.intelligence)) / (60 + sqrt(huihe) + m.times));
			oe = (steal_money*(60 - e.intelligence) / (60 + huihe + e.times));
			if (cm<12) cm = 12; else if (cm >= oe) cm = oe - oe / 50;
			if (oe<18) oe = 18; else if (oe >= e.money) oe = e.money - oe / 50;
			m.money += cm; e.money -= oe;
			//printf("你偷了敌方 %d 金钱.对方损失了 %d 金钱.现在你的金钱为: %d.\n", cm, oe, m.money);
			return 1; break;
		default: printf("输入错误！请重新输入！\n");
		}
	}
}

void before_battle(general &A_player, general &B_player, int &lose_b, int &lose_m) {
	lose_m = (A_player.money + B_player.intelligence) / 4 - A_player.intelligence / 2;
	if (lose_m>A_player.money) lose_m = A_player.money; else if (lose_m<0) lose_m = 0;
	lose_b = A_player.blood / 6 + B_player.intelligence / (A_player.intelligence + huihe / 2) + 1;
	if(A_player.blood>3){
		if (lose_b<3) lose_b = 3;
	}
	else lose_b=1;
	A_player.money -= lose_m; A_player.blood -= lose_b;
}

int before_battle_computer_choose(general &player, general &computer) { //0为逃跑，1为不逃跑
	int hurtblood, rate;
	if (computer.escape_times >= 3) return 1;
	srand((unsigned)time((time_t*)NULL) * 13 + huihe); rate = rand() % 10;
	hurtblood = HurtBlood(player, computer, player.storepower);
	if ((computer.blood - hurtblood)<5) {
		if ((computer.situation > 0) || (computer.blood > hurtblood)) return 1;
		if (computer.blood < hurtblood) return 0;
		else return rand() % 2;
	}
	else return 1;
}

int battle_two(general &A_player, general &B_player) {
	strategyin(A_player, B_player, 'A');
	system("pause");
	strategyin(B_player, A_player, 'B');
	system("pause");
	while (1) {
		system("cls");
		printf("\n****************** 第 %d 次回合 ********************\n", huihe);
		printf(" 有无玩家选择战前逃跑？\n 1.A玩家战前逃跑\n 2.B玩家战前逃跑\n 3.无玩家逃跑\n");
		int choose, lose_b, lose_m; scanf("%d", &choose);
		switch (choose) {
		case 1:	if (A_player.escape_times >= 3) { printf("A玩家连续逃跑已经有3次，不能再继续逃跑！\n"); system("pause"); }
				else {
					before_battle(A_player, B_player, lose_b, lose_m); printf("A玩家连续逃跑已有 %d 次。\n", ++A_player.escape_times);
					printf("A玩家逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m); return 1;
				} break;
		case 2:	if (B_player.escape_times >= 3) printf("B玩家连续逃跑已经有3次，不能再逃跑！\n");
				else {
					before_battle(B_player, A_player, lose_b, lose_m); printf("B玩家连续逃跑已有 %d 次。\n", ++B_player.escape_times);
					printf("B玩家逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m); return 1;
				} break;
		case 3: A_player.escape_times = 0; B_player.escape_times = 0;
			system("cls"); printf("战斗开始！\n");//system("pause");system("cls");
			general_attack_way_two(A_player, B_player);
			batman_attack_way(B_player, A_player, 'B', 'A');
			batman_attack_way(A_player, B_player, 'A', 'B'); return 1; break;
		default: printf("输入错误！请重新输入！\n"); system("pause"); system("cls"); break;
		}
	}
}

int battle_one(general &A_player, general &B_player,int r) {
	strategyin(A_player, B_player, 'A');
	system("pause");
	com_strategyin(B_player, A_player, 'B',r);
	//system("pause");
	system("cls");
	while (1) {
		printf("\n****************** 第 %d 次回合 ********************\n", huihe);
		printf(" 你是否选择战前逃跑？\n 0.是的，我得暂避锋芒！\n 1.不，我要勇往直前！\n");
		int choose, lose_b, lose_m; scanf("%d", &choose);
		if (choose != 0 && choose != 1) { printf("请正确输入序号！(0或1)\n"); continue; }
		if (!choose) {
			if (A_player.escape_times >= 3) { printf("你连续逃跑已经有3次，不能再继续逃跑！\n"); system("pause"); continue; }
			before_battle(A_player, B_player, lose_b, lose_m);
			printf("你连续逃跑已有 %d 次。\n", ++A_player.escape_times);
			printf("你在逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m); return 1;
		}
		A_player.escape_times = 0;
		choose = before_battle_computer_choose(A_player, B_player);
		if (!choose) {
			before_battle(B_player, A_player, lose_b, lose_m);
			printf("电脑在此次战斗中选择了逃跑。\n电脑在逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m);
			printf("电脑连续逃跑已有 %d 次。\n", ++B_player.escape_times); return 1;
		}
		printf("电脑也选择了勇往直前！"); B_player.escape_times = 0;
		system("pause"); system("cls"); printf("                                  战斗开始！\n");
		general_attack_way_one(A_player, B_player); system("pause");
		batman_attack_way(B_player, A_player, 'B', 'A');
		batman_attack_way(A_player, B_player, 'A', 'B'); return 1;
	}
}

int c_text(general &A_player, general &B_player,int a,int b) {
	com_strategyin(A_player, B_player, 'A',a);
	//system("pause");
	com_strategyin(B_player, A_player, 'B',b);
	//system("pause");
	system("cls");
	while (1) {
		printf("\n****************** 第 %d 次回合 ********************\n", huihe);
		printf(" 有无玩家选择战前逃跑？\n 1.A玩家战前逃跑\n 2.B玩家战前逃跑\n 3.无玩家逃跑\n");
		int choose, lose_b, lose_m;
		choose = before_battle_computer_choose(B_player, A_player);
		if (!choose) {
			before_battle(A_player, B_player, lose_b, lose_m);
			printf("电脑A在此次战斗中选择了逃跑。\n电脑在逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m);
			printf("电脑A连续逃跑已有 %d 次。\n", ++A_player.escape_times); return 1;
		}
		printf("电脑A选择了勇往直前！"); A_player.escape_times = 0;
		choose = before_battle_computer_choose(A_player, B_player);
		if (!choose) {
			before_battle(B_player, A_player, lose_b, lose_m);
			printf("电脑B在此次战斗中选择了逃跑。\n电脑在逃跑过程中损失 %d 滴血，金钱损失 %d\n", lose_b, lose_m);
			printf("电脑B连续逃跑已有 %d 次。\n", ++B_player.escape_times); return 1;
		}
		printf("电脑B也选择了勇往直前！"); B_player.escape_times = 0;
		//system("pause"); 
		system("cls"); printf("                                  战斗开始！\n");
		general_attack_way_text(A_player, B_player); //system("pause");
		batman_attack_way(B_player, A_player, 'B', 'A');
		batman_attack_way(A_player, B_player, 'A', 'B'); return 1;
	}

}

void two_player(general &A_player, general &B_player) {
	printf("属性参考值为：100 30 20 10 15\n");
	printf("请输入 A 的属性:\n"); value(A_player);
	printf("请输入 B 的属性:\n"); value(B_player);
	value_shop(A_player.shop);
	value_shop(B_player.shop);
	print(A_player, B_player);
	while (A_player.blood>0 && B_player.blood>0) {
		system("pause");
		battle_two(A_player, B_player);
		//A_player.money+=5;
		//B_player.money+=5;
		print(A_player, B_player);
	}
	if (A_player.blood>B_player.blood) {
		printf("****************************************************\n");
		printf("      A 赢得了游戏！\n");
		printf("****************************************************\n");
	}
	else {
		printf("****************************************************\n");
		printf("      B 赢得了游戏！\n");
		printf("****************************************************\n");
	}
	printf("按回车键回到主菜单！\n");
	system("pause"); system("cls");
}

int one_player(general &A_player, general &B_player) {
	int n;
	printf("\n         游戏难度");
	printf("\n---------------------------\n");
	printf("          1.简单\n          2.中等\n          3.困难");
	printf("\n---------------------------\n");
	printf("请选择游戏难度："); scanf("%d", &n);
	while(n>3||n<1) { 
		printf("输入错误！请重新输入："); scanf("%d", &n);
	}
	/*if (n == 3) {
		system("cls");
		printf("\n--------------------------------\n");
		printf("\n   对不起，此难度还在开发中！");
		printf("\n--------------------------------\n");
		system("pause"); system("cls"); return 0;
	}*/
	system("cls");
	printf("属性参考值为：100 30 20 10 15\n");
	printf("请输入 A 的属性(A为玩家属性):\n"); value(A_player);
	printf("请输入 B 的属性(B为电脑属性):\n"); value(B_player);
	value_shop(A_player.shop);
	value_shop(B_player.shop);
	print(A_player, B_player);
	while (A_player.blood>0 && B_player.blood>0) {
		system("pause");
	    system("cls"); battle_one(A_player, B_player,n);
		//A_player.money+=5;
		//B_player.money+=5;
		print(A_player, B_player);
	}
	if (A_player.blood>B_player.blood) {
		printf("****************************************************\n");
		printf("      恭喜你！你赢了！\n");
		printf("****************************************************\n");
	}
	else {
		printf("****************************************************\n");
		printf("      很遗憾！你输了！\n");
		printf("****************************************************\n");
	}
	printf("按回车键回到主菜单！\n");
	system("pause"); system("cls"); return 1;
}

void computer_text(general &A_player, general &B_player) {//100 30 20 10 15
	int a, b;
	printf("\n         游戏难度");
	printf("\n---------------------------\n");
	printf("          1.简单\n          2.中等\n          3.困难");
	printf("\n---------------------------\n");
	printf("请分别为电脑A、B选择游戏难度：\n");
	printf("A为："); scanf("%d", &a); printf("B为："); scanf("%d", &b); system("cls");
	printf("属性参考值为：100 30 20 10 15\n");
	printf("请输入 A 的属性(A为电脑属性):\n"); value(A_player);
	printf("请输入 B 的属性(B为电脑属性):\n"); value(B_player);
	value_shop(A_player.shop);
	value_shop(B_player.shop);
	print(A_player, B_player);
	while (A_player.blood>0 && B_player.blood>0) {
		system("pause");
		c_text(A_player, B_player,a,b);
		//A_player.money+=5;
		//B_player.money+=5;
		print(A_player, B_player);
	}
	if (A_player.blood>B_player.blood) {
		printf("****************************************************\n");
		printf("      A 赢得了游戏！\n");
		printf("****************************************************\n");
	}
	else {
		printf("****************************************************\n");
		printf("      B 赢得了游戏！\n");
		printf("****************************************************\n");
	}
	printf("按回车键回到主菜单！\n");
	system("pause"); system("cls");
}

int main() {
	srand((unsigned)time((time_t*)NULL) * 13 + huihe);
	rand();
	int choose;
	while (1) {
		printf("\n           战斗策略小游戏");
		printf("\n---------------------------------------\n");
		printf("            1.游戏介绍\n            2.双人游戏\n            3.人机游戏\n            4.游戏测试\n            0.退出游戏");
		printf("\n---------------------------------------\n");
		printf("请选择序号: ");
		scanf("%d", &choose); huihe = 0;
		general A_player, B_player; system("cls");
		switch (choose) {
		case 1:game_profile(); break;
		case 2:two_player(A_player, B_player); break;
		case 3:one_player(A_player,B_player); break;
		case 4:computer_text(A_player, B_player); break;
		case 0:exit(0);
		default: printf("输入错误！请重新输入！\n");
		}
	}
}
