////////////////////////////////////////////////////////////////////////////
//实验要求：(1)理解OpenGL中的变换过程                                     //
//          (2)理解透视投影与平行投影的不同                               // 
//          (3)添加代码实现太阳、地球和月亮的运动模型                     //
//          (4)了解深度测试                                               //
//          (5)通过变换调整观察的位置与方向                               //
//          (6)加入光照模型                                               //
////////////////////////////////////////////////////////////////////////////

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void Initial()
{
    glEnable(GL_DEPTH_TEST);	// 启用深度测试
    glFrontFace(GL_CCW);		// 指定逆时针绕法表示多边形正面
    glEnable(GL_CULL_FACE);     //启用剔除效果   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );	//背景为白色
}

void SetupRC(){

    //设置光源LIGHT0的参数
    GLfloat light_diffuse[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat light_ambient[]={0.0f,0.0f,0.0f,0.0f};
    GLfloat light_specular[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);    //散射光
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);    //环境光
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);  //镜面光

    //是光源有效
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //使用颜色材质
    glEnable(GL_COLOR_MATERIAL);

    //设置材料反射属性
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}
void ChangeSize(int w, int h)
{
    if(h == 0)	h = 1;

    // 设置视区尺寸
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 设置修剪空间
    GLfloat fAspect;
    fAspect = (float)w/(float)h;
    gluPerspective(45.0, fAspect, 1.0, 500.0);
    /*
       if (w <= h) 
       glOrtho (-nRange, nRange, nRange*h/w, -nRange*h/w, -nRange*2.0f, nRange*2.0f);
       else 
       glOrtho (-nRange*w/h, nRange*w/h, nRange, -nRange, -nRange*2.0f, nRange*2.0f);
       */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void RenderScene(void)
{
    // 绕原子核旋转的角度
    static float fElect1 = 0.0f,fElect2=0.0f;

    GLfloat position[]={0.0f,0.0f,0.0f,1.0f};

    //设置光源的位置
    //glLightfv(GL_LIGHT0,GL_POSITION,position);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 重置模型视图矩阵
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    //向远移动场景
    glTranslatef(0.0f,0.0f,-300.0f);

    // 绘制红色的太阳
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidSphere(40, 60, 60);
    glRotatef(fElect1,0.0f,1.0f,0.0f);
    glTranslatef(0.0f,0.0f,0.0f);
    // 当前绘制颜色变为黄色
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_POSITION,position);

    //绘制蓝色的地球
    //保存当前的模型视图矩阵
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);//绕y轴旋转一定的角度
    glTranslatef(130.0f, 0.0f, 0.0f);//平移一段距离
    glutSolidSphere(15.0f, 60, 60);//画出电子


    // 绘制黄色的月亮
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
    glTranslatef(20.0f, 0.0f, 0.0f);
    glutSolidSphere(8.0f, 60,60);
    glPopMatrix();

    // 第三个电子
    //glPushMatrix();
    //glRotatef(-45.0f,0.0f, 0.0f, 1.0f);
    //glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    //glTranslatef(0.0f, 0.0f, 60.0f);
    //glutSolidSphere(6.0f, 15, 15);
    //glPopMatrix();

    // 增加旋转步长
    fElect1 += 2.0f;
    if(fElect1 > 360.0f)	fElect1 = 10.0f;
    fElect2+=20.0f;
    if(fElect2>360.0f){
        fElect2=10.0f;
    }
    glutSwapBuffers();
}

void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200,700);
    glutCreateWindow("日地月模型");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(500, TimerFunc, 1);

    SetupRC();

    Initial();
    glutMainLoop();

    return 0;
}
