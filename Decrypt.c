#include "action.h"

 
int hittimes = 0;
int maxtimes1 = 35;
int droptimes = 0;
int maxtimes2 = 2;
int score2 = 0;
int score1 = 0;
extern int interface;
int IFDROP[9]={0,0,0,0,0,0,0,0,0};
int userhitnow[1];
int userscorenow[1];
extern int ifstart;

int ifwrite = 0;

void GetScore(){
	int i;
	int n = 0;
	for(i=1;i<=8;i++){
		if(ball[i].ifdrop == 1){
			n++;
		}
	}score2=n;
}

void judge2(){
	if(hittimes>maxtimes1 || droptimes>maxtimes2){
		userhitnow[1]=hittimes;
		userscorenow[1]=score2;
		interface = 21;
	}else if(score2>=8){
		userhitnow[1]=hittimes;
		userscorenow[1]=score2;
		interface = 22;
	}
}

void judge1(){
	int i;
	double bx, by;
	for(i=1;i<=8;i++){
		if(ball[i].ifdrop!=IFDROP[i]){
			bx=hole[score2-1].x;
			by=hole[score2-1].y;
			hole[score2-1].x=25+score2;
			hole[score2-1].y=25;
			ball[i].x=bx+0.2;
			ball[i].y=by;
			IFDROP[i]=ball[i].ifdrop;
		}
	}
}

void DrawDecryptBoard()
{
	int i;
	SetFont("Default");
    SetPenColor("White");
	DefineColor("Board1", .46, .53, .72);
	SetPenColor("Board1");
	SetPenSize(7);
	
	StartFilledRegion(1);
	MovePen(12.25, 15.75);
	DrawLine(-10.25,0);
	DrawArc(0.25, 90, 127);
	DrawLine(1.2, -1.6);
	DrawArc(0.25, 217, 53);
	DrawLine(18.1, 0);
	DrawArc(0.25, -90, 53);
	DrawLine(1.2, 1.6);
	DrawArc(0.25, -37, 127);
	DrawLine(-10.25,0);
	EndFilledRegion();
    
    DefineColor("Board3", .15, .14, .31);
    SetPenColor("Board3");
    SetPenSize(1);
	StartFilledRegion(1);
	MovePen(12.25, 15.75);
	DrawLine(-10.25,0);
	DrawArc(0.25, 90, 127);
	DrawLine(1.2, -1.6);
	DrawArc(0.25, 217, 53);
	DrawLine(18.1, 0);
	DrawArc(0.25, -90, 53);
	DrawLine(1.2, 1.6);
	DrawArc(0.25, -37, 127);
	DrawLine(-10.25,0);
	EndFilledRegion();
    
    DefineColor("Board2", .23, .20, .39);
	SetPenColor("Board2");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(12.25, 15.75);
	DrawLine(-10.25,0);
	DrawArc(0.25, 90, 127);
	DrawLine(0.4, -0.8/3*2);
	DrawArc(0.25, 217, 53);
	DrawLine(19.7, 0);
	DrawArc(0.25, -90, 53);
	DrawLine(0.4, 0.8/3*2);
	DrawArc(0.25, -37, 127);
	DrawLine(-10.25,0);
    EndFilledRegion();
    
    DefineColor("hole", .6, .6, .75);
    SetPenColor("hole");
    
	for(i=0;i<8;i++){
		StartFilledRegion(1);
		MovePen(hole[i].x+0.34, hole[i].y);
		DrawArc(0.34, 0, 360);
		EndFilledRegion();
    }
    
    SetPenColor("White"); 
    MovePen(6, 15);
    DrawTextString("击球次数：");
    string HITTIMES = IntegerToString(hittimes);
    DrawTextString(HITTIMES);
    MovePen(10, 15);
    DrawTextString("白球落袋次数：");
    string DROPTIMES = IntegerToString(droptimes);
    DrawTextString(DROPTIMES);
    GetScore();
    MovePen(16, 15);
    DrawTextString("获得分数：");
    string SCORE2 = IntegerToString(score2); 
    DrawTextString(SCORE2);
}


