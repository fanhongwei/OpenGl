#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

//初始化窗口
void SetupRC(void)
{
	GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	GLfloat light0_diffuse[]= { 0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	GLfloat light1_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light1_diffuse[]= { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light1_specular[] = { 1.0f, 0.6f, 0.6f, 1.0f };
	GLfloat light1_position[] = { -3.0f, -3.0f, 3.0f, 1.0f };
	GLfloat spot_direction[]={ 1.0f, 1.0f, -1.0f};

	//定义材料属性
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS,mat_shininess);

	//light0为一个漫反射点光源
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,light0_position);

	//light1为一个聚光光源
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR,light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION,light1_position);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,spot_direction);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//蓝色光
	glEnable(GL_LIGHT1);//红色光
	glEnable(GL_DEPTH_TEST);

	// 设置窗口颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	// 设置视区尺寸
   	glViewport(0, 0, w, h);
	
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// 建立修剪空间的范围
   	if (w <= h) 
		glOrtho (-5.5f, 5.5f, -5.5f*h/w, 5.5f*h/w, -10.0f, 10.0f);
    else 
		glOrtho (-5.5f*w/h, 5.5f*w/h, -5.5f, 5.5f, -10.0f, 10.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 在窗口中绘制图形
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated (-3.0f, -3.0f, 3.0f);
	glPopMatrix ();
	glutSolidSphere(2.0f, 50, 50);

    glFlush();
}

void main(void)
{
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("多光源球"); 
	glutDisplayFunc(RenderScene); 
    glutReshapeFunc(ChangeSize); 
   	
	SetupRC();
	glutMainLoop(); 
}
