#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

GLint nNumPoints = 3;
GLfloat ctrlPoints[3][3][3]= {{{  -4.0f, 0.0f, 4.0f},	
						      { -2.0f, 4.0f, 4.0f},	
							  {  4.0f, 0.0f, 4.0f }},
							 
							  {{  -4.0f, 0.0f, 0.0f},	
						      { -2.0f, 4.0f, 0.0f},	
							  {  4.0f, 0.0f, 0.0f }},
							  
							  {{  -4.0f, 0.0f, -4.0f},	
						      { -2.0f, 4.0f, -4.0f},	
							  {  4.0f, 0.0f, -4.0f }}};


void DrawPoints(void)
{
	int i,j;	
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		for(i = 0; i < nNumPoints; i++)
			for(j = 0; j < 3; j++)
				glVertex3fv(ctrlPoints[i][j]);
	glEnd();
}

void Initial()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	
/*	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat	 lightPos[] = { 20.0f, 0.0f, 0.0f, 0.0f };
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_AUTO_NORMAL);
*/
	glEnable(GL_DEPTH_TEST);	
	glColor3f(0.0f, 0.0f, 1.0f);	
}

void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(60.0f, 1.0f, 0.0f, 0.0f);

	glMap2f(GL_MAP2_VERTEX_3,	// 生成的数据类型
	0.0f,						// 参数u最小值
	10.0f,						// 参数u最大值
	3,							// 控制点数据顶点之间的数目
	3,							// Dimension in u direction (order)
	0.0f,						// 参数v最小值
	10.0f,						// 参数v最大值
	9,							// 控制点数据顶点之间的数目
	3,							// Dimension in v direction (order)
	&ctrlPoints[0][0][0]);		// 保存数据的数组

	glEnable(GL_MAP2_VERTEX_3);

	glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
	glEvalMesh2(GL_LINE,0,10,0,10);
//	glEvalMesh2(GL_FILL,0,10,0,10);

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
	glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Bezier曲面");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
