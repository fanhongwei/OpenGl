#include <windows.h>
#include <gl/gl.h>
//#include <gl/glu.h>
#include <gl/glut.h>
//#include <math.h>

// 旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bDepth = FALSE;//深度测试开关
BOOL bCull = FALSE;//剔除开关

//初始化窗口
void SetupRC(void)
{
    // 设置窗口背景颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glShadeModel(GL_FLAT);//指定多边形的阴影模式为平面阴暗模式
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
	//清除颜色及深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	//是否开启设度测试
	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	//是否打开剔除
	if(bCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// 旋转图形
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glFrontFace(GL_CW);//指定顺时针绕法的多边形为多边形正面

	//绘制三棱锥的三个棱面，他们的颜色分别为红、绿、蓝
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 0.0, 80.0);
		glVertex3f(0.0, 50.0, 0.0);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(50.0, -50.0, 0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(-50.0, -50.0, 0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0, 50.0, 0.0);
	glEnd();

	//绘制三棱锥的底面，其颜色为黄色
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 50.0, 0.0);
		glVertex3f(50.0, -50.0, 0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(-50.0, -50.0, 0.0);		
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
			bDepth = !bDepth;
			break;
		case 2:
			bCull = !bCull;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutCreateWindow("三棱锥");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// 创建右键菜单
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("深度测试",1);
	glutAddMenuEntry("剔除背面",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();

	return 0;
}
