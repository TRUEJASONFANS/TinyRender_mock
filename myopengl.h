//
// Created by zhxie on 5/19/2023.
//

#ifndef TINYRENDER_MOCK_MYOPENGL_H
#define TINYRENDER_MOCK_MYOPENGL_H
#include "tgaimage.h"
#include "geometry.h"

extern Matrix ModelView;
extern Matrix Viewport;
extern Matrix Projection;
const float depth = 2000.f;

void viewport(int x, int y, int w, int h);
void projection(float coeff=0.f); // coeff = -1/c
void lookat(Vec3f eye, Vec3f center, Vec3f up);

/**
 * 求取重心坐标
 * @param A
 * @param B
 * @param C
 * @param P
 * @return
 */
Vec3f barycentric(Vec3i A, Vec3i B, Vec3i C, Vec3i P);

struct IShader {
    virtual ~IShader() = 0;
    virtual Vec4f vertex(int iface, int nthvert) = 0;
    virtual bool fragment(Vec3f bar, TGAColor &color) = 0;
};

void triangle(Vec4f *pts, IShader &shader, TGAImage &image, float* zbuffer);
template <typename T> T CLAMP(const T& value, const T& low, const T& high) {
    return value < low ? low : (value > high ? high : value);
}

#endif //TINYRENDER_MOCK_MYOPENGL_H
