#include "allheader.h" 
#include "main.h"

 
int BallMoveTimer = 1;
int ShootBallTimer = 2; 
int BattleBallMoveTimer = 3;
int FoulTimer = 4;
int power = 0;  
double Radius = 0.34;   /* ��İ뾶 */
int ifstart = 0;
int usetimes1 = 0;
int usetimes2 = 0;
int interface = 0; 
int IfBattleStart = 0;
static double winwidth, winheight;   // ���ڳߴ�
extern void DrawBall(double x, double y, int number, string color);
extern void DrawTable(double x, double y);
extern void DrawWall(double startx, double starty, double endx, double endy);
extern ballstate;
extern double Distance();
extern Flick();
extern double mx;
extern double my;
extern int player;
extern void foul();
extern void InitLinkelist();
extern int IfScore;
extern HitFlag;
extern DrawBattleChoice();
string MODE[3] = {"������ϰ", "˫�˶�ս", "�о�����"}; 
int mode = 0;
extern int hittimes;
extern int maxtimes1;
extern int droptimes;
extern int maxtimes2;
extern int interface;
extern int ifwin2;
extern int score2;
extern void judge2();



// ��ʾ����
void display(void);

// �ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// ����¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	display(); // ˢ����ʾ
	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON && ball[0].ifdrop==0 && mx>=1.3 && mx<=23.2 && my>=0.9 && my<=12.7 && (interface == 3 || interface == 4 || interface == 5 )
		    && ball[0].speed==0 && ball[1].speed==0 
			&& ball[2].speed==0 && ball[3].speed==0 
			&& ball[4].speed==0 && ball[5].speed==0 
			&& ball[6].speed==0 && ball[7].speed==0 
			&& ball[8].speed==0 && ball[9].speed==0 
			&& ball[10].speed==0 && ball[11].speed==0 
			&& ball[12].speed==0 && ball[13].speed==0 
			&& ball[14].speed==0 && ball[15].speed==0)
		{
          
            startTimer(ShootBallTimer, 50);	
            if(interface==5){
            	hittimes++;
            }
		}
		else if (button == LEFT_BUTTON && ball[0].ifdrop==1 && mx>=2.215+Radius && mx<=22.285-Radius 
					&& my>=1.715+Radius && my<=11.785-Radius )
		{
			ball[0].ifdrop = 0;
			ball[0].x = mx;
			ball[0].y = my;
			if(interface==5){
           	droptimes++;
            }
		}
		break;

    case BUTTON_UP:
    	if(button == LEFT_BUTTON && mx>=1.3 && mx<=23.2 
		&& my>=0.9 && my<=12.7 && ball[0].ifdrop==0 && (interface == 3 || interface == 4 || interface == 5 )
		    && ball[0].speed==0 && ball[1].speed==0 
			&& ball[2].speed==0 && ball[3].speed==0 
			&& ball[4].speed==0 && ball[5].speed==0 
			&& ball[6].speed==0 && ball[7].speed==0 
			&& ball[8].speed==0 && ball[9].speed==0 
			&& ball[10].speed==0 && ball[11].speed==0 
			&& ball[12].speed==0 && ball[13].speed==0 
			&& ball[14].speed==0 && ball[15].speed==0)
    	{			
    	
        	Shoot();
    		cancelTimer(ShootBallTimer);
			power = 0;
    	}
//    	display();
    	break;
    
//	case MOUSEMOVE:
//		display();
//		break;

	default:
		break;
	}
}

// ��ʱ����Ӧ���� 
void TimerEventProcess(int timerID)
{
	int i;
	switch(timerID)
	{
		case 1:
			{
        	    for(i=0;i<=15;i++)
        	    {
        	    	if(ball[i].speed > 0)    
					{
						ball[i].speed -= 0.35; 

					}   	    	        	    		
					else
					{
						ball[i].speed = 0;
					}    	    		     	    		
        	    }
        	    		display();
						BallMove();
						break;
			}
			case 2:	
		{
			power++;
			break;
		}
		case 3:	
		{
			for(i=0;i<=15;i++)
        	    {
        	    	if(ball[i].speed > 0)    
					{
						ball[i].speed -= 0.35; 

					}   	    	        	    		
					else
					{
						ball[i].speed = 0;
					}    	    		     	    		
        	    }
        	    		display();
						BattleBallMove();
						break;
		}		
	}
}



