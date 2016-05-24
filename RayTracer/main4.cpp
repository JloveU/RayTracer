#include <iostream>
#include <string>
#include <opencv.hpp>


// �޸���Ƶ֡��
int main()
{
    std::string videoFileName("D:\\ProgramData\\VS2010Projects\\RayTracer\\RayTracer\\RenderResults\\animation1.7_2.avi");
    cv::VideoCapture videoCapture(videoFileName);

    if(!videoCapture.isOpened())
    {
        return -1;
    }

    cv::Mat frame;

    std::string videoFileNameNew("D:\\ProgramData\\VS2010Projects\\RayTracer\\RayTracer\\RenderResults\\animation1.7_2_fps15.avi");
    double fpsNew = 15;
    cv::VideoWriter videoWriter(videoFileNameNew, CV_FOURCC('M', 'J', 'P', 'G'), fpsNew, cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)), true);

    while (videoCapture.read(frame))
    {
        videoWriter << frame;
    }

    videoCapture.release();
    videoWriter.release();

    std::cout << "�޸ĺ����Ƶ�ѱ��浽�ļ� " << videoFileNameNew << std::endl;
    std::cout << "���س����˳�..." << std::endl;
    std::cin.get();

    return 0;
}
