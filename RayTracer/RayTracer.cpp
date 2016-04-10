// ������

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
    //����
    Scene scene(Vec3f(1.0, 1.0, 1.0));
    // ��ӷǹ�Դ������
    scene.addGeometry(new Sphere(Vec3f(0.0, 0.0, -20.0),  4.0, Vec3f(1.0, 0.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(5.0, -1.0, -15.0), 2.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(5.0, 0.0, -25.0),  3.0, Vec3f(0.0, 0.0, 1.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Sphere(Vec3f(-5.5, 0.0, -15.0), 3.0, Vec3f(0.0, 1.0, 0.0), Vec3f(0.0, 0.0, 0.0), 0.0, 1.0));
    scene.addGeometry(new Plane(Vec3f(0.0, -4.0, 0.0), Vec3f(0.0, 1.0, 0.0), Vec3f(0.2, 0.2, 0.2), Vec3f(0.0, 0.0, 0.0), 0.0, 0.0));
    // ��ӹ�Դ
    scene.addGeometry(new Sphere(Vec3f(-10.0, 50.0, -30.0), 3.0, Vec3f(0.0, 0.0, 0.0), Vec3f(3.0, 3.0, 3.0), 0.0, 0.0));

    // ���
    Camera camera(Vec3f(0.0, 0.0, 0.0), Vec3f(0.0, 0.0, -1.0), Vec3f(0.0, 1.0, 0.0), 30, 1, 640, 480);

    // ����չʾ����ͣ���ƶ��������ת������ĳ���
    // �����У������е����м������Լ���Դ�̶�������ֻ�ƶ����λ�ü�ָ��
    // ����˶�����Ϊ������(0,0,-20)Ϊ���ģ�40Ϊ�뾶������������ϣ�xzƽ��������Բ���˶���ͬʱ��ƽ����y��ĸ�ƽ���ϲ�����xzƽ���Ϸ����������ٰ�Բ���˶������ʼ��ָ������(0,0,-20)�������������ʼ�������ָ��ֱ���ɴ˿�ȷ�����ͷ��ָ��
    float horizontalCircleRadius = 40;
    float horizontalCircleAlpha = 0.0;
    float horizontalCircleSpeed = 2 * 3.14 / 180;
    float verticalCircleRadius = 40;
    float verticalCircleAlpha = 0.0;
    float verticalCircleSpeed = 5 * 3.14 / 180;
    bool verticalCircleSpeedPositive = true;
    std::string videoFileName("animation1.avi");
    cv::VideoWriter videoWriter(videoFileName, CV_FOURCC('M', 'J', 'P', 'G'), 5, camera.image().size(), true);
    clock_t processStartTime = clock();  // ����������ʼʱ�䣨clock()�������شӳ���ʼ���е����ڵĺ�������
    clock_t processEndTime = processStartTime;  // ������������ʱ��
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
        std::cout << "֡��Ⱦ��ϣ���֡��ʱ " << frameEndTime - frameStartTime << " ms����ǰ����ʱ " << (processEndTime - processStartTime) / 1000 << " s��vAlpha:" << verticalCircleAlpha * 180 / 3.14 << ", hAlpha:" << horizontalCircleAlpha * 180 / 3.14 << ", x:" << camera.viewPoint().x << ", y:" << camera.viewPoint().y << ", z:" << camera.viewPoint().z << std::endl;

        cv::imshow("Render result", camera.image());

        videoWriter << camera.image();

        // ���а�������ʱ�˳�ѭ����Ⱦ
        if(cv::waitKey(1) != -1)
        {
            break;
        }

        // ����ָ��ʱ��ʱ�˳�ѭ����Ⱦ
        if(processEndTime - processStartTime > 30000)
        {
            break;
        }
    }

    cv::destroyWindow("Render result");

    std::cout << "��������������������ʱ " << (processEndTime - processStartTime) / 1000 << " s��" << std::endl;
    std::cout << "�����ѱ��浽��Ƶ�ļ� " << videoFileName << std::endl;
    std::cout << "��������˳�..." << std::endl;
    std::cin.get();

    return 0;
}
