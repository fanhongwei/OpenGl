#include <windows.h>
#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
//#include <math.h>

// 旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bWinding = TRUE;//确定多边形绕法的方向

//初始化窗口
void SetupRC(void)
{
    // 设置窗口背景颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
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

// 在窗口中绘制图形
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 旋转图形
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glPointSize(5);
	glLineWidth(5);
	
	//设置多边形绕法的方向是顺时针还是逆时针
	if (bWinding) 
		glFrontFace(GL_CW);
	else
		glFrontFace(GL_CCW);

	glBegin(GL_TRIANGLES);//绘制三角形
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0, 60, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-60, -60, 0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(60, -60, 0);
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

void ProcessMenu(int value)
{

	switch(value)
	{
		case 1:
			glPolygonMode(GL_FRONT,GL_FILL);;
			break;
		case 2:
			glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 3:
			glPolygonMode(GL_FRONT,GL_POINT);
			break;
		case 4:
			glPolygonMode(GL_FRONT,GL_FILL);
			break;
		case 5:
			glPolygonMode(GL_FRONT,GL_LINE);
			break;
		case 6:
			glPolygonMode(GL_FRONT,GL_POINT);
			break;
		case 7:
			glShadeModel(GL_FLAT);
			break;
		case 8:
			glShadeModel(GL_SMOOTH);
			break;
		case 9:
			bWinding = !bWinding;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	int nModeMenu;
	int nMainMenu;
	int nColorMenu;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("多边形演示");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// 创建菜单
	nModeMenu = glutCreateMenu(ProcessMenu);//创建菜单并定义菜单回调函数
	//添加菜单项，1表示选择菜单条目时传递的参数值
	glutAddMenuEntry("正面多边形填充模式",1);
	glutAddMenuEntry("正面线框模型",2);
	glutAddMenuEntry("正面点模式",3);
	glutAddMenuEntry("反面多边形填充模式",4);
	glutAddMenuEntry("反面线框模型",5);
	glutAddMenuEntry("反面点模式",6);

	nColorMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("平面明暗模式",7);
	glutAddMenuEntry("光滑明暗模式",8);

	nMainMenu = glutCreateMenu(ProcessMenu);
	glutAddSubMenu("多边形模式", nModeMenu);
	glutAddSubMenu("颜色模式", nColorMenu);
	glutAddMenuEntry("改变绕法",9);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();

	return 0;
}
