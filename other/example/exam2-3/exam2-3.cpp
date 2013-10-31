#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// Define a constant for the value of PI
#define GL_PI 3.1415f

// 旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// 标志
#define MODE_SOLID 0
#define MODE_LINE  1
#define MODE_POINT 2
int iMode = MODE_SOLID;
GLboolean bEdgeFlag = TRUE;

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

	glColor3f(0.0f, 0.0f, 0.0f);
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	if(h == 0)		h = 1;

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

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if(iMode == MODE_LINE)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	if(iMode == MODE_POINT)
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	if(iMode == MODE_SOLID)
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	//旋转景物
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glLineWidth(3);
	// 绘制图形
	glBegin(GL_TRIANGLES);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 0.0f);
		glEdgeFlag(TRUE);
		glVertex2f(20.0f, 0.0f);
		glVertex2f(0.0f, 40.0f);

		glVertex2f(-20.0f,0.0f);
		glVertex2f(-60.0f,-20.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f,-40.0f);
		glEdgeFlag(TRUE);

		glVertex2f(-20.0f,-40.0f);
		glVertex2f(0.0f, -80.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, -40.0f);		
		glEdgeFlag(TRUE);

		glVertex2f(20.0f, -40.0f);		
		glVertex2f(60.0f, -20.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, 0.0f);
		glEdgeFlag(TRUE);

		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 0.0f);
		glVertex2f(-20.0f,-40.0f);
		glVertex2f(20.0f, 0.0f);
		
		glVertex2f(-20.0f,-40.0f);
		glVertex2f(20.0f, -40.0f);
		glVertex2f(20.0f, 0.0f);
		glEdgeFlag(TRUE);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void ProcessMenu(int value)
{
	switch(value)
	{
		case 1:
			iMode = MODE_SOLID;
			break;
		case 2:
			iMode = MODE_LINE;
			break;
		case 3:
			iMode = MODE_POINT;
			break;
		case 4:
			bEdgeFlag = TRUE;
			break;
		case 5:
		default:
			bEdgeFlag = FALSE;
			break;
	}
	glutPostRedisplay();
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

	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	int nModeMenu;
	int nEdgeMenu;
	int nMainMenu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("星形");
	
	// 创建菜单
	nModeMenu = glutCreateMenu(ProcessMenu);//创建菜单并定义菜单回调函数
	//添加菜单项，1表示选择菜单条目时传递的参数值
	glutAddMenuEntry("多边形填充模式",1);
	glutAddMenuEntry("线框模型",2);
	glutAddMenuEntry("点",3);

	nEdgeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("开",4);
	glutAddMenuEntry("关",5);

	nMainMenu = glutCreateMenu(ProcessMenu);
	glutAddSubMenu("Mode", nModeMenu);
	glutAddSubMenu("Edges", nEdgeMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
