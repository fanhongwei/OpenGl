#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
	//设置光源LIGHT0的参数
	GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat light_ambient[]={0.0f,0.5f,0.5f,1.0f};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);

	//使光源有效
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//开启深度测试
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f,1.0f);
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 80.0f;
	if(h == 0)		h = 1;

    glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(40.0f, (GLfloat) w/(GLfloat) h, 1.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	GLfloat position[] = { 0.0f, 0.0f, 1.5f, 1.0f };
	
	glPushMatrix ();
	glTranslatef (0.0f, 0.0f, -5.0f);
	glPushMatrix ();
	glRotated (yRot, 0.0f, 1.0f, 0.0f);
	glRotated (xRot, 1.0f, 0.0f, 0.0f);
	
	//设置光源的位置
	glLightfv (GL_LIGHT0, GL_POSITION, position);
	
	glTranslated (0.0f, 0.0f, 1.5f);
	
	//绘制一个黄色的光球
	glDisable (GL_LIGHTING);
	glColor3f (1.0f, 1.0f, 0.0f);
	glutSolidSphere (0.1f, 50.0f, 50.0f);
	glEnable (GL_LIGHTING);
	
	glPopMatrix ();
	//设置材质属性
	GLfloat mat_diffuse[]={0.0,0.5,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);

	glutSolidTorus (0.275, 0.85, 50, 50);
	glPopMatrix ();
	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)		xRot-= 5.0f;
	if(key == GLUT_KEY_DOWN)	xRot += 5.0f;
	if(key == GLUT_KEY_LEFT)	yRot -= 5.0f;
	if(key == GLUT_KEY_RIGHT)	yRot += 5.0f;

	if(key > 356.0f)	xRot = 0.0f;
	if(key < -1.0f)		xRot = 355.0f;
	if(key > 356.0f)	yRot = 0.0f;
	if(key < -1.0f) 	yRot = 355.0f;

	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("移动的光源");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}
