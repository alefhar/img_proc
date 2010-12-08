#ifndef FILTERS_H
#define FILTERS_H

#include <vector>
#include <algorithm>

#include "image.h"

class Filters
{
private:

public:
    template <class T> void average(Image<T> &img, Image<T> &filtered, int size)
    {
        int height = img.getHeight();
        int width = img.getWidth();
        T max = img.getMaxAsT();

        T sum = 0;
        T pixel;

        std::cout << "averaging...\n";

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; j++) {
                for (int k = i - size; k < i + size; ++k)
                    for (int l = j - size; l < j + size; ++l) {
                        if (k < 0 || l < 0 || k >= height || l >= width)
                            sum += max;
                        else
                            sum += img.getPixel(k, l);
                    }
                pixel = (sum / (size * size)) % max;
                filtered.setPixel(i, j, pixel);
                sum = 0;
            }
    }

    template <class T> void median(Image<T> &img, Image<T> &filtered, int size)
    {
        int height = img.getHeight();
        int width = img.getWidth();
        T max = img.getMaxAsT();

        std::vector<T> pixels;

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; j++) {
                for (int k = i - size; k < i + size; ++k)
                    for (int l = j - size; l < j + size; ++l) {
                        if (k < 0 || l < 0 || k >= height || l >= width)
                            pixels.push_back(max);
                        else
                            pixels.push_back(img.getPixel(k, l));
                    }
                std::sort(pixels.begin(), pixels.end());
                filtered.setPixel(i, j, pixels[pixels.size() / 2]);
                pixels.clear();
            }
    }

    template <class T> void negative(Image<T> &img, Image<T> &filtered)
    {
        int height = img.getHeight();
        int width = img.getWidth();
        int max = img.getMax();

        T pixel;

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j) {
                pixel = max - img.getPixel(i, j);
                filtered.setPixel(i, j, pixel);
            }
    }
};

#endif // FILTERS_H
