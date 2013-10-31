#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

/* 初始化 alpha 融合的参数 */
void Initial(void)
{
	glEnable (GL_BLEND);
	//GL_SRC_ALPHA表示缩放因子为源颜色与源alpha相乘
	//GL_ONE_MINUS_SRC_ALPHA表示缩放因子为目的色与（1－源alpha相乘）
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel (GL_FLAT);
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	if (w <= h) 
		gluOrtho2D (0.0f, 1.0f, 0.0f, 1.0f*h/w);
    else 
		gluOrtho2D (0.0f, 1.0f*w/h, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

// 在窗口中绘制图形
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor4f (1.0, 0.0, 0.0, 0.7);
	glRectf (0.25, 0.4, 0.75, 0.9);
	glColor4f (0.0, 1.0, 0.0, 0.5);
	glRectf (0.1, 0.1, 0.6, 0.6);
	glColor4f (0.0, 0.0, 1.0, 0.3);
	glRectf (0.4, 0.1, 0.9, 0.6);
	
	// 刷新OpenGL命令队列
    glFlush();
}

void main(void)
   {
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("混色"); 
	glutDisplayFunc(ReDraw); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
   	
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
}
