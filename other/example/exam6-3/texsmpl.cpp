#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

/* 创建纹理 */
#define ImageWidth 64
#define ImageHeight 64
GLubyte Image[ImageWidth][ImageHeight][3];

void makeImage(void)
{
	int i, j, r,g,b;
	for (i = 0; i < ImageWidth; i++)
	{
		for (j = 0; j < ImageHeight; j++)
		{
			r=(i*j)%255;
			g=(4*i)%255;
			b=(4*j)%255;
			Image[i][j][0] = (GLubyte) r;
			Image[i][j][1] = (GLubyte) g;
			Image[i][j][2] = (GLubyte) b;
		}
	}
}

//初始化窗口
void Initial(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	makeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	/* 定义纹理 */
	glTexImage2D(GL_TEXTURE_2D, 0, 3, ImageWidth,
	ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &Image[0][0][0]);
	
	/* 控制滤波 */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	/* 说明映射方式*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	
	/* 启动纹理映射 */
	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_FLAT);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
   	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.6);
}

// 在窗口中绘制图形
void ReDraw(void)
{
	//用当前背景色填充窗口
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 设置纹理坐标和物体几何坐标 */
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

		glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
		glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
	glEnd();

// 刷新OpenGL命令队列
	glFlush();
}

void main(void)
   {
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("简单纹理映射"); 
	glutDisplayFunc(ReDraw); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
   	
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
}
