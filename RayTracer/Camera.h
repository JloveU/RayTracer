#ifndef CAMERA_H
#define CAMERA_H


#include <opencv.hpp>
#include "Matrix.h"
#include "Scene.h"


// 相机
class Camera
{

public:
    Camera(const Vec3f &viewPoint=Vec3f(0.0, 0.0, 0.0), const Vec3f &viewDirection=Vec3f(0.0, 0.0, -1.0), const Vec3f &headDirection=Vec3f(0.0, 1.0, 0.0), const float verticalFOV=30, const float distanceFromEye2Image=1, const unsigned imageWidth=640, const unsigned imageHeight=480);

    inline const Vec3f & viewPoint() const
    {
        return _viewPoint;
    }

    inline const Vec3f & viewDirection() const
    {
        return _viewDirection;
    }

    inline const Vec3f & headDirection() const
    {
        return _headDirection;
    }

    inline float verticalFOV() const
    {
        return _verticalFOV;
    }

    inline float distanceFromEye2Image() const
    {
        return _distanceFromEye2Image;
    }

    inline unsigned imageWidth() const
    {
        return _imageWidth;
    }

    inline unsigned imageHeight() const
    {
        return _imageHeight;
    }

    inline const cv::Mat & image() const
    {
        return _image;
    }

    void SetViewPoint(const Vec3f &viewPoint)
    {
        _viewPoint = viewPoint;
    }

    void SetViewDirection(const Vec3f &viewDirection)
    {
        _viewDirection = viewDirection * (1.0 / viewDirection.norm());
    }

    void SetHeadDirection(const Vec3f &headDirection)
    {
        _headDirection = headDirection * (1.0 / headDirection.norm());
    }

    void SetVerticalFOV(const float verticalFOV)
    {
        _verticalFOV = verticalFOV;
    }

    void SetDistanceFromEye2Image(const float distanceFromEye2Image)
    {
        _distanceFromEye2Image = distanceFromEye2Image;
    }

    void SetImageSize(const unsigned imageWidth, const unsigned imageHeight)
    {
        _imageWidth = imageWidth;
        _imageHeight = imageHeight;
    }

    // 渲染场景
    const cv::Mat & render(const Scene &scene);

private:
    Vec3f _viewPoint;  // 视点
    Vec3f _viewDirection;  // 视线前方指向的方向上的单位向量（与像面垂直向前）
    Vec3f _headDirection;  // 头顶指向的方向上的单位向量
    float _verticalFOV;  // 垂直视场角
    float _distanceFromEye2Image;  // 从眼睛到像面的距离
    int _imageWidth, _imageHeight;  // 图像宽高
    cv::Mat _image;  // 图像

};


#endif
