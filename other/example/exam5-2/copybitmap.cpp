#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

void quads(void)
{
	glBegin (GL_QUADS);
		glColor3f (1.0, 1.0, 0.0);
		glVertex2f (10.0, 10.0);
		glColor3f(0.0,0.3,1.0);
		glVertex2f (30.0, 10.0);
		glColor3f(1.0,0.0,0.0);
		glVertex2f (30.0, 30.0);
		glColor3f(0.0,1.0,0.0);
		glVertex2f (10.0, 30.0);
	glEnd ();
}

//初始化窗口
void Initial(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   	if (w <= h) 
		gluOrtho2D (0.0f, 150.0f, 0.0f, 150.0f*h/w);
    else 
		gluOrtho2D (0.0f, 150.0f*w/h, 0.0f, 150.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 在窗口中绘制图形
void ReDraw(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	/* 绘制原始图像 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
    glTranslatef(10.0f, 100.0f,0.0f);
	quads();
	glPopMatrix();

	/* 拷贝图像 */
	glPushMatrix();
	for(i=0;i<5;i++)
	{
		glRasterPos2i( 20+i*30,10+i*20);
//		glPixelZoom(2.0,2.0);
		glCopyPixels(50,300,50,50,GL_COLOR);
	}
	glPopMatrix();
	// 刷新OpenGL命令队列
    glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowSize(500,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("象素处理");
	glutDisplayFunc(ReDraw); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
   	
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
	return 0;
}
