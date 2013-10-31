#include <windows.h>
#include <gl/glut.h>

// 正方体的位置和大小
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// 变化的步长
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// 窗口大小
GLfloat windowWidth;
GLfloat windowHeight;

//初始化窗口
void Initial(void)
{
    // 设置窗口颜色为蓝色
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	glViewport(0, 0, w, h);// 设置视区尺寸
	
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 建立修剪空间的范围
	if (w <= h) 
	{
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
	}
    else 
	{
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 在窗口中绘制图形
void ReDraw(void)
{
	//用当前背景色填充窗口
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 设置当前的绘图绘图RGB颜色
	glColor3f(1.0f, 0.0f, 0.0f);
	
	// 使用当前颜色绘制一个填充的矩形
	glRectf(x1, y1, x1+rsize, y1+rsize);
	
	// 刷新OpenGL命令队列
    glutSwapBuffers();
}

// 设置时间回调函数
void TimerFunction(int value)
{
	if(x1 > windowWidth-rsize || x1 < 0)	xstep = -xstep;
	if(y1 > windowHeight-rsize || y1 < 0)	ystep = -ystep;

	if(x1 > windowWidth-rsize)		x1 = windowWidth-rsize-1;
	if(y1 > windowHeight-rsize)		y1 = windowHeight-rsize-1;

	x1 += xstep;
	y1 += ystep;

	// 用新坐标重画图形
    glutPostRedisplay();
	glutTimerFunc(33,TimerFunction, 1);
}

// Main program entry point
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("移动的矩形");
	glutDisplayFunc(ReDraw);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);

	Initial();
	glutMainLoop();

	return 0;
}