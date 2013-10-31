#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// 旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//初始化窗口
void Initial(void)
{
    // 设置窗口背景颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	if(h == 0)	h = 1;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// 在窗口中绘制图形
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 旋转图形
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//点的参数
	glPointSize(5);

	//线的参数
//	glLineWidth(5);
//	glEnable(GL_LINE_STIPPLE);
//	glLineStipple(1,0x00FF);
	
	//面的参数
//	glPolygonMode(GL_BACK,GL_LINE);
//	glShadeModel(GL_FLAT);

// 绘制图形
	glBegin(GL_POINTS);//绘制三个点
//	glBegin(GL_LINE_LOOP);//利用三个点绘制三角形
//	glBegin(GL_TRIANGLES);//绘制三角形
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 50, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50, -50, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(50, -50, 0);
	glEnd();

	glPopMatrix();

	// 刷新命令缓冲区
	glutSwapBuffers();
}


void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;

	if(xRot > 356.0f)	xRot = 0.0f;
	if(xRot < -1.0f)	xRot = 355.0f;
	if(yRot > 356.0f)	yRot = 0.0f;
	if(yRot < -1.0f)	yRot = 355.0f;

	// 刷新窗口
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("例3");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
