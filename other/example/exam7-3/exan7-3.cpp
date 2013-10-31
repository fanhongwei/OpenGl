#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

int twin,qwin;

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
	// 设置视区尺寸
   	glViewport(0, 0, w, h);
	
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 3.0f, 5.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(15.0,1.0,1.0,0.0);
}

// 在窗口中绘制图形
void ReDrawt(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(8.0f);
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f (0.0, 0.6, 1.0, 1.0);
	glutWireOctahedron();
    glFlush();
}

// 在第二个窗口中绘制图形
void ReDraww(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//使用混合、反走样
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glLineWidth(8.0f);
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f (0.0, 0.6, 1.0, 1.0);
	glutWireOctahedron();
    glFlush();
}

void main(void)
   {
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	twin = glutCreateWindow("原始图形");
	glutDisplayFunc(ReDrawt); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
   	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(500, 500);
	qwin = glutCreateWindow("反走样");
	glutDisplayFunc(ReDraww); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数

	glutMainLoop(); //启动主GLUT事件处理循环
}