void Main() 
{
//	InitConsole(); 
	
	SetWindowTitle("̨��");
	winwidth = 24.5;
    winheight = 17;
    SetWindowSize(winwidth, winheight);
// ��ô��ڳߴ�

    InitLinkelist();
    
    InitGraphics();
// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��

// ��С����ٺ�����ʱ��	
	
}

void display()
{
	int i,a,j,k;
	if(interface == 0){
		DisplayClear();
		DrawBackground0();
		drawButtons0();
	}
	if(interface == 1){
		DisplayClear();
		DrawBackground1();
		drawButtons1();
		
		SetPointSize(18);
    	SetPenColor("White");
		MovePen(3.5,11.5);
		DrawTextString("1.���������������������ͷź����");
		MovePen(3.5,10.5);
		DrawTextString("2.˫�˶�սģʽ�£���һ������ĳ�֣���ɫ����ɫ��������������һ�ֻ�ɫ���򱾳��������������");
		MovePen(3.5,9.5);
		DrawTextString("3.˫�˶�սģʽ�£�������δ�����������򣬷���");
		MovePen(3.5,8.5);
		DrawTextString("4.˫�˶�սģʽ�£�������ʱ��һ���������Ĳ�����ȷ���������࣬����");
		MovePen(3.5,7.5);
		DrawTextString("5.˫�˶�սģʽ�£���ĸ���붴������");
		MovePen(3.5,6.5);
		DrawTextString("6.˫�˶�սģʽ�£������������򻹴�����̨��ʱ��8��������붴���������");
		MovePen(3.5,5.5);
		DrawTextString("7.˫�˶�սģʽ�£���������Ӧ���л�ɫ���붴��8��������붴��Ӯ�ñ���");
		MovePen(3.5,4.5);
		DrawTextString("8.˫�˶�սģʽ�£��������Σ��������");
		MovePen(3.5,3.5);
		DrawTextString("9.˫�˶�սģʽ�£�����󣬽�����Ȩ");
		MovePen(3.5,2.5);
		DrawTextString("10.�о�ģʽ�£��������������35�λ����������Σ���������������ɲ鿴��д�����а�");
		
	}
	if(interface == 2){
		DisplayClear();
		DrawBackground2();
		SetPointSize(18);
    	SetPenColor("White");
		MovePen(3.5,11.5);
		DrawTextString("����Ϸ������ʱ����Դ�ĥ��");
		MovePen(3.5,10.5);
		DrawTextString("��Ȼ��Ȼ����һЩ���⣬���ǿ��Ի������С�");
		MovePen(3.5,9.5);
		DrawTextString("����Ϸ�����У����ܴ��ڿ��٣������ĵȴ���");
		MovePen(3.5,8.5);
		DrawTextString("����������ֹͣ���ٲ�����Ӧ��ť��");
		MovePen(3.5,7.5);
		DrawTextString("��л����֧�֣�");
		drawButtons1();
	}
	if(interface == 3 ){
	    // ����
		DisplayClear();
		DrawBackground3();
		DrawTable(1, 0.5);
		DrawBoard();
	    drawButtons3();
	    // ��ʼ��С��λ�� 
		
		if (ball[0].ifdrop == 0){
			DrawBall(ball[0].x,ball[0].y,0,ball[0].color);
		}else if ( mx>=2.215+Radius && mx<=22.285-Radius 
		&& my>=1.715+Radius && my<=11.785-Radius ) {
			DrawBall0();
		}
		// ����С�� 
		for(i=1;i<=15;i++){
			DrawBall(ball[i].x,ball[i].y,i,ball[i].color);
		} 
		if(ifstart){
		    if(ball[0].ifdrop==0 && mx>=1.3 && mx<=23.2 && my>=0.9 && my<=12.7 
			&& ball[0].speed==0 && ball[1].speed==0 
			&& ball[2].speed==0 && ball[3].speed==0 
			&& ball[4].speed==0 && ball[5].speed==0 
			&& ball[6].speed==0 && ball[7].speed==0 
			&& ball[8].speed==0 && ball[9].speed==0 
			&& ball[10].speed==0 && ball[11].speed==0 
			&& ball[12].speed==0 && ball[13].speed==0 
			&& ball[14].speed==0 && ball[15].speed==0)
			{
	    	    DrawCue(0.5+power/10);
	        }
		}
		
		Flick();
	//	FlickWall();
	    WallJudge();
	}
	if(interface == 4)
	{
		DisplayClear();
		DrawBackground4();
		DrawTable(1, 0.5);
		DrawBattleBoard();
		DrawReturnBotton();
	
		if (ball[0].ifdrop == 0){
			DrawBall(ball[0].x,ball[0].y,0,ball[0].color);
		}else if ( mx>=2.215+Radius && mx<=22.285-Radius 
		&& my>=1.715+Radius && my<=11.785-Radius ){
			DrawBall0();
		}
		
		for(i=1;i<=15;i++){
			DrawBall(ball[i].x,ball[i].y,i,ball[i].color);
		}		
	
		    if(ball[0].ifdrop==0 && mx>=1.3 && mx<=23.2 && my>=0.9 && my<=12.7 
			&& ball[0].speed==0 && ball[1].speed==0 
			&& ball[2].speed==0 && ball[3].speed==0 
			&& ball[4].speed==0 && ball[5].speed==0  
			&& ball[6].speed==0 && ball[7].speed==0 
			&& ball[8].speed==0 && ball[9].speed==0 
			&& ball[10].speed==0 && ball[11].speed==0 
			&& ball[12].speed==0 && ball[13].speed==0 
			&& ball[14].speed==0 && ball[15].speed==0)
			{
			    DrawBattleChoice();
	    	    DrawCue(0.5+power/5);
	        }
	        		
				
		Flick();
	    WallJudge();
	}
	if(interface == 5){
		DisplayClear();
		DrawBackground3();
		DrawTable(1, 0.5);
		DrawDecryptBoard();
	    drawButtons5();
	    // ��ʼ��С��λ�� 
	    if (ball[0].ifdrop == 0){
			DrawBall(ball[0].x,ball[0].y,0,ball[0].color);
		}
		else if (mx>=2.215+Radius && mx<=22.285-Radius 
		&& my>=1.715+Radius && my<=11.785-Radius )
		{
			DrawBall0();
		}	
		// ����С�� 
		for(i=1;i<=8;i++){
			DrawBall(ball[i].x,ball[i].y,i,ball[i].color);
		} 
		if(ifstart){
		    if(ball[0].ifdrop==0 && mx>=1.3 && mx<=23.2 && my>=0.9 && my<=12.7 
			&& ball[0].speed==0 && ball[1].speed==0 
			&& ball[2].speed==0 && ball[3].speed==0 
			&& ball[4].speed==0 && ball[5].speed==0 
			&& ball[6].speed==0 && ball[7].speed==0 
			&& ball[8].speed==0 && ball[9].speed==0 
			&& ball[10].speed==0 && ball[11].speed==0 
			&& ball[12].speed==0 && ball[13].speed==0 
			&& ball[14].speed==0 && ball[15].speed==0)
			{
	    	    DrawCue(0.5+power/10);
	        }
		}
		
		Flick();
	    WallJudge();
	    judge2();
	    judge1();
	}
	if(interface == 14)
	{
		DisplayClear();
		DrawBackground4();
		DrawChoiceBotton();
	}
	if(interface == 15)
	{
		DisplayClear();
		DrawBackground4();
		DrawFileBotton(); 

	}
	if(interface == 16)
	{
		DisplayClear();
		DrawBackground4();
		DrawWinner(); 
	}
	if(interface == 21){
		DisplayClear();
		DrawBackground21();

	}
	if(interface == 22){
		DisplayClear();
		DrawBackground22();

	}
	if(interface == 23){
		DisplayClear();
		DrawBackground23();
        read2(); 
	}
	if(interface == 23){
		DisplayClear();
		DrawBackground23();
        read2(); 
	}
}

