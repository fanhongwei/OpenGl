#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>

#define GL_PI 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

//将任意法线矢量变为单位法线矢量
void ReduceToUnit(float vector[3])
{
	float length;
	
	// 计算向量的长度		
	length = (float)sqrt((vector[0]*vector[0]) + 
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	if(length == 0.0f)
		length = 1.0f;

	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


//利用平面上三个点计算法线矢量
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	ReduceToUnit(out);//变为单位法线矢量
}

// 初始化 
void Initial()
{
	// 光源参数
	GLfloat  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };

	glEnable(GL_DEPTH_TEST);	
	glFrontFace(GL_CCW);		
	glEnable(GL_CULL_FACE);		

	glEnable(GL_LIGHTING);

	// 设置光源light0
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	
	//指定光源参数的镜面成分
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);

	// 启用颜色跟踪
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//增加材料的镜面属性
//	GLfloat  specref[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
//	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
//	glMateriali(GL_FRONT,GL_SHININESS,128);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 80.0f;
	GLfloat	 lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };

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
    
	//设置光源位置
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
}

void ReDraw(void)
{
	float normal[3];	// 保存方向矢量

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glColor3ub(128, 128, 128);
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 60.0f);
		glVertex3f(-15.0f, 0.0f, 30.0f);
		glVertex3f(15.0f,0.0f,30.0f);
	
	{
		float v[3][3] =	{{ 15.0f, 0.0f, 30.0f},
						{ 0.0f, 15.0f, 30.0f},
						{ 0.0f, 0.0f,	60.0f}};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}	

	{
		float v[3][3] = {{ 0.0f, 0.0f, 60.0f },
						 { 0.0f, 15.0f, 30.0f },
						 { -15.0f, 0.0f, 30.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ -15.0f,0.0f,30.0f },
					 { 0.0f, 15.0f, 30.0f },
					 { 0.0f, 0.0f, -56.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}
	
	{
		float v[3][3] = {{ 0.0f, 0.0f, -56.0f },
						 { 0.0f, 15.0f, 30.0f },
						 { 15.0f,0.0f,30.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);	
	}
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(15.0f,0.0f,30.0f);
		glVertex3f(-15.0f, 0.0f, 30.0f);
		glVertex3f(0.0f, 0.0f, -56.0f);

	{
		float v[3][3] = {{ 0.0f,2.0f,27.0f },
					 { -60.0f, 2.0f, -8.0f },
					 { 60.0f, 2.0f, -8.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}
	
	{
		float v[3][3] =    {{ 60.0f, 2.0f, -8.0f},
						{0.0f, 7.0f, -8.0f},
						{0.0f,2.0f,27.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{60.0f, 2.0f, -8.0f},
						{-60.0f, 2.0f, -8.0f},
						{0.0f,7.0f,-8.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{0.0f,2.0f,27.0f},
						 {0.0f, 7.0f, -8.0f},
						 {-60.0f, 2.0f, -8.0f}};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-30.0f, -0.50f, -57.0f);
		glVertex3f(30.0f, -0.50f, -57.0f);
		glVertex3f(0.0f,-0.50f,-40.0f);

	{
		float v[3][3] = {{ 0.0f,-0.5f,-40.0f },
						{30.0f, -0.5f, -57.0f},
						{0.0f, 4.0f, -57.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ 0.0f, 4.0f, -57.0f },
						{ -30.0f, -0.5f, -57.0f },
						{ 0.0f,-0.5f,-40.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ 30.0f,-0.5f,-57.0f },
						{ -30.0f, -0.5f, -57.0f },
						{ 0.0f, 4.0f, -57.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ 0.0f,0.5f,-40.0f },
						{ 3.0f, 0.5f, -57.0f },
						{ 0.0f, 25.0f, -65.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ 0.0f, 25.0f, -65.0f },
						{ -3.0f, 0.5f, -57.0f},
						{ 0.0f,0.5f,-40.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	}

	{
		float v[3][3] = {{ 3.0f,0.5f,-57.0f },
						{ -3.0f, 0.5f, -57.0f },
						{ 0.0f, 25.0f, -65.0f }};
		calcNormal(v,normal);
		glNormal3fv(normal);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
	glEnd();
	}

	glPopMatrix();
	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;
	if(key > 356.0f)   	xRot = 0.0f;
	if(key < -1.0f)		xRot = 355.0f;
	if(key > 356.0f)	yRot = 0.0f;
	if(key < -1.0f)		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Lighted Jet");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(ReDraw);
	Initial();
	glutMainLoop();

	return 0;
}
