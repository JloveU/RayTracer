// 主程序

#include <iostream>
#include <string>
#include <opencv.hpp>
#include <time.h>
#include "Matrix.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Box.h"
#include "GeometryUnion.h"
#include "Mesh.h"
#include "shared_ptr.h"


int main()
{
    // 场景
    Scene scene(Vec3f(0.2, 0.5, 0.8));
//     Scene scene(Vec3f(0.5, 0.5, 0.5));
//     // 添加坐标系标志（即在坐标原点处放3个分别平行于xy、yz、zx平面的三角形）
//     scene.addAxes();
    // 添加地面（无限平面）
//     scene.addGeometry(new Plane(Vec3f(0.0, -4.0, 0.0), Vec3f(0.0, 1.0, 0.0), Vec3f(0.6, 0.6, 0.6), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
//     std::string groundTextureFileName("./Textures/texture2.png");
//     std::string groundTextureKey("ground_texture");
//     TexturePool::instance().add(groundTextureKey, groundTextureFileName);
//     float groundSize = 15;
//     const shared_ptr<Triangle> groundTriangle1(new Triangle(Vec3f(-groundSize, 0.0, groundSize), Vec3f(groundSize, -0.0, groundSize), Vec3f(groundSize, 0.0, -groundSize), Vec3f(0.4, 0.4, 0.4), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0, 1.0));
//     groundTriangle1->setTexture(groundTextureKey);
//     groundTriangle1->setTextureCoordinates(Vec2f(0.0, 0.0), Vec2f(10.0, 0.0), Vec2f(10.0, 10.0));
//     scene.addGeometry(groundTriangle1);
//     const shared_ptr<Triangle> groundTriangle2(new Triangle(Vec3f(groundSize, 0.0, -groundSize), Vec3f(-groundSize, 0.0, -groundSize), Vec3f(-groundSize, 0.0, groundSize), Vec3f(0.4, 0.4, 0.4), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0, 1.0));
//     groundTriangle2->setTexture(groundTextureKey);
//     groundTriangle2->setTextureCoordinates(Vec2f(10.0, 10.0), Vec2f(0.0, 10.0), Vec2f(0.0, 0.0));
//     scene.addGeometry(groundTriangle2);
//     // 添加球体
//     const shared_ptr<Sphere> sphere1(new Sphere(Vec3f(0.0, 4.0, 0.0),  4.0, Vec3f(1.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.5, 1.0, 0.0));
//     scene.addGeometry(sphere1);
//     const shared_ptr<Sphere> sphere2(new Sphere(Vec3f(8.0, 4.0, 0.0),  3.0, Vec3f(1.0, 1.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.6, 0.8));
//     scene.addGeometry(sphere2);
//     const shared_ptr<Sphere> sphere3(new Sphere(Vec3f(-7.0, 4.0, 0.0), 3.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.1, 0.6));
//     scene.addGeometry(sphere3);
//     // 添加三角形
//     const shared_ptr<Triangle> triangle1(new Triangle(Vec3f(-3.0, 2.0, -9.0), Vec3f(3.0, 2.0, -9.0), Vec3f(0.0, 7.196, -9.0), Vec3f(1.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
//     scene.addGeometry(triangle1);
//     // 添加五边形（多边形）
//     const Vec3f _polygon1Vertices[5] = {Vec3f(-7.0, 2.0, -4.0), Vec3f(-3.0, 2.0, -8.0), Vec3f(-3.0, 6.0, -8.0), Vec3f(-5.0, 10.0, -6.0), Vec3f(-7.0, 6.0, -4.0)};
//     const std::vector<Vec3f> polygon1Vertices(_polygon1Vertices, _polygon1Vertices + 5);
//     const shared_ptr<Polygon> polygon1(new Polygon(polygon1Vertices, Vec3f(1.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
//     scene.addGeometry(polygon1);
//     // 添加长方体
//     const shared_ptr<Box> box1(new Box(Vec3f(4.0, 5.0, -7.0), Vec3f(4.0, 2.0, 2.0), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.2));
//     scene.addGeometry(box1);
//     // 添加四面体（组合几何图形）
//     shared_ptr<GeometryUnion> geometryUnion1(new GeometryUnion(Vec3f(1.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.2));
//     float geometryUnion1Size = 5;
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(1.0, 1.0, 0.0))));
//     scene.addGeometry(geometryUnion1);
    // 添加Mesh
    shared_ptr<Mesh> mesh1(new Mesh(Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0, 1.0));
    mesh1->loadObj("Models/PAC-216/OBJ/PAC-216-wheel.obj");
    scene.addGeometry(mesh1);
    // 添加光源
    const shared_ptr<Sphere> light1(new Sphere(Vec3f(60.0, 120.0, 120.0), 30.0, Vec3f(1.0, 1.0, 1.0), Vec3f(1.0, 1.0, 1.0), 1.0, 0.0, 0.0));
    scene.addGeometry(light1);
    const shared_ptr<Sphere> light2(new Sphere(Vec3f(-120.0, 120.0, -120.0), 30.0, Vec3f(1.0, 1.0, 1.0), Vec3f(0.5, 0.5, 0.5), 1.0, 0.0, 0.0));
    scene.addGeometry(light2);

    // 动画展示（不停地移动相机并且转动相机的朝向）
    // 动画中，场景中的所有几何体以及光源固定不动，只移动相机位置及指向
    // 相机运动规则为：在以(0,0,-20)为球心，40为半径的球体外表面上，xz平面做匀速圆周运动，同时在平行于y轴的各平面上并且在xz平面上方做反复匀速半圆周运动，相机始终指向球心(0,0,-20)，并且相机像面始终与相机指向垂直（由此可确定相机头顶指向）
