说明：
    (1)dll目录中保存OpenGL程序运行时所需的动态链接库，使用时可以将目录中的所有文件拷贝到
系统文件夹（操作系统目录中的system32目录）。
    (2)include和lib目录中存有OpenGL程序编译时所需的头文件和库文件，编译时需加到VC环境中。
具体方法：在VC环境中选择tools下的Options命令，打开options对话框，选择directories页，在“show
directories for”项中选择“include files”，在“directories”列表项中加入“拷贝目录\include”
目录;然后在“show directories for”项中选择“library files”，在“directories”列表项中加入
“拷贝目录\lib”目录。
    (3)example中保存了多个OpenGL示例程序。
    (4)上机实验目录中包括两次实验的原始框架以及OpenGL编程文档。
    (5)glu.lib glut32.lib opengl.lib