#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "myopengl.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

Vec3f light_dir(1,1,1);
Vec3f       eye(1,1,3);
Vec3f    center(0,0,0);
Vec3f        up(0,1,0);

class GouraudSharder : public IShader {
public:
    Vec3f varying_intensity; // written by vertex shader, read by fragment shader
    mat<2,3,float> varying_uv;        // same as above

    Vec4f vertex(int iface, int nthvert) override {
        Vec4f gl_Vertex = embed<4>(model->vert(iface, nthvert)); // read the vertex from .obj file
        varying_uv.set_col(nthvert, model->uv(iface, nthvert));
        gl_Vertex = Viewport * Projection * ModelView * gl_Vertex;
        varying_intensity[nthvert] = std::max(0.f, model->normal(iface, nthvert)*light_dir); // get diffuse lighting intensity
        return proj<4>(gl_Vertex/gl_Vertex[3]);
    }

    bool fragment(Vec3f bar, TGAColor &color) override {
        float intensity = varying_intensity*bar;   // interpolate intensity for the current pixel
        auto uv = varying_uv*bar;   // interpolate intensity for the current pixel
        color = model->diffuse(uv)*intensity; // well duh
        return false;
    }

    ~GouraudSharder() override {

    }
};

class DepthShader : public IShader {
    mat<3,3,float> varying_tri;
    public :
    DepthShader() : varying_tri() {}

    virtual Vec4f vertex(int iface, int nthvert) {
        Vec4f gl_Vertex = embed<4>(model->vert(iface, nthvert)); // read the vertex from .obj file
        gl_Vertex = Viewport*Projection*ModelView*gl_Vertex;          // transform it to screen coordinates
        varying_tri.set_col(nthvert, proj<3>(gl_Vertex/gl_Vertex[3]));
        return gl_Vertex;
    }

    virtual bool fragment(Vec3f bar, TGAColor &color) {
        Vec3f p = varying_tri*bar;
        color = TGAColor(255, 255, 255)*(p.z/depth);
        return false;
    }
    ~DepthShader() override {

    }
};


int main(int argc, char** argv) {
    if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("african_head.obj");
    }

    light_dir.normalize();


    Matrix M = Viewport*Projection*ModelView;

    TGAImage image(width, height, TGAImage::RGB);
    float *zbuffer = new float[width*height];
    float *shadowbuffer  = new float[width*height];

    {
        TGAImage depth(width, height, TGAImage::RGB);
        lookat(eye, center, up);
        viewport(width/8, height/8, width*3/4, height*3/4);
        projection(-1.f/(eye-center).norm());

        DepthShader depthshader;
        Vec4f screen_coords[3];
        for (int i=0; i<model->nfaces(); i++) {
            for (int j=0; j<3; j++) {
                screen_coords[j] = depthshader.vertex(i, j);
            }
            triangle(screen_coords, depthshader, depth, shadowbuffer);
        }
        depth.flip_vertically(); // to place the origin in the bottom left corner of the image
        depth.write_tga_file("depth.tga");
    }


    delete model;
    delete [] zbuffer;
    delete [] shadowbuffer;
    return 0;
}