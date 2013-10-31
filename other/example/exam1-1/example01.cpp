//GLRect.c
#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

// 函数RenderScene用于在窗口中绘制需要的图形
void RenderScene(void)
{
	//用当前清除色清除颜色缓冲区，即设定窗口的背景色
	glClear(GL_COLOR_BUFFER_BIT); 
	
		//设置当前绘图使用的RGB颜色
   		glColor3f(1.0f, 0.0f, 0.0f); 

		//使用当前颜色绘制一个填充的矩形
	glRectf(100.0f, 150.0f, 150.0f, 100.0f); 
		
		//刷新OpenGL命令队列
		glFlush();
	}

// 函数ChangeSize是窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
	{
	if(h == 0)		h = 1;
		
		//设置视区尺寸
	glViewport(0, 0, w, h); 

	// 重置坐标系统，使投影变换复位
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 建立修剪空间的范围
   		if (w <= h) 
			glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0f, -1.0f);
    	else 
			glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

//函数SetupRC用于初始化，常用来设置场景渲染状态
void SetupRC(void)
{
	// 设置窗口的清除色为白色
   	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
}

void main(void)
   {
		//初始化GLUT库OpenGL窗口的显示模式
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

// 创建一个名为GLRect的窗口
	glutCreateWindow("GLRect"); 

	// 设置当前窗口的显示回调函数和窗口再整形回调函数
		glutDisplayFunc(RenderScene); 
    glutReshapeFunc(ChangeSize); 

   	 	SetupRC();

		//启动主GLUT事件处理循环
	glutMainLoop();
}
