#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

int        Width;  /* 窗口宽度 */
int        Height; /* 窗口高度 */
static GLubyte smiley[] = /* 16x16 笑脸 */
{
    0x03, 0xc0, 0, 0, /*                 ****                 */
    0x0f, 0xf0, 0, 0, /*               ********               */
    0x1e, 0x78, 0, 0, /*              ****  ****              */
    0x39, 0x9c, 0, 0, /*             ***  **  ***             */
    0x77, 0xee, 0, 0, /*            *** ****** ***            */
    0x6f, 0xf6, 0, 0, /*            ** ******** **            */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0xff, 0xff, 0, 0, /*           ****************           */
    0x73, 0xce, 0, 0, /*            ***  ****  ***            */
    0x73, 0xce, 0, 0, /*            ***  ****  ***            */
    0x3f, 0xfc, 0, 0, /*             ************             */
    0x1f, 0xf8, 0, 0, /*              **********              */
    0x0f, 0xf0, 0, 0, /*               ********               */
    0x03, 0xc0, 0, 0  /*                 ****                 */
};

//初始化窗口
void Initial(void)
{
     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// 窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h)
{
	if(h == 0)		h = 1;
	
   	glViewport(0, 0, w, h);
	
	Width = w;
	Height = h;
	// 重置坐标系统
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

// 在窗口中绘制图形
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f (1.0, 0.0, 1.0);
	glRasterPos2i (100, 200);
	glBitmap (16, 16, 0.0, 0.0, 30.0, 30.0, smiley);
	glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);

	glColor3f (1.0, 1.0, 0.0);
	glRasterPos2i (150, 200);
	glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);

	glColor3f (0.0, 0.0, 1.0);
	int i;
	for(i=0;i<20;i++)
	{
		glRasterPos2i (rand()% Width, rand()%Height);
		glBitmap (16, 16, 0.0, 0.0, 0.0, 0.0, smiley);
	}
	// 刷新OpenGL命令队列
    glFlush();
}

void main(void)
{
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutCreateWindow("位图"); 
	glutDisplayFunc(ReDraw); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
}
