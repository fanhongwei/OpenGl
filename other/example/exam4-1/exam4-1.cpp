#include <GL/glut.h>

GLenum DepthFunc = GL_LESS; /* 深度对比函数 */

//初始化窗口
void Initial(void)
{
    static float red_light[4]  = {  1.0,  0.0,  0.0,  1.0 };
    static float red_pos[4]    = {  1.0,  1.0,  1.0,  0.0 };
    static float blue_light[4] = {  0.0,  0.0,  1.0,  1.0 };
    static float blue_pos[4]   = { -1.0, -1.0, -1.0,  0.0 };
   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, red_light);
    glLightfv(GL_LIGHT0, GL_POSITION, red_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_light);
    glLightfv(GL_LIGHT1, GL_POSITION, blue_pos);
}

void Resize(int width, int height) 
{
    /* 重置视区*/
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(22.5, (float)width / (float)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)   
{
    if (key == 'd' || key == 'D')
    {
		/* 切换深度对比函数 */
        if (DepthFunc == GL_LESS)
            DepthFunc = GL_GREATER;
        else
            DepthFunc = GL_LESS;
        glutPostRedisplay();
    }
}

void Redraw(void)
{
    glShadeModel(GL_SMOOTH);
	
	//启用深度测试并设置深度测试函数
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(DepthFunc); 
    //不同的深度对比函数使用不同的初始值
    if (DepthFunc == GL_LESS)
        glClearDepth(1.0);
    else
        glClearDepth(0.0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(-1.0, 0.0, -20.0);
    glutSolidSphere(1.0, 36, 18);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.0, 0.0, -20.0);
    glRotatef(15.0, 0.0, 1.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();

	glFlush();
}

int main(int  argc, char *argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    //建议窗口的初始尺寸
	glutInitWindowSize(792, 573);
    glutCreateWindow("深度测试");
    glutReshapeFunc(Resize);
    glutDisplayFunc(Redraw);
    glutKeyboardFunc(Keyboard);//键盘响应回调函数
	Initial();
    glutMainLoop();
    return (0);
}
