#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int timeb=2,timea=2,timed=2,timei=2,huihe=0;
//²Î¿¼Öµ£º100 30 20 10 
typedef struct batman{
	int quantity;
	int blood;//100--200
	int attact,defence;//25 10
}batman;
typedef struct general{
	int blood;//100--200
	int attack,defense;//50--80  20--50
	int intelligence;//20--50
	//batman command;
}general; 
int IT(int x, int y) {
	return (rand()%((x)/(y)+1)+(sqrt(x))/(y));
}
void value(general &m){
	printf("Blood Attack Defense Intelligence:");
	scanf("%d %d %d %d",&m.blood,&m.attack,&m.defense,&m.intelligence);
}
void print(general me,general enemy){
	printf("\n************** The %dth battle's result *****************\n",huihe);
	printf("Your general:\nBlood: %d  Attact: %d  Defense: %d  Intelligence: %d\n",me.blood,me.attack,me.defense,me.intelligence);
	printf("Enemy general:\nBlood: %d  Attact: %d  Defense: %d  Intelligence: %d\n",enemy.blood,enemy.attack,enemy.defense,enemy.intelligence);
	printf("********************************************************\n");
}
void strategy(general &m,char c){
	int up;
	srand((unsigned)time(NULL));
	switch(c){
		case '1':up=28+IT(m.intelligence,2*timeb++);m.blood+=up;printf("The blood has added %d.Now the blood:%d.\n",up,m.blood);break;
		case '2':up=2+IT(m.intelligence,2*timei++);m.intelligence+=up;printf("The intelligence has added %d.Now your intelligence:%d.\n",up,m.intelligence);break;
		case '3':up=4+IT(m.attack,2*timea++);m.attack+=up;printf("The attack has added %d.Now the attack:%d.\n",up,m.attack);break;
		case '4':up=5+IT(m.defense,2*timed++);m.defense+=up;printf("The defense has added %d.Now the defense:%d.\n",up,m.defense);break;
		default: printf("Input error!\n");
	}
}
void battle(general &me,general &enemy){
	int i,rm,re,down;
	printf("\n----------------Now is your operation!------------------\n");
	printf("What kind of selections do you want to choose?\n");
	printf("1:Add your blood            2:Increase your intelligence     \n3:Strength your attack      4:Strength your defense\n");
	//scanf("%d",&i);
	if(me.blood<=35) {i=1;}
	else i=rand()%3+2;
	strategy(me,i+48);
	rm=IT(me.attack,2)+IT(me.intelligence,3);down=rm-IT(enemy.defense,2);
	if(down<=2) down=5;
	enemy.blood-=down;printf("You attack enemy %d blood.Now the enemy's blood:%d.\n",down,enemy.blood);
	printf("\n---------------Now is enemy operation!------------------\n");
	if(enemy.blood<=35) {i=1;if(enemy.blood<=10) enemy.blood+=10; else enemy.blood+=1;}
	else i=rand()%3+2;
	strategy(enemy,i+48);
	re=IT(enemy.attack,2)+IT(enemy.intelligence,3);down=re-IT(me.defense,2);
	if(down<=2) down=3;
	me.blood-=down;printf("Enemy attack you %d blood.Now your blood:%d.\n",down,me.blood);
}
void winner(general &me,general &enemy){
	int rm,re;
	while(me.blood>0&&enemy.blood>0){
	    battle(me,enemy);
		//print(me,enemy);
		system("cls");
		huihe++;
		print(me,enemy);	
	}
	if(me.blood>enemy.blood) {
		printf("********************************************************\n");
	    printf("   Congratulation!You win the game!\n");
	    printf("********************************************************\n");
	}
	else {
		printf("********************************************************\n");
		printf("What a pity!You have defeated!");
		printf("********************************************************\n");
	}	
}
int main(){
	srand((unsigned)time((time_t*)NULL));
	rand();
	general me,enemy;
	printf("Please input your general attributes:\n");value(me);
	printf("Please input the enemy general attributes:\n");value(enemy);
	print(me,enemy);
	winner(me,enemy);
}
