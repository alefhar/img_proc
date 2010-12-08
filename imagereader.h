#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "image.h"
#include "type.h"

using namespace std;
class ImageReader
{
public:
    template <class T> bool read(Image<T> &img, Type t, string name)
    {
        bool success = false;
        switch (t) {
        case PGM:
            success = read(img, name, ".pgm");
            break;
        case PPM:
            success = read(img, name, ".ppm");
        default:
            break;
        }
        return success;
    }

private:
    template <class T> bool read(Image<T> &img, string name, string ext)
    {
        bool success = false;
        int height, width, max;

        bool v, s, m;
        v = s = m = false;

        T pixel;
        string temp;
        string file = name + ext;

        ifstream in(file.c_str(), ios::in);
        stringstream ss(stringstream::in | stringstream::out);

        if (in.is_open()) {
            // read header, ignore comments
            while ((!v || !s || !m) && getline(in, temp)) {
                if (temp[0] == '#')
                    continue;
                else if (!v) {
                    v = true;
                } else if (!s) {
                    ss.str(temp);
                    ss >> width >> height;
                    ss.clear();
                    s = true;
                } else if (!m) {
                    ss.str(temp);
                    ss >> max;
                    ss.clear();
                    m = true;
                }
            }

            // header read, allocate memory
            success = img.allocate(height, width);
            if (!success)
                return false;
            img.setMax(max);

            // read color data
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j) {
                in >> pixel;
                img.setPixel(i, j, pixel);
            }

            in.close();
        }

        return success;
    }
};

#endif // IMAGEREADER_H
