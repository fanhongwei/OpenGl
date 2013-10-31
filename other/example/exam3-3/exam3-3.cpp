#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

//初始化窗口
void SetupRC(void)
{
    // 设置窗口背景颜色为白色
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
}

//绘制三角形
void DrawTriangle(void)
{
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(40.0f, 0.0f);
		glVertex2f(20.0f, 40.0f);
	glEnd();
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-100.0f, 100.0f, -100.0f*h/w, 100.0f*h/w, -100.0f, 100.0f);
    else 
		glOrtho (-100.0f*w/h, 100.0f*w/h, -100.0f, 100.0f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//绘制黑色的坐标轴
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex2f(-100.0f, 0.0f);
		glVertex2f(100.0f, 0.0f);
		glVertex2f(0.0f, -100.0f);
		glVertex2f(0.0f, 100.0f);
	glEnd();

	//画出初始的红色三角形
	glColor3f(1.0f, 0.0f, 0.0f);
	DrawTriangle();

	//画出逆时针旋转200度角的绿色三角形
	glRotatef(200.0f,0.0f,0.0f,1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	DrawTriangle();

	//画出沿x轴负向平移40的黄色三角形
	glLoadIdentity();
	glTranslatef(-60.0f,0.0f,0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawTriangle();

	//画出缩放因子为1.0,2.0,1.0的蓝色三角形
	glTranslatef(100.0f,10.0f,0.0f);
	glScalef(1.0f,2.0f,1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	DrawTriangle();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("变换实例");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	
	SetupRC();
	glutMainLoop();

	return 0;
}
