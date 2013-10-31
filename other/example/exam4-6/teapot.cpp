#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

// 初始化 
void SetupRC()
{
	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { -5.0f, 5.0f, 5.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_AUTO_NORMAL);
//	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);

	glClearColor(0.0, 0.1, 0.1, 0.0);
}

void ChangeSize(int w, int h)
{
	if(h == 0)		h = 1;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) 
		glOrtho (-4.0f, 4.0f, -4.0f*h/w, 4.0f*h/w, -10.0f, 10.0f);
	else 
		glOrtho (-4.0f*w/h, 4.0f*w/h, -4.0f, 4.0f, -10.0f, 10.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	/* 第一个茶壶使用了GL_FRONT材质和单面光照。*/
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	GLdouble equ[4] = { -1.0f, 2.3f, 2.3f, 2.3f };
	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f );
	//glClipPlane定义裁减平面，equ中保存平面方程的系数
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);

	GLfloat tea_ambient[] = { 0.0f, 0.2f, 1.0f, 1.0f };
	GLfloat tea_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };
	GLfloat tea_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		
	glMaterialfv(GL_FRONT, GL_AMBIENT, tea_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, tea_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, tea_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

	//开启双面光照
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	/* 第二个茶壶正面和反面使用相同的材质。*/
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f );
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);

	GLfloat teafb_ambient[] = { 1.0f, 0.2f, 0.0f, 1.0f };
	GLfloat teafb_diffuse[] = { 0.9f, 0.5f, 0.8f, 1.0f };
	GLfloat teafb_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, teafb_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, teafb_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, teafb_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 55.0f);
	glutSolidTeapot(1.0);
	glPopMatrix();

	/* 第三个茶壶打开了双面光照。*/
	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f );
	glClipPlane(GL_CLIP_PLANE0, equ);
	glEnable(GL_CLIP_PLANE0);

	GLfloat teaf_ambient[] = { 0.6f, 0.4f, 0.4f, 1.0f };
	GLfloat teaf_diffuse[] = { 1.0f, 0.4f, 0.1f, 1.0f };
	GLfloat teaf_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		
	glMaterialfv(GL_FRONT, GL_AMBIENT, teaf_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, teaf_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, teaf_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
	
	GLfloat teab_ambient[] = { 0.4f, 0.1f, 1.0f, 1.0f };
	GLfloat teab_diffuse[] = { 0.2f, 0.8f, 0.1f, 1.0f };
	GLfloat teab_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		
	glMaterialfv(GL_BACK, GL_AMBIENT, teab_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, teab_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, teab_specular);
	glMaterialf(GL_BACK, GL_SHININESS, 8.0f);
	
	glutSolidTeapot(1.0);
	glPopMatrix();

	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(400,400);
	glutInitWindowPosition(200,200);
	glutCreateWindow("不同材质属性的茶壶");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}
