////////////////////////////////////////////////////////////////////////////
//实验要求：(1)理解glut程序框架                                           //
//          (2)理解窗口到视区的变换                                       // 
//          (3)理解OpenGL实现动画的原理                                   //   
//          (4)添加代码实现中点Bresenham算法画直线                        //
//          (5)添加代码实现改进Bresenham算法画直线                        //
//          (6)添加代码实现圆的绘制（可以适当对框架坐标系进行修改）       //
//          (7)适当修改代码实现具有宽度的图形（线刷子或方刷子）           //
////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include "stdio.h"

int m_PointNumber = 0; //动画时绘制点的数目
int m_DrawMode = 1;    //绘制模式   1    DDA算法画直线
//           2    中点Bresenham算法画直线
//           3    改进Bresenham算法画直线
//           4    八分法绘制圆
//           5    四分法绘制椭圆

//绘制坐标线
void DrawCordinateLine(void)
{
	int i = 0 ;
	//坐标线为黑色
	glColor3f(0.0f, 0.0f ,0.0f);
	glBegin(GL_LINES);
        for (i=10;i<=250;i=i+10)
		{
			glVertex2f((float)(i), 0.0f);
			glVertex2f((float)(i), 250.0f);
			glVertex2f(0.0f, (float)(i));
			glVertex2f(250.0f, (float)(i));
		}
	glEnd();
}

//绘制一个点，这里用一个正方形表示一个点。
void putpixel(GLsizei x, GLsizei y)
{
	glRectf(10*x,10*y,10*x+10,10*y+10);
}

///////////////////////////////////////////////////////////////////
//DDA画线算法                                                    //
//参数说明：x0,y0  起点坐标                                      //  
//          x1,y1  终点坐标                                      // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画  //
/////////////////////////////////////////////////////////////////// 
void DDACreateLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	//设置颜色
	glColor3f(1.0f,0.0f,0.0f);
	
	//对画线动画进行控制
	if(num == 1)
		printf("DDA画线算法：各点坐标\n");
	else if(num==0)
		return;

	//画线算法的实现
	GLsizei dx,dy,epsl,k;
	GLfloat x,y,xIncre,yIncre;

	dx = x1-x0;
	dy = y1-y0;
	x = x0;
	y = y0;

	if(abs(dx) > abs(dy)) epsl = abs(dx);
	else epsl = abs(dy);
	xIncre = (float)dx / epsl ;
	yIncre = (float)dy / epsl ;

	for(k = 0; k<=epsl; k++){
		putpixel((int)(x+0.5), (int)(y+0.5));
		if (k>=num-1) {
			printf("x=%f,y=%f,取整后 x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
			break;
		}
		x += xIncre;
		y += yIncre;

		if(x >= 25 || y >= 25) break;
	}
	
}

