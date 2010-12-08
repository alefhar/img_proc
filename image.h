#ifndef IMAGE_H
#define IMAGE_H

#include <string>

using namespace std;

template <class T> class Image
{
private:
    int _height;
    int _width;
    T ** _data;
    int _max;
    T _max_T;
    std::string _file;
    std::string _name;

    bool _allocated;

public:
    Image<T>(string name)
    {
        _height = 0;
        _width = 0;
        _data = 0;
        _name = name;
    }

    Image<T>(Image<T> &orig)
    {
        _height = orig.getHeight();
        _width = orig.getWidth();
        _name = orig.getName();
        _max = orig.getMax();

        _data = new T*[_height];

        for (int i = 0; i < _height; ++i)
            _data[i] = new T[_width];

        for (int i = 0; i < _height; ++i)
            for (int j = 0; j < _width; ++j)
                _data[i][j] = orig.getPixel(i, j);
    }

    ~Image()
    {
        for (int i = 0; i < _height; ++i)
            delete [] _data[i];
        delete [] _data;
    }

    bool allocate(int height, int width)
    {
        if (_allocated)
            return false;

        _height = height;
        _width = width;
        _data = new T*[_height];
        for (int i = 0; i < _height; i++)
            _data[i] = new T[_width];

        return true;
    }

    void setPixel(int x, int y, T pixel)
    {
        _data[x][y] = pixel;
    }

    T getPixel(int x, int y)
    {
        return _data[x][y];
    }

    int getHeight()
    {
        return _height;
    }

    int getWidth()
    {
        return _width;
    }

    void setMax(int max)
    {
        _max = max;
        _max_T = T(max);
    }

    int getMax()
    {
        return _max;
    }

    T getMaxAsT()
    {
        return _max_T;
    }

    void setName(std::string name)
    {
        _name = name;
    }

    std::string getName()
    {
        return _name;
    }
};

#endif // IMAGE_H
