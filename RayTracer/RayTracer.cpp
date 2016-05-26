// ������

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
    // ����
    Scene scene(Vec3f(0.2, 0.5, 0.8));
//     Scene scene(Vec3f(0.5, 0.5, 0.5));
//     // �������ϵ��־����������ԭ�㴦��3���ֱ�ƽ����xy��yz��zxƽ��������Σ�
//     scene.addAxes();
    // ��ӵ��棨����ƽ�棩
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
//     // �������
//     const shared_ptr<Sphere> sphere1(new Sphere(Vec3f(0.0, 4.0, 0.0),  4.0, Vec3f(1.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.5, 1.0, 0.0));
//     scene.addGeometry(sphere1);
//     const shared_ptr<Sphere> sphere2(new Sphere(Vec3f(8.0, 4.0, 0.0),  3.0, Vec3f(1.0, 1.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.6, 0.8));
//     scene.addGeometry(sphere2);
//     const shared_ptr<Sphere> sphere3(new Sphere(Vec3f(-7.0, 4.0, 0.0), 3.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.1, 0.6));
//     scene.addGeometry(sphere3);
//     // ���������
//     const shared_ptr<Triangle> triangle1(new Triangle(Vec3f(-3.0, 2.0, -9.0), Vec3f(3.0, 2.0, -9.0), Vec3f(0.0, 7.196, -9.0), Vec3f(1.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
//     scene.addGeometry(triangle1);
//     // �������Σ�����Σ�
//     const Vec3f _polygon1Vertices[5] = {Vec3f(-7.0, 2.0, -4.0), Vec3f(-3.0, 2.0, -8.0), Vec3f(-3.0, 6.0, -8.0), Vec3f(-5.0, 10.0, -6.0), Vec3f(-7.0, 6.0, -4.0)};
//     const std::vector<Vec3f> polygon1Vertices(_polygon1Vertices, _polygon1Vertices + 5);
//     const shared_ptr<Polygon> polygon1(new Polygon(polygon1Vertices, Vec3f(1.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
//     scene.addGeometry(polygon1);
//     // ��ӳ�����
//     const shared_ptr<Box> box1(new Box(Vec3f(4.0, 5.0, -7.0), Vec3f(4.0, 2.0, 2.0), Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.2));
//     scene.addGeometry(box1);
//     // ��������壨��ϼ���ͼ�Σ�
//     shared_ptr<GeometryUnion> geometryUnion1(new GeometryUnion(Vec3f(1.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.2));
//     float geometryUnion1Size = 5;
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0, 3.0, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(1.0, 1.0, 0.0))));
//     geometryUnion1->addGeometry(shared_ptr<Triangle>(new Triangle(Vec3f(-8.0 + geometryUnion1Size, 3.0, 6.0), Vec3f(-8.0, 3.0 + geometryUnion1Size, 6.0), Vec3f(-8.0, 3.0, 6.0 + geometryUnion1Size), Vec3f(1.0, 1.0, 0.0))));
//     scene.addGeometry(geometryUnion1);
    // ���Mesh
    shared_ptr<Mesh> mesh1(new Mesh(Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0, 1.0));
    mesh1->loadObj("Models/PAC-216/OBJ/PAC-216-wheel.obj");
    scene.addGeometry(mesh1);
    // ��ӹ�Դ
    const shared_ptr<Sphere> light1(new Sphere(Vec3f(60.0, 120.0, 120.0), 30.0, Vec3f(1.0, 1.0, 1.0), Vec3f(1.0, 1.0, 1.0), 1.0, 0.0, 0.0));
    scene.addGeometry(light1);
    const shared_ptr<Sphere> light2(new Sphere(Vec3f(-120.0, 120.0, -120.0), 30.0, Vec3f(1.0, 1.0, 1.0), Vec3f(0.5, 0.5, 0.5), 1.0, 0.0, 0.0));
    scene.addGeometry(light2);

    // ����չʾ����ͣ���ƶ��������ת������ĳ���
    // �����У������е����м������Լ���Դ�̶�������ֻ�ƶ����λ�ü�ָ��
    // ����˶�����Ϊ������(0,0,-20)Ϊ���ģ�40Ϊ�뾶������������ϣ�xzƽ��������Բ���˶���ͬʱ��ƽ����y��ĸ�ƽ���ϲ�����xzƽ���Ϸ����������ٰ�Բ���˶������ʼ��ָ������(0,0,-20)�������������ʼ�������ָ��ֱ���ɴ˿�ȷ�����ͷ��ָ��
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
    Camera camera(Vec3f(0.0, 0.0, 10.0), Vec3f(0.0, 0.0, -1.0), Vec3f(0.0, 1.0, 0.0), 40, 1, 1280, 720);  // ���
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
    clock_t processStartTime = clock();  // ����������ʼʱ�䣨clock()�������شӳ���ʼ���е����ڵĺ�������
    clock_t processEndTime = processStartTime;  // ������������ʱ��
    unsigned frameCount = 0;  // ��ǰ����Ⱦ��ϵ�֡��
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
        std::cout << "�� " << frameCount << " ֡��Ⱦ��ϣ���֡��ʱ " << frameEndTime - frameStartTime << " ms����ǰ����ʱ " << (processEndTime - processStartTime) / 1000 << " s��vAlpha:" << verticalCircleAlpha * 180 / 3.14 << ", hAlpha:" << horizontalCircleAlpha * 180 / 3.14 << ", x:" << camera.viewPoint().x() << ", y:" << camera.viewPoint().y() << ", z:" << camera.viewPoint().z() << std::endl;

        cv::imshow("Render result", camera.image());

        videoWriter << camera.image();

        // ���а�������ʱ�˳�ѭ����Ⱦ
        if(cv::waitKey(1) != -1)
        {
            break;
        }

        // ����ָ��ʱ��ʱ�˳�ѭ����Ⱦ
//         if(processEndTime - processStartTime > 30000)
//         {
//             break;
//         }

        // ����ָ��֡��ʱ�˳�ѭ����Ⱦ
        if(frameCount >= 300)
        {
            break;
        }
    }

    videoWriter.release();
    cv::destroyWindow("Render result");

    std::cout << "������������ " << frameCount << " ֡������������ʱ " << (processEndTime - processStartTime) / 1000 << " s��" << std::endl;
    std::cout << "�����ѱ��浽��Ƶ�ļ� " << videoFileName << std::endl;
//     std::cout << "���س����˳�..." << std::endl;
//     std::cin.get();

    return 0;
}