void read2()
{
    static int userhit[100];
    static int userscore[100];
	
	FILE *file;
	file = fopen("Decrypt.txt", "r");
	
	string str1,str2,str3,str0;
	int t;

	int i = 1; 
	int n, j, max;
    if (!file)
    {
        drawLabel(9, 6, "读取失败");
    }
	else{
		rewind(file);
		while(!feof(file)) {
    	fscanf(file, "%d", &userscore[i]);
    	fscanf(file, "%d", &userhit[i]); 
    	i++;
    }
    n=i;

    } 
	for (i=1;i<=n;i++)
	{
		max=i;
		for(j=i+1;j<=n;j++){
			if(userscore[j]>userscore[max])
			{
				max=j;
			}
			else if(userscore[j]==userscore[max])
			{
				if(userhit[j]<userhit[max])
				{
				max=j;
				}
			}
			t=userscore[i];
			userscore[i]=userscore[max];
			userscore[max]=t;
			t=userhit[i];
			userhit[i]=userhit[max];
			userhit[max]=t;
		}
	}
	drawLabel(6, 11, "名次                            分数                            击球次数");
	for(i=1;i<n;i++)
	{
		str1=IntegerToString(i);
		str2=IntegerToString(userscore[i]);
		str3=IntegerToString(userhit[i]);
		str0="                                      ";
		str1=Concat(str1,str0);
		str1=Concat(str1,str2);
		str1=Concat(str1,str0);
		str1=Concat(str1,str3);
		
		drawLabel(6, 11-i, str1);
	}
	
	if(file){
		fclose(file);
	}
	 
}


void write2()
{
    FILE *file;
	file = fopen("Decrypt.txt", "a");
    if (!file)
    {
        drawLabel(9, 6, "写入失败");
    }else{
    	if(ifwrite==0){
			fprintf(file, "%d %d ", userscorenow[1], userhitnow[1]);
    	ifwrite=1;
    	}
    }
    if(file)
    {
    	fclose(file);
    }
    	
} 


void DrawBackground21()
{
	int i, j;
	DefineColor("background1", .15, .14, .31);
	DefineColor("background2", .23, .20, .39);
	SetPenColor("background1");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(0, 0);
	DrawLine(24.5, 0);
	DrawLine(0, 17);
	DrawLine(-24.5, 0);
	DrawLine(0, -17);
    EndFilledRegion();
    SetPenColor("background2");
    for(i=0;i<4;i++){
    	for(j=0;j<4;j++){
    		MovePen(-2+10*i, -1.5+10*j);
    		StartFilledRegion(1);
    		DrawLine(5, 5);
    		DrawLine(5, -5);
    		DrawLine(-5, -5);
    		DrawLine(-5, 5);
    		EndFilledRegion();
    	}
    }
    SetPointSize(60);
    SetPenColor("White");
    MovePen(9,10);
    DrawTextString("You Lose");
    SetPointSize(18);
    if (button(GenUIID(0), 16, 5, 4.5, 1.5, "返回标题界面"))
	{
		interface = 0;
		hittimes = 0;
		score2 = 0;
		droptimes = 0;
		for(i=0;i<=8;i++){
			IFDROP[i]=0;
			ball[i].ifdrop=0;
		}
	}
	if (button(GenUIID(0), 10, 5, 4.5, 1.5, "写入排行榜"))
	{

		write2();
		
	}
	if (button(GenUIID(0), 4, 5, 4.5, 1.5, "打开排行榜"))
	{
		interface=23;
	}
}





