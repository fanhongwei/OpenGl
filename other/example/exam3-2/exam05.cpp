#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// 启用深度测试
	glFrontFace(GL_CCW);		// 指定逆时针绕法表示多边形正面

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );	//背景为白色
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;

	// 设置视区尺寸
    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置修剪空间
	GLfloat fAspect;
	fAspect = (float)w/(float)h;
	gluPerspective(45.0, fAspect, 1.0, 500.0);
/*
	    if (w <= h) 
			glOrtho (-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0f, nRange*2.0f);
		else 
			glOrtho (-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0f, nRange*2.0f);
*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void RenderScene(void)
{
	// 绕原子核旋转的角度
	static float fElect1 = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 重置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//将图形沿z轴负向移动
	glTranslatef(0.0f, 0.0f, -250.0f);	

	// 绘制红色的原子核
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(10.0f, 15, 15);

	// 当前绘制颜色变为黄色
	glColor3f(0.0f, 0.0f, 0.0f);

	//绘制第一个电子
	//保存当前的模型视图矩阵
	glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);//绕y轴旋转一定的角度
	glTranslatef(90.0f, 0.0f, 0.0f);//平移一段距离
	glutSolidSphere(6.0f, 15, 15);//画出电子

	// 恢复矩阵
	glPopMatrix();

	// 第二个电子
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// 第三个电子
	glPushMatrix();
	glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	// 增加旋转步长
	fElect1 += 10.0f;
	if(fElect1 > 360.0f)	fElect1 = 10.0f;

	glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("原子核示例");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
    glutTimerFunc(500, TimerFunc, 1);

	SetupRC();
	glutMainLoop();

	return 0;
}
