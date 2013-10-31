#include <windows.h>
#include <gl/glut.h>
#include<gl/gl.h>
#include<gl/glu.h>

#define stripeImageWidth 64
GLubyte stripeImage[3*stripeImageWidth];
//定义纹理图像
void makeStripeImage(void)
{
	int j;
	for (j = 0; j < stripeImageWidth; j++)
	{
		stripeImage[3*j] = 255;
		stripeImage[3*j+1] =255-2*j;
		stripeImage[3*j+2] =255;
	}
}
/* 参数设置 */
GLfloat sgenparams[] = {1.0, 1.0, 1.0, 0.0};

//初始化窗口
void Initial(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);

	makeStripeImage();
	//函数设定从内存中读取纹理图并放到屏幕上的方式
	//指定内存中每个象素行起始的排列要求为字节排列（1）
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//定义纹理环境参数：调整当前亮度和颜色信息，使之适应纹理图像
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//纹理绕转使用重复方式
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//定义纹理放大和缩小函数均为GL_LINEAR
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//定义纹理
	glTexImage1D(GL_TEXTURE_1D, 0, 3, stripeImageWidth, 0, GL_RGB, GL_UNSIGNED_BYTE, stripeImage);

	//控制纹理坐标的生成
	//指定单值纹理生成参数
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//指定纹理坐标生成函数,系数由sgenparams指定
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_1D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
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
		glOrtho (-3.5f, 3.5f, -3.5f, 3.5f*h/w, -3.5, 3.5);
    else 
		glOrtho (-3.5f, 3.5f*w/h, -3.5f, 3.5f, -3.5, 3.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// 在窗口中绘制图形
void ReDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix ();
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glutSolidTeapot(1.5);
	glPopMatrix ();
	glFlush();
}

void main(void)
   {
	//初始化GLUT库OpenGL窗口的显示模式
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 

	glutCreateWindow("纹理茶壶"); 
	glutDisplayFunc(ReDraw); // 设置当前窗口的显示回调函数
    glutReshapeFunc(ChangeSize); // 为当前窗口设置窗口再整形回调函数
   	
	// 窗口初始化
    Initial();
	glutMainLoop(); //启动主GLUT事件处理循环
}
