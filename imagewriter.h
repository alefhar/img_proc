#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include <iostream>
#include <fstream>

#include "image.h"
#include "type.h"

using namespace std;

class ImageWriter
{
public:
    template <class T> bool write(Image<T> &img, Type t, string name)
    {
        bool success = false;
        switch (t) {
        case PGM:
            success = write(img, name, ".pgm", "P2");
            break;
        case PPM:
            success = write(img, name, ".ppm", "P3");
        default:
            break;
        }
        return success;
    }

private:
    template <class T> bool write(Image<T> &img, string name, string ext, string ver)
    {
        bool success = false;

        std::ofstream out;
        string file = name + ext;
        out.open(file.c_str());

        int height = img.getHeight();
        int width = img.getWidth();

        out << ver << '\n';
        out << width << ' ' << height << '\n';
        out << img.getMax() << '\n';

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width - 1; ++j)
                out << img.getPixel(i, j) << ' ';
            out << img.getPixel(i, width - 1) << '\n';
        }

        out.close();
        success = true;
        return success;
    }
};

#endif // IMAGEWRITER_H
