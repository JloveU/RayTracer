// 主程序

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <opencv.hpp>
#include <math.h>
#include <time.h>
#include "Vector.h"
#include "Geometry.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"


int main()
{
    //场景
    Scene scene(Vec3f(1.0, 1.0, 1.0));
    // 添加非光源几何体
    scene.addGeometry(new Sphere(Vec3f(0.0, 0.0, -20.0),  4.0, Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(5.0, -1.0, -15.0), 2.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(5.0, 0.0, -25.0),  3.0, Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(-5.5, 0.0, -15.0), 3.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Plane(Vec3f(0.0, -4.0, 0.0), Vec3f(0.0, 1.0, 0.0), Vec3f(0.2, 0.2, 0.2), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    // 添加光源
    scene.addGeometry(new Sphere(Vec3f(-10.0, 50.0, -30.0), 3.0, Vec3f(0.0, 0.0, 0.0), Vec3f(3.0, 3.0, 3.0), 0.0, 0.0));

    // 相机
    Camera camera(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, -1.0), Vec3f(0.0, 1.0, 0.0), 30, 1, 640, 480);

    // 动画展示（不停地移动相机并且转动相机的朝向）
    // 动画中，场景中的所有几何体以及光源固定不动，只移动相机位置及指向
    // 相机运动规则为：在以(0,0,-20)为球心，40为半径的球体外表面上，xz平面做匀速圆周运动，同时在平行于y轴的各平面上并且在xz平面上方做反复匀速半圆周运动，相机始终指向球心(0,0,-20)，并且相机像面始终与相机指向垂直（由此可确定相机头顶指向）
    float horizontalCircleRadius = 40;
    float horizontalCircleAlpha = 0.0;
    float horizontalCircleSpeed = 2 * 3.14 / 180;
    float verticalCircleRadius = 40;
    float verticalCircleAlpha = 0.0;
    float verticalCircleSpeed = 5 * 3.14 / 180;
    bool verticalCircleSpeedPositive = true;
    std::string videoFileName("animation1.avi");
    cv::VideoWriter videoWriter(videoFileName, CV_FOURCC('M', 'J', 'P', 'G'), 5, camera.image().size(), true);
    clock_t processStartTime = clock();  // 整个动画开始时间（clock()函数返回从程序开始运行到现在的毫秒数）
    clock_t processEndTime = processStartTime;  // 整个动画结束时间
    while (true)
    {
        horizontalCircleAlpha += horizontalCircleSpeed;
        if (verticalCircleAlpha < 0 * 3.14 / 180 || verticalCircleAlpha > 80 * 3.14 / 180)
        {
            verticalCircleSpeedPositive = !verticalCircleSpeedPositive;
        }
        verticalCircleAlpha += verticalCircleSpeedPositive ? verticalCircleSpeed : -verticalCircleSpeed;
        camera.SetViewPoint(Vec3f(horizontalCircleRadius * sin(horizontalCircleAlpha) * cos(verticalCircleAlpha), verticalCircleRadius * sin(verticalCircleAlpha), -20 +  horizontalCircleRadius * cos(horizontalCircleAlpha) * cos(verticalCircleAlpha)));
        camera.SetViewDirection(Vec3f(0, 0, -20) - camera.viewPoint());
        camera.SetHeadDirection(camera.viewDirection().cross(Vec3f(-cos(horizontalCircleAlpha), 0, sin(horizontalCircleAlpha))));

        clock_t frameStartTime = clock();
        camera.render(scene);
        clock_t frameEndTime = clock();
        processEndTime = clock();
        std::cout << "帧渲染完毕，该帧用时 " << frameEndTime - frameStartTime << " ms，当前总用时 " << (processEndTime - processStartTime) / 1000 << " s。vAlpha:" << verticalCircleAlpha * 180 / 3.14 << ", hAlpha:" << horizontalCircleAlpha * 180 / 3.14 << ", x:" << camera.viewPoint().x << ", y:" << camera.viewPoint().y << ", z:" << camera.viewPoint().z << std::endl;

        cv::imshow("Render result", camera.image());

        videoWriter << camera.image();

        // 当有按键按下时退出循环渲染
        if(cv::waitKey(1) != -1)
        {
            break;
        }

        // 到达指定时间时退出循环渲染
        if(processEndTime - processStartTime > 30000)
        {
            break;
        }
    }

    cv::destroyWindow("Render result");

    std::cout << "动画结束！整个过程用时 " << (processEndTime - processStartTime) / 1000 << " s。" << std::endl;
    std::cout << "动画已保存到视频文件 " << videoFileName << std::endl;
    std::cout << "按任意键退出..." << std::endl;
    std::cin.get();

    return 0;
}
