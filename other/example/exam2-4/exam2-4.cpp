#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
//#include<gl/glu.h>

// 在窗口中绘制图形
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //用当前背景色填充窗口
   	glColor3f(0.0f, 0.0f, 0.0f); //设置当前的绘图绘图RGB颜色

//绘制不同大小的点
    GLfloat sizes[2];  //保存绘制点的尺寸范围
	GLfloat step;      //保存绘制点尺寸的步长
	GLfloat curSize;   //当前绘制的点的大小
	glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);

	curSize=sizes[0];
	
	for (int i=0;i<25;i++)
	{
		glPointSize(curSize);
        glBegin(GL_POINTS);
			glVertex3f(25.0+i*8,200.0,0.0);
		glEnd();
        curSize +=step*2;
	}

//绘制一条宽度为5的直线
	glLineWidth(5);
	glBegin(GL_LINES);
		glVertex3f(25.0,160.0,0.0);
		glVertex3f(225.0,160.0,0.0);
	glEnd();

//绘制一条虚线
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1,0x00FF);
	glBegin(GL_LINES);
		glVertex3f(25.0,120.0,0.0);
		glVertex3f(225.0,120.0,0.0);
	glEnd();

//绘制一条宽度为3的点划线
	glLineWidth(3);
	glLineStipple(1,0xFF0C);
	glBegin(GL_LINES);
		glVertex3f(25.0,80.0,0.0);
		glVertex3f(225.0,80.0,0.0);
	glEnd();

//增加重复因子绘制的点划线
	glLineStipple(4,0xFF0C);
	glBegin(GL_LINES);
		glVertex3f(25.0,40.0,0.0);
		glVertex3f(225.0,40.0,0.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glFlush();//刷新OpenGL命令队列
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
		
	glViewport(0, 0, w, h); //设置视区尺寸

	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 建立修剪空间的范围
   		if (w <= h) 
			glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
    	else 
			glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetupRC(void)
{
   	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 设置窗口的背景色
}

void main(void)
{
	//初始化GLUT库OpenGL窗口的显示模式
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("点与线"); 
	glutDisplayFunc(RenderScene); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数

	SetupRC();
	glutMainLoop(); //启动主GLUT事件处理循环
}

