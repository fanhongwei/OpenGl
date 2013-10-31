#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// NURBS对象指针
GLUnurbsObj *pNurb = NULL;

// 曲线的控制点
GLint nNumPoints = 4; 

GLfloat ctrlPoints[4][3]  = {{  -6.0f, -6.0f, 0.0f},
							 {   2.0f, -2.0f, 8.0f},
							 {   2.0f,  6.0f, 0.0f},
							 {   6.0f, 6.0f,  0.0f}};
//定义结点
GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

void DrawPoints(void)
{
	int i;

	glPointSize(5.0f);
	glColor3ub(255,0,0);

	glBegin(GL_POINTS);
		for(i = 0; i < 4; i++)
			glVertex3fv(ctrlPoints[i]);	
	glEnd();
}

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

	glLineWidth(3.0f);

	//初始化NURBS对象
    pNurb = gluNewNurbsRenderer();
	//采样的最大长度为25
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
	//显示模式为GLU_FILL
	gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
}

void ReDraw(void)
{
	glColor3ub(0,0,220);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(330.0f, 1.0f,0.0f,0.0f);
	
	// 定义NURBS曲线
    gluBeginCurve(pNurb);
		gluNurbsCurve(pNurb,     // 定义NURBS对象
			8,                   // knot中的结点数目
			Knots,               // knots数组
			3,                   // 相邻两个曲线控制点之间的偏移量
			&ctrlPoints[0][0],   // 指向控制点数组的指针
			4,                   // 曲线的阶数
			GL_MAP1_VERTEX_3);   // 曲线的类型
	gluEndCurve(pNurb);
	
	DrawPoints();

	glPopMatrix();
	glutSwapBuffers();
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45.0f, (GLdouble)w/(GLdouble)h, 1.0, 40.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -20.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("NURBS曲线");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
