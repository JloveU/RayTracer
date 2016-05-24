#include <iostream>
#include <string>
#include <opencv.hpp>


// 修改视频帧率
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

    std::cout << "修改后的视频已保存到文件 " << videoFileNameNew << std::endl;
    std::cout << "按回车键退出..." << std::endl;
    std::cin.get();

    return 0;
}
