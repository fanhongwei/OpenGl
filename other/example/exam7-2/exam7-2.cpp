#include <GL/glut.h>

//初始化窗口
void Initial(void)
{
    static GLfloat red_light[4]  = { 1.0, 0.0, 0.0, 1.0 };
    static GLfloat red_pos[4]    = { 1.0, 1.0, 1.0, 0.0 };
    static GLfloat blue_light[4] = { 0.0, 0.0, 1.0, 1.0 };
    static GLfloat blue_pos[4]   = { -1.0, -1.0, -1.0, 0.0 };
	
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT0, GL_POSITION, red_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_pos);

    glEnable(GL_COLOR_MATERIAL);
}

void Redraw(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//GL_SRC_ALPHA表示缩放因子为源颜色与源alpha相乘
	//GL_ONE_MINUS_SRC_ALPHA表示缩放因子为目的色与（1－源alpha相乘）
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(0.0, 0.0, -15.0);
    glRotatef(-45.0, 0.0, 1.0, 0.0);

    glDisable(GL_BLEND);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);

    glEnable(GL_BLEND);
    glColor4f(1.0, 1.0, 1.0, 0.25);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glFlush();
}

void Resize(int width, int height) 
{

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(22.5, (float)width / (float)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int  argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(792, 573);
    glutCreateWindow("透明茶壶");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
	Initial();
    glutMainLoop();
    return (0);
}