//     Vec3f cameraMotionSphereCenter(0.0, 0.0, 0.0);
    Vec3f cameraMotionSphereCenter(1.17518, 0.663388, -0.00610712);  // PAC-216-wheel.obj
//     float circleRadius = 40;
    float circleRadius = 3;  // PAC-216-wheel.obj
    float horizontalCircleRadius = circleRadius;
    float horizontalCircleAlpha = 0.0;
    float horizontalCircleSpeed = 3 * 3.14 / 180;
    float verticalCircleRadius = circleRadius;
    float verticalCircleAlpha = 60 * 3.14 / 180;
    float verticalCircleSpeed = 2 * 3.14 / 180;
    bool verticalCircleSpeedPositive = true;
    Camera camera(Vec3f(0.0, 0.0, 10.0), Vec3f(0.0, 0.0, -1.0), Vec3f(0.0, 1.0, 0.0), 40, 1, 1280, 720);  // 相机
    camera.SetViewPoint(Vec3f(cameraMotionSphereCenter.x() + horizontalCircleRadius * sin(horizontalCircleAlpha) * cos(verticalCircleAlpha), cameraMotionSphereCenter.y() + verticalCircleRadius * sin(verticalCircleAlpha), cameraMotionSphereCenter.z() + horizontalCircleRadius * cos(horizontalCircleAlpha) * cos(verticalCircleAlpha)));
    camera.SetViewDirection(cameraMotionSphereCenter - camera.viewPoint());
    camera.SetHeadDirection(camera.viewDirection().cross(Vec3f(-cos(horizontalCircleAlpha), 0, sin(horizontalCircleAlpha))));
    Mat4f sphere2RotateMatrix = Matrix::formRotateMatrix(Vec3f(0, 1, 0), 3 * 3.14 / 180);
    Mat4f triangle1RotateMatrix = Matrix::formRotateMatrix(Vec3f(0, 1, 0), 5 * 3.14 / 180);
    Mat4f mesh1RotateMatrix = Matrix::formRotateMatrix(Vec3f(1.17518, 0.663388, -0.00610712), 5 * 3.14 / 180);
    Mat4f light2RotateMatrix = Matrix::formRotateMatrix(Vec3f(0, 1, 0), -2 * 3.14 / 180);
    std::stringstream videoFileNameStream;
    videoFileNameStream << "./RenderResults/animationTemp_" << time(0) << ".avi";
    std::string videoFileName(videoFileNameStream.str());
    cv::VideoWriter videoWriter(videoFileName, CV_FOURCC('M', 'J', 'P', 'G'), 20, camera.image().size(), true);
    clock_t processStartTime = clock();  // 整个动画开始时间（clock()函数返回从程序开始运行到现在的毫秒数）
    clock_t processEndTime = processStartTime;  // 整个动画结束时间
    unsigned frameCount = 0;  // 当前已渲染完毕的帧数
    while (true)
    {
        horizontalCircleAlpha += horizontalCircleSpeed;
        if (verticalCircleAlpha < 0 * 3.14 / 180 || verticalCircleAlpha > 80 * 3.14 / 180)
        {
            verticalCircleSpeedPositive = !verticalCircleSpeedPositive;
        }
        verticalCircleAlpha += verticalCircleSpeedPositive ? verticalCircleSpeed : -verticalCircleSpeed;
        
//         camera.SetViewPoint(Vec3f(cameraMotionSphereCenter.x() + horizontalCircleRadius * sin(horizontalCircleAlpha) * cos(verticalCircleAlpha), cameraMotionSphereCenter.y() + verticalCircleRadius * sin(verticalCircleAlpha), cameraMotionSphereCenter.z() + horizontalCircleRadius * cos(horizontalCircleAlpha) * cos(verticalCircleAlpha)));
//         camera.SetViewDirection(cameraMotionSphereCenter - camera.viewPoint());
//         camera.SetHeadDirection(camera.viewDirection().cross(Vec3f(-cos(horizontalCircleAlpha), 0, sin(horizontalCircleAlpha))));

//         sphere2->transform(sphere2RotateMatrix);
//         triangle1->transform(triangle1RotateMatrix);
        mesh1->transform(mesh1RotateMatrix);
//         light2->transform(light2RotateMatrix);

        clock_t frameStartTime = clock();
        camera.render(scene);
        clock_t frameEndTime = clock();
        processEndTime = clock();
        frameCount++;
        std::cout << "第 " << frameCount << " 帧渲染完毕，该帧用时 " << frameEndTime - frameStartTime << " ms，当前总用时 " << (processEndTime - processStartTime) / 1000 << " s。vAlpha:" << verticalCircleAlpha * 180 / 3.14 << ", hAlpha:" << horizontalCircleAlpha * 180 / 3.14 << ", x:" << camera.viewPoint().x() << ", y:" << camera.viewPoint().y() << ", z:" << camera.viewPoint().z() << std::endl;

        cv::imshow("Render result", camera.image());

        videoWriter << camera.image();

        // 当有按键按下时退出循环渲染
        if(cv::waitKey(1) != -1)
        {
            break;
        }

        // 到达指定时间时退出循环渲染
//         if(processEndTime - processStartTime > 30000)
//         {
//             break;
//         }

        // 到达指定帧数时退出循环渲染
        if(frameCount >= 300)
        {
            break;
        }
    }

    videoWriter.release();
    cv::destroyWindow("Render result");

    std::cout << "动画结束！共 " << frameCount << " 帧，整个过程用时 " << (processEndTime - processStartTime) / 1000 << " s。" << std::endl;
    std::cout << "动画已保存到视频文件 " << videoFileName << std::endl;
//     std::cout << "按回车键退出..." << std::endl;
//     std::cin.get();

    return 0;
}
