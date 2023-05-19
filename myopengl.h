//
// Created by zhxie on 5/19/2023.
//

#ifndef TINYRENDER_MOCK_MYOPENGL_H
#define TINYRENDER_MOCK_MYOPENGL_H
#include "tgaimage.h"
#include "geometry.h"

void viewport(int x, int y, int w, int h);
void projection(float coff = 0.);
void lookat(Vec3f eye, Vec3f center, Vec3f up);

class IShader {
public:
    virtual ~IShader();
    virtual Vec3f vertex(int iface, int nthvert) =0;
    virtual bool fragment(Vec3f bar, TGAColor &color) = 0;
};

void triangle(Vec4f *pts, IShader &shader, TGAImage &image, TGAImage &zbuffer);

#endif //TINYRENDER_MOCK_MYOPENGL_H
