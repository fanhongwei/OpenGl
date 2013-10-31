#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

// 旋转参数
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

BOOL bColorMaterial = FALSE;//颜色跟踪模式

//初始化窗口
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f );
	glShadeModel(GL_FLAT);
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
	glEnable(GL_DEPTH_TEST);

	//设置光照
	glEnable(GL_LIGHTING);
	GLfloat ambient[]={0.8f, 0.8f, 0.8f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	//设置材质属性
	if(bColorMaterial)
	{
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	else
	{

		glDisable(GL_COLOR_MATERIAL);
		GLfloat material_ambiemt[]={0.75f, 0.75f, 0.75f, 1.0f};
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,material_ambiemt);
	}

	// 旋转图形
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glFrontFace(GL_CW);

	//绘制三棱锥
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
			bColorMaterial = FALSE;
			break;
		case 2:
			bColorMaterial = TRUE;
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
	glutCreateWindow("加光照的三棱锥");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	
	// 创建右键菜单
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("普通材质",1);
	glutAddMenuEntry("颜色跟踪材质",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	SetupRC();
	glutMainLoop();
	return 0;
}
