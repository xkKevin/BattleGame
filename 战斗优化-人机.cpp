#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
int huihe=0;
//²Î¿¼Öµ£º100 30 20 10
/*typedef struct batman{
	int quantity;
	int blood=30;//100--200
	int attact=10,defence=5;//25 10
}batman;*/
typedef struct general{
	int blood;//100--200
	int attack,defense;//50--80  20--50
	int intelligence;//20--50
	//batman command;
	int times=3;
}general; 
int increase(int x,int t) {
	int d,m=sqrt(2*(x+t)/t);
	d=rand()%(m);
	if(d<=m/2) return d+(m+1)/3+rand()%((x+t)/(6+t)+1)-1;
	else return d+rand()%((x+t)/(6+t)+1)-1;
}
int harm(general x,general y){
	int h;
	h=x.attack*(1+x.intelligence/(100+huihe))-y.defense*(1+y.intelligence/(100+huihe));
	if(h>(x.attack-y.defense+x.intelligence/10)+1) return (h-rand()%(y.intelligence/5+1)-y.intelligence/8+1);
	else if(h<(x.attack-y.defense-y.intelligence/10)-1) return (h+rand()%(x.intelligence/5+1)+x.intelligence/8-1);
	else return (h+rand()%(x.intelligence/10+1)-1);
}
void value(general &m){
	printf("Blood Attack Defense Intelligence:");
	scanf("%d %d %d %d",&m.blood,&m.attack,&m.defense,&m.intelligence);
}
void print(general me,general enemy){
	printf("\n************** The %dth battle's result *****************\n",huihe);
	printf("Your general:\nBlood: %d  Attack: %d  Defense: %d  Intelligence: %d\n",me.blood,me.attack,me.defense,me.intelligence);
	printf("Enemy general:\nBlood: %d  Attack: %d  Defense: %d  Intelligence: %d\n",enemy.blood,enemy.attack,enemy.defense,enemy.intelligence);
	printf("********************************************************\n");
}
void strategyin(general &m,char c){
	int up;
	srand((unsigned)time(NULL));
	switch(c){
		case '1':up=28+increase(m.intelligence,3)+sqrt(2*(huihe+1)-2*m.times/5);m.blood+=up;printf("The blood has added %d.Now the blood:%d.\n",up,m.blood);break;
		case '2':up=3+increase(m.intelligence,m.times++);m.intelligence+=up;printf("The intelligence has added %d.Now your intelligence:%d.\n",up,m.intelligence);break;
		case '3':up=4+increase(m.intelligence,3);m.attack+=up;printf("The attack has added %d.Now the attack:%d.\n",up,m.attack);break;
		case '4':up=5+increase(m.intelligence,3);m.defense+=up;printf("The defense has added %d.Now the defense:%d.\n",up,m.defense);break;
		default: printf("Input error!\n");
	}
}
int strategyat(general me,general enemy){
	int eattackm,mattacke;
	if(huihe<=3) return rand()%3+2;
	eattackm=enemy.attack*(1+enemy.intelligence/(100+huihe))-me.defense*(1+me.intelligence/(100+huihe));
	mattacke=me.attack*(1+me.intelligence/(100+huihe))-enemy.defense*(1+enemy.intelligence/(100+huihe));
	if(me.blood>=35+sqrt(2*huihe)){
		if(enemy.blood<25+sqrt(2*huihe)||mattacke>=enemy.blood) return 3;
		if(eattackm>10) return 4;
		if(mattacke<=6) return 3;
	    else return 2;
	}
	else{
		if(me.blood<=10) {me.blood+=5;return 1;}
		if(mattacke>=enemy.blood&&eattackm<me.blood) return 3;
		if(me.blood<30)  {me.blood+=2;return 1;}
		else return rand()%3+2;
	} 
}
void battle(general &me,general &enemy){
	int im,ie,rm,re;
	printf("\n----------------Now is your operation!------------------\n");
	printf("What kind of selections do you want to choose?\n");
	printf("1:Add your blood            2:Increase your intelligence     \n3:Strengthen your attack    4:Strengthen your defense\n");
	scanf("%d",&im);
	//im=strategyat(me,enemy);
	printf("Your choose: %d\n",im);
	strategyin(me,im+48);
	system("pause");
	printf("\n---------------Now is enemy operation!------------------\n");
    ie=strategyat(enemy,me);
	printf("Enemy choose: %d\n",ie);
	strategyin(enemy,ie+48);printf("\n");
	rm=harm(me,enemy);
	if(rm<=2) rm=3;
	enemy.blood-=rm;printf("You attack enemy %d blood. Now the enemy's blood: %d.\n",rm,enemy.blood);
	re=harm(enemy,me);
	if(re<=2) re=3;
	me.blood-=re;printf("Enemy attack you %d blood. Now your blood:%d.\n",re,me.blood);
}
void winner(general &me,general &enemy){
	int rm,re;
	while(me.blood>0&&enemy.blood>0){
	    system("cls");
		print(me,enemy);
	    battle(me,enemy);huihe++;
		print(me,enemy);
		system("pause");
	}
	if(me.blood>enemy.blood) {
		printf("********************************************************\n");
	    printf("   Congratulation!You win the game!\n");
	    printf("********************************************************\n");
	}
	else {
		printf("********************************************************\n");
		printf("What a pity!You have been defeated!\n");
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
