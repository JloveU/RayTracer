#ifndef TEXTUREPOOL_H
#define TEXTUREPOOL_H


#include <map>
#include <string>
#include <opencv.hpp>
#include "shared_ptr.h"


class TexturePool
{

public:

    static TexturePool & instance();

    void add(const std::string &key, const std::string &imageFileName);

    const shared_ptr<const cv::Mat> get(const std::string &key) const;

private:

    TexturePool();

    void add(const std::string &key, const cv::Mat &image);

private:

    static shared_ptr<TexturePool> _instance;
    std::map<std::string, shared_ptr<const cv::Mat> > _textureImages;

};


#endif
