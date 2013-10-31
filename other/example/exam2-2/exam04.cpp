#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#define GL_PI 3.1415f

// 设置旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// 指定的参数
BOOL bDepth = FALSE;

// 初始化
void Initial()
{
	// 背景色为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	// 设置当前颜色为绿色
	glColor3f(0.0f, 1.0f, 0.0f);
	// 颜色阴影模式为平面模式
	glShadeModel(GL_FLAT);
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	if(h == 0)		h = 1;
	// 设置视区尺寸
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 设置修剪空间
    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ReDraw(void)
{
	GLfloat x,y,angle;   
	int iPivot = 1;	// 设置颜色变换标志

	// 清除窗口以及深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(bDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
		
	// 保存当前矩阵并进行旋转
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	
	// 绘制锥体的三角扇形
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 75.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		// 将颜色在红色与绿色之间切换
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		// 指定下一个点
		glVertex2f(x, y);
	}
	glEnd();
	
	// 绘制锥底的扇形
	glFrontFace(GL_CCW);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for(angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI/8.0f))
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		if((iPivot %2) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		iPivot++;
		glVertex2f(x, y);
	}
	glEnd();
	// 恢复矩阵
	glPopMatrix();
	// 执行缓冲区交换，并刷新流水线
	glutSwapBuffers();
}

//响应方向键，分别绕x轴和y轴逆时针和顺时针旋转
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)		xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)		yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)		yRot += 5.0f;
	if(xRot > 356.0f)	xRot = 0.0f;
	if(xRot < -1.0f)	xRot = 355.0f;
	if(yRot > 356.0f)	yRot = 0.0f;
	if(yRot < -1.0f)	yRot = 355.0f;

	glutPostRedisplay();
}

// 设置右键菜单
void ProcessMenu(int value)
{
	switch(value)
		{
		case 1:
			bDepth = !bDepth;
			break;
		default:
			break;
		}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Triangle Culling Example");
	//创建右键菜单
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("启用深度测试",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();
	return 0;
}
