#include "allheader.h" 
#include "main.h"

 
int BallMoveTimer = 1;
int ShootBallTimer = 2; 
int BattleBallMoveTimer = 3;
int FoulTimer = 4;
int power = 0;  
double Radius = 0.34;   /* 球的半径 */
int ifstart = 0;
int usetimes1 = 0;
int usetimes2 = 0;
int interface = 0; 
int IfBattleStart = 0;
static double winwidth, winheight;   // 窗口尺寸
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
string MODE[3] = {"单人练习", "双人对战", "残局迷云"}; 
int mode = 0;
extern int hittimes;
extern int maxtimes1;
extern int droptimes;
extern int maxtimes2;
extern int interface;
extern int ifwin2;
extern int score2;
extern void judge2();



// 显示函数
void display(void);

// 字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	mx = ScaleXInches(x);
	my = ScaleYInches(y);
	display(); // 刷新显示
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

// 计时器响应函数 
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
	
	SetWindowTitle("台球");
	winwidth = 24.5;
    winheight = 17;
    SetWindowSize(winwidth, winheight);
// 获得窗口尺寸

    InitLinkelist();
    
    InitGraphics();
// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器

// 打开小球减速函数计时器	
	
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
		DrawTextString("1.长按鼠标左键进行蓄力，释放后击球");
		MovePen(3.5,10.5);
		DrawTextString("2.双人对战模式下，当一方击打某种（花色、纯色）球数量大于另一种花色，则本场比赛击打该种球");
		MovePen(3.5,9.5);
		DrawTextString("3.双人对战模式下，若击球未触碰到任意球，犯规");
		MovePen(3.5,8.5);
		DrawTextString("4.双人对战模式下，若击球时第一个触碰到的不是已确定的球种类，犯规");
		MovePen(3.5,7.5);
		DrawTextString("5.双人对战模式下，若母球入洞，犯规");
		MovePen(3.5,6.5);
		DrawTextString("6.双人对战模式下，在其他任意球还存在在台上时将8号球击打入洞，输掉比赛");
		MovePen(3.5,5.5);
		DrawTextString("7.双人对战模式下，当己方对应所有花色球都入洞后将8号球击打入洞，赢得比赛");
		MovePen(3.5,4.5);
		DrawTextString("8.双人对战模式下，犯规三次，输掉比赛");
		MovePen(3.5,3.5);
		DrawTextString("9.双人对战模式下，犯规后，交换球权");
		MovePen(3.5,2.5);
		DrawTextString("10.残局模式下，若击球次数多余35次或白球进洞三次，则输掉比赛，随后可查看或写入排行榜");
		
	}
	if(interface == 2){
		DisplayClear();
		DrawBackground2();
		SetPointSize(18);
    	SetPenColor("White");
		MovePen(3.5,11.5);
		DrawTextString("本游戏历经长时间调试打磨，");
		MovePen(3.5,10.5);
		DrawTextString("虽然仍然存在一些问题，但是可以基本运行。");
		MovePen(3.5,9.5);
		DrawTextString("本游戏过程中，可能存在卡顿，请耐心等待。");
		MovePen(3.5,8.5);
		DrawTextString("请在所有球都停止后再操作对应按钮。");
		MovePen(3.5,7.5);
		DrawTextString("感谢您的支持！");
		drawButtons1();
	}
	if(interface == 3 ){
	    // 清屏
		DisplayClear();
		DrawBackground3();
		DrawTable(1, 0.5);
		DrawBoard();
	    drawButtons3();
	    // 初始化小球位置 
		
		if (ball[0].ifdrop == 0){
			DrawBall(ball[0].x,ball[0].y,0,ball[0].color);
		}else if ( mx>=2.215+Radius && mx<=22.285-Radius 
		&& my>=1.715+Radius && my<=11.785-Radius ) {
			DrawBall0();
		}
		// 绘制小球 
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
	    // 初始化小球位置 
	    if (ball[0].ifdrop == 0){
			DrawBall(ball[0].x,ball[0].y,0,ball[0].color);
		}
		else if (mx>=2.215+Radius && mx<=22.285-Radius 
		&& my>=1.715+Radius && my<=11.785-Radius )
		{
			DrawBall0();
		}	
		// 绘制小球 
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

