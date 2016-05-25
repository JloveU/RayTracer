#include "TexturePool.h"


shared_ptr<TexturePool> TexturePool::_instance;


TexturePool::TexturePool()
{
}


TexturePool & TexturePool::instance()
{
    if (!_instance)
    {
        _instance.reset(new TexturePool());
    }

    return *_instance;
}


void TexturePool::add(const std::string &key, const std::string &imageFileName)
{
    add(key, cv::imread(imageFileName));
}


void TexturePool::add(const std::string &key, const cv::Mat &image)
{
    shared_ptr<const cv::Mat> _image(new cv::Mat(image.rows, image.cols, image.type()));
    image.copyTo(*_image);
    _textureImages[key] = _image;
}


const shared_ptr<const cv::Mat> TexturePool::get(const std::string &key) const
{
    std::map<std::string, shared_ptr<const cv::Mat> >::const_iterator iter = _textureImages.find(key);
    if (iter == _textureImages.end())
    {
        return NULL;
    }

    return iter->second;
}
