#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// 初始化
void Initial()
{
	//背景为白色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	
}

void Drawquad(void)
{
	glBegin(GL_QUADS);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(80.0f, 0.0f);
		glVertex2f(80.0f, 80.0f);
		glVertex2f(0.0f, 80.0f);
	glEnd();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 建立修剪空间的范围
   	if (w <= h) 
		glOrtho (0.0f, 300.0f, 0.0f, 300.0f*h/w, 1.0, -1.0);
    else 
		glOrtho (0.0f, 300.0f*w/h, 0.0f, 300.0f, 1.0, -1.0);
}

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//绘制黑色的坐标轴
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(150.0f, 300.0f);
		glVertex2f(150.0f, 0.0f);
		glVertex2f(0.0f, 150.0f);
		glVertex2f(300.0f, 150.0f);
	glEnd();

	//画出初始图形
	glTranslatef( 150.0, 150.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	Drawquad();

//	glPushMatrix();
	// 绘制出旋转后的图形
	glRotatef( 135.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	Drawquad();

//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

//	glPopMatrix();
	// 绘制出第二次旋转后的图形
	glRotatef( 300.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	Drawquad();

	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("图形变换");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