///////////////////////////////////////////////////////////////////
//中点Bresenham算法画直线(0<=k<=1)                               //
//参数说明：x0,y0  起点坐标                                      //  
//          x1,y1  终点坐标                                      // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画  //
/////////////////////////////////////////////////////////////////// 
void BresenhamLine(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("中点Bresenham算法画直线：各点坐标及判别式的值\n");
	else if(num==0)
		return;
  
  //画线算法的实现
  GLsizei dx,dy,d,UpInce,DownInce,x,y,k;
  if(x0>x1){
    x=x1;x1=x0;x0=x;
    y=y1;y1=y0;y0=y;
  }
  x=x0;y=y0;
  dx=x1-x0;dy=y1-y0;
  d=dx-2*dy;
  UpInce=2*dx-2*dy;  DownInce=-2*dy;
  for(k=0;x<=x1;k++){
   putpixel(x,y);
    if (k>=num-1) {
      printf("x=%d,y=%d,取整后 x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
      break;
    }
  x++;
    if(d<0){
    y++;
      d+=UpInce;
    }
    else  d+=DownInce;
  }
  
}

///////////////////////////////////////////////////////////////////
//改进的Bresenham算法画直线(0<=k<=1)                             //
//参数说明：x0,y0  起点坐标                                      //  
//          x1,y1  终点坐标                                      // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画  //
/////////////////////////////////////////////////////////////////// 
void Bresenham2Line(GLsizei x0, GLsizei y0, GLsizei x1, GLsizei y1, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("改进的Bresenham算法画直线：各点坐标及判别式的值\n");
	else if(num==0)
		return;
  //画线算法的实现
  GLsizei x,y,dx,dy,e,k;
  dx=x1-x0;
  dy=y1-y0;
  e=-dx;x=x0;y=y0;
  for(k=0;x<=x1;k++){
    putpixel(x,y);  
    if(k>=num-1){
    
      printf("x=%d,y=%d,取整后 x=%d,y=%d\n", x, y, (int)(x+0.5),(int)(y+0.5));
      break;
    }
    x++;
    e=e+2*dy;
    if(e>0){
    y++;
    e=e-2*dx;
    }
  }
}

///////////////////////////////////////////////////////////////////
//Bresenham算法画圆                                              //
//参数说明：x,y    圆心坐标                                      //  
//          R      圆半径                                        // 
//          num    扫描转换时从起点开始输出的点的数目，用于动画  //
/////////////////////////////////////////////////////////////////// 
void BresenhamCircle(GLsizei x, GLsizei y, GLsizei R, GLsizei num)
{
	glColor3f(1.0f,0.0f,0.0f);

	if(num == 1)
		printf("Bresenham算法画圆：各点坐标及判别式的值\n");
  else if(num==0)
    return;
  

  //画圆算法的实现
   GLsizei x1,y1,d,k;
  x1=0;y1=R;d=1-R;
  for(k=0;x1<=y1;k++){
    putpixel(x1,y1);
    if(k>=num-1){
      printf("x=%d,y=%d,取整后x=%d,y=%d\n",x,y,(int)(x+0.5),(int)(y+0.5));
      break;
    }
   if(d<0) d+=2*x1+3;
    else{
      d+=2*(x1-y1)+5;
      y1--;
    }
    x1++;
  }
	

}

//初始化窗口
void Initial(void)
{
    // 设置窗口颜色为蓝色
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{

	if(h == 0)		h = 1;

	// 设置视区尺寸
   	glViewport(0, 0, w, h);
	
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 建立修剪空间的范围
   	if (w <= h) 
		glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

}

// 在窗口中绘制图形
void ReDraw(void)
{
	//用当前背景色填充窗口
	glClear(GL_COLOR_BUFFER_BIT);

	//画出坐标线
	DrawCordinateLine();
	
	switch(m_DrawMode)
	{
	case 1:
		DDACreateLine(0,0,20,15,m_PointNumber);
		break;
	case 2:
		BresenhamLine(0,0,20,15,m_PointNumber);
		break;
	case 3:
		Bresenham2Line(1,1,8,6,m_PointNumber);
		break;
	case 4:
		BresenhamCircle(0,0,20,m_PointNumber);
		break;
	default:
		break;
	}

    glFlush();
}

//设置时间回调函数
void TimerFunc(int value)
{
	if(m_PointNumber == 0)
		value = 1;

	m_PointNumber = value;

	glutPostRedisplay();
	glutTimerFunc(500, TimerFunc, value+1);
}

//设置键盘回调函数
void Keyboard(unsigned char key, int x, int y)   
{
    if (key == '1')     m_DrawMode = 1;
	if (key == '2')     m_DrawMode = 2;
	if (key == '3')     m_DrawMode = 3;
	if (key == '4')     m_DrawMode = 4;

	m_PointNumber = 0;
	glutPostRedisplay();
}

//void main(void)
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);

	glutCreateWindow("基本图元绘制程序");	glutDisplayFunc(ReDraw); 
  glutReshapeFunc(ChangeSize); 
	glutKeyboardFunc(Keyboard);//键盘响应回调函数
	glutTimerFunc(500, TimerFunc, 1);

   	
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环

	return 0;
}