void DrawBackground22()
{
	int i, j;
	DefineColor("background1", .15, .14, .31);
	DefineColor("background2", .23, .20, .39);
	SetPenColor("background1");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(0, 0);
	DrawLine(24.5, 0);
	DrawLine(0, 17);
	DrawLine(-24.5, 0);
	DrawLine(0, -17);
    EndFilledRegion();
    SetPenColor("background2");
    for(i=0;i<4;i++){
    	for(j=0;j<4;j++){
    		MovePen(-2+10*i, -1.5+10*j);
    		StartFilledRegion(1);
    		DrawLine(5, 5);
    		DrawLine(5, -5);
    		DrawLine(-5, -5);
    		DrawLine(-5, 5);
    		EndFilledRegion();
    	}
    }
    SetPointSize(60);
    SetPenColor("White");
    MovePen(9,10);
    DrawTextString("You Win");
    SetPointSize(18);
    if (button(GenUIID(0), 16, 5, 4.5, 1.5, "返回标题界面"))
	{
		interface = 0;
		hittimes = 0;
		score2 = 0;
		droptimes = 0;
		for(i=0;i<=8;i++){
			IFDROP[i]=0;
			ball[i].ifdrop=0;
		}
	}
	if (button(GenUIID(0), 10, 5, 4.5, 1.5, "写入排行榜"))
	{

		write2();
        
	}
	if (button(GenUIID(0), 4, 5, 4.5, 1.5, "查看排行榜"))
	{
		interface = 24;
		
	}
}

void DrawBackground23()
{
	int i, j;
	DefineColor("background1", .15, .14, .31);
	DefineColor("background2", .23, .20, .39);
	SetPenColor("background1");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(0, 0);
	DrawLine(24.5, 0);
	DrawLine(0, 17);
	DrawLine(-24.5, 0);
	DrawLine(0, -17);
    EndFilledRegion();
    SetPenColor("background2");
    for(i=0;i<4;i++){
    	for(j=0;j<4;j++){
    		MovePen(-2+10*i, -1.5+10*j);
    		StartFilledRegion(1);
    		DrawLine(5, 5);
    		DrawLine(5, -5);
    		DrawLine(-5, -5);
    		DrawLine(-5, 5);
    		EndFilledRegion();
    	}
    }
    SetPointSize(60);
    SetPenColor("White");
    MovePen(9.5,13);
    DrawTextString("排行榜");
    SetPointSize(18);
    if (button(GenUIID(0), 4, 13, 1.8, 0.8, "返回"))
	{
		interface = 21;
	}
}

void DrawBackground24()
{
	int i, j;
	DefineColor("background1", .15, .14, .31);
	DefineColor("background2", .23, .20, .39);
	SetPenColor("background1");
	SetPenSize(1);
	StartFilledRegion(1);
	MovePen(0, 0);
	DrawLine(24.5, 0);
	DrawLine(0, 17);
	DrawLine(-24.5, 0);
	DrawLine(0, -17);
    EndFilledRegion();
    SetPenColor("background2");
    for(i=0;i<4;i++){
    	for(j=0;j<4;j++){
    		MovePen(-2+10*i, -1.5+10*j);
    		StartFilledRegion(1);
    		DrawLine(5, 5);
    		DrawLine(5, -5);
    		DrawLine(-5, -5);
    		DrawLine(-5, 5);
    		EndFilledRegion();
    	}
    }
    SetPointSize(60);
    SetPenColor("White");
    MovePen(9.5,13);
    DrawTextString("排行榜");
    SetPointSize(18);
    if (button(GenUIID(0), 4, 13, 1.8, 0.8, "返回"))
	{
		interface = 22;
	}
}

void drawButtons5()
{
	int i;
	double h = GetWindowHeight()/20;
	double x = GetWindowWidth()/12;  
	double y = GetWindowHeight()*18.85/20; 
	double w = GetWindowWidth()/12; // 控件宽度
	
	DefineColor("Color1", .15, .14, .31);
	DefineColor("Color2", .23, .20, .39);
	setButtonColors ("Color1", "White", "Color2", "White", 1);
	if (button(GenUIID(0), 5.5*x, y, w, h, ifstart ? "暂停" : "开始"))
	{
		ifstart = ! ifstart;
	}
	if (button(GenUIID(0), 9*x, y, 2*w, h, "返回标题界面"))
	{
		interface = 0;
		hittimes = 0;
		score2 = 0;
		droptimes = 0;
		for(i=0;i<=8;i++){
			IFDROP[i]=0;
			ball[i].ifdrop=0;
		}
	}
	
}





