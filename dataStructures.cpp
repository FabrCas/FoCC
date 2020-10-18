#include <iostream>


/* linear algebra vectors*/
struct vec3f{
    float x,y,z;
};

/* Coordinates systems or frames */
struct frame3f {
    float x,y,z,origin;
};

/* Image data structure*/
struct image{
    int width,height;
    Datatype pixels[];   //not a matrix, but a continue list of pixels in one row

    Datatype getPixel(int i, int j){
        return pixels[j*width+i]
    }

    void setPixels (int i, int j, Datatype v){
        pixels[j*width+i] = v;//j*width is like select the correct row, i select the element in the column
    }
};

/* Camera representantion*/
struct camera {
    frame3f frame;
    float lens, aspect, film;
    float aperture, focus;
};


/* Mesh structure not efficent*/
struct mesh{
    vec3f pos[nt][3]
};

/* better way*/
struct shape {
    vector<vec3f> pos; //vertex position
    vector<vec3f> norm; //vertex normals
    vector<vec3f> texcoord; //vertex texture coordinates

    vector<int> points; //point indices
    vector<vec2i> lines; //line indices
    vector<vec3i> triangles //triangle indices
};

/*c computing vertex normals*/
vector<vec3f> compute_normals(const vector<vec3f>& positions, const vector<vec3i>& triangles){
    //initialize normals to 0
    auto normals = vector<vec3f>(positions.size(), {0,0,0});
    //accumulate triangle normals
    for(auto t: triangles) {
        auto n = triangle_normal(positions[t.x], positions[t.y], positions[t.z]);
        auto a = triangle_area(positions[t.x], positions[t.y], positions[t.z]);
        normals[t.x] += a * n;
        normals[t.y] += a * n;
        normals[t.z] += a * n;
    }
    //normalize the result
    for(auto& n: norm) n = normalize(n);
    return norm;
}

/* Interpolating vertx data*/

vec3f normal(shape* shape, int element, vec2f uv) {   //uv -> weights
    auto t = shape->triangles[element];
    return normalize((1 - uv.x - uv.y) * shape->normals[t.x] + uv.x * shape->normals[t.y] + uv.y * shape->normals[t.z]);
}

vec3f position (shape* shape, int element, vec3f uv) {
    auto t= shape->triangles[element];
    return (1 - uv.x - uv.y) * shape->positions[t.x] + uv.x * shape->positions[t.y] + uv.y * shape->positions[t.z];
}

/*Representing materials*/

struct texture_old {
    image<vec3f> hdr;
    image<vec3b> ldr;
};

struct  legacy_material{
    vec3f emission;
    vec3f diffuse;
    vec3f specular;
    float roughness;
    texture* emission_texture;
    texture* diffuse_texture;
    texture* specular_texture;
    texture* roughness_texture;
};

struct texture {
    image<vec3f> colorf; //for color values
    image<vec3b> colorb;
    image<float> scalarf; //for scalar values
    image<byte> scalarb;
};

struct  material{
    vec3f emission;
    vec3f diffuse;
    float metallic;
    float roughness;
    texture* diffuse_texture;
    texture* metallic_texture;
    texture* roughness_texture;
};


/* Representing light */
struct texture {
    image<vec3f> colorf; //for color values
    image<vec3b> colorb;
    image<float> scalarf; //for scalar values
    image<byte> scalarb;
};

struct  legacy_material{
    vec3f emission;
    vec3f diffuse;
    float metallic;
    float roughness;
    texture* emission_texture;
    texture* diffuse_texture;
    texture* metallic_texture;
    texture* roughness_texture;
};

/*Environment maps*/

struct environment{
    frame3f frame;
    vec3f emission; //emission
    texture* emission_texture; //emission map
};

/*Representing object*/
struct object{
    frame3f frame; //coordinates frame
    shape* shape:
    material* material;
};

/*Representing scenes*/

struct scene{
    vector<camera*> cameras;
    vector<object*> objecs;
    vector<shape*> shapes;
    vector<material*> materials;
    vector<texture*> textures;
    vector<environment*> environments:
};









