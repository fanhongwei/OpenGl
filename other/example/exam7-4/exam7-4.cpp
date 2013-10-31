#include <GL/glut.h>

void Redraw(void)
{
    static GLfloat red_light[4]  = { 1.0, 0.0, 0.0, 1.0 };
    static GLfloat red_pos[4]    = { 1.0, 1.0, 1.0, 0.0 };
    static GLfloat blue_light[4] = { 0.0, 0.0, 1.0, 1.0 };
    static GLfloat blue_pos[4]   = { -1.0, -1.0, -1.0, 0.0 };
    static GLfloat fogcolor[4]   = { 0.0, 0.0, 0.0, 0.0 };

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* 设置雾的参数 */
    glFogfv(GL_FOG_COLOR, fogcolor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 10.0);
    glFogf(GL_FOG_END, 20.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_FOG);

    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT0, GL_POSITION, red_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_pos);

    glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glTranslatef(2.5, 0.0, -18.0);
    glRotatef(-45.0, 0.0, 1.0, 0.0);

    glColor3f(1.0, 1.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 0.0, -10.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);

    glColor3f(0.0, 1.0, 1.0);
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
    glutCreateWindow("具有深度感的茶壶");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
    glutMainLoop();
    return (0);
}


