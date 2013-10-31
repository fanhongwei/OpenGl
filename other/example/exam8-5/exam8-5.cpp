#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

// NURBS对象指针
GLUnurbsObj *pNurb = NULL;

GLint nNumPoints = 4; // 4 X 4

GLfloat ctrlPoints[4][4][3]= {{{  -6.0f, -6.0f, 0.0f},	// u = 0,	v = 0
						      {	  -6.0f, -2.0f, 0.0f},	//			v = 1
							  {   -6.0f,  2.0f, 0.0f},	//			v = 2	
							  {   -6.0f,  6.0f, 0.0f}}, //			v = 3
							 
							  {{  -2.0f, -6.0f, 0.0f},	// u = 1	v = 0
						      {   -2.0f, -2.0f, 8.0f},	//			v = 1
							  {   -2.0f,  2.0f, 8.0f},	//			v = 2
							  {   -2.0f,  6.0f, 0.0f}},	//			v = 3
							  
							  {{   2.0f, -6.0f, 0.0f }, // u =2		v = 0
							  {    2.0f, -2.0f, 8.0f }, //			v = 1
							  {    2.0f,  2.0f, 8.0f },	//			v = 2
							  {    2.0f,  6.0f, 0.0f }},//			v = 3

							  {{   6.0f, -6.0f, 0.0f},	// u = 3	v = 0
							  {    6.0f, -2.0f, 0.0f},	//			v = 1
							  {    6.0f,  2.0f, 0.0f},	//			v = 2
							  {    6.0f,  6.0f, 0.0f}}};//			v = 3

GLfloat Knots[8] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f};

void DrawPoints(void)
{
	int i,j;
	glPointSize(5.0f);
	glColor3ub(255,0,0);
	glBegin(GL_POINTS);
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				glVertex3fv(ctrlPoints[i][j]);	
	glEnd();
}

void Initial()
{
	GLfloat  whiteLight[] = {0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat  shine[] = { 100.0f };

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glEnable(GL_AUTO_NORMAL);

	//定义NURBS参数
    pNurb = gluNewNurbsRenderer();
    gluNurbsProperty(pNurb, GLU_SAMPLING_TOLERANCE, 25.0f);
	gluNurbsProperty(pNurb, GLU_DISPLAY_MODE, (GLfloat)GLU_FILL);
}

void ReDraw(void)
{
	glColor3ub(0,0,220);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(330.0f, 1.0f,0.0f,0.0f);

    gluBeginSurface(pNurb);
		gluNurbsSurface(pNurb,	    // NURBS对象指针
			8,                      // 参数化u方向上的结点数目
			Knots,		        	// 参数化u方向上递增的结点值的数组	
			8,                      // 参数化v方向上的结点数目
			Knots,			        // 参数化v方向上递增的结点值的数组
			4 * 3,			       	// 参数化u方向上相邻控制点之间的偏移量
			3,					    // 参数化v方向上相邻控制点之间的偏移量
			&ctrlPoints[0][0][0],   // 包含曲面控制点的数组
			4,                      // 参数化u方向上的阶数
			4,					    // 参数化v方向上的阶数
			GL_MAP2_VERTEX_3);		// 曲面的类型
	gluEndSurface(pNurb);
	
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
	glutCreateWindow("NURBS曲面");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();
	return 0;
}
