// 简单的光线追踪程序
// 参考：http://www.jianshu.com/p/81329c6c7002
//Compile using clang under Windows: cl -o RayTracer.exe RayTracer.cpp

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

#define M_PI 3.141592653589
#define INFINITY 1e8

//define class Vec_3, used in ray direction
template<typename T>
class Vec_3
{
public:
    T x, y, z;
    Vec_3(): x(T(0)), y(T(0)), z(T(0)) {}
    Vec_3(T xx): x(xx), y(xx), z(xx) {}
    Vec_3(T xx, T yy, T zz): x(xx), y(yy), z(zz){}
    Vec_3<T> operator * (const T &f) const
    { return Vec_3<T>(x * f, y * f, z * f);}
    Vec_3<T> operator * (const Vec_3<T> &v) const 
    { return Vec_3<T>(x * v.x, y * v.y, z * v.z);}
    T dot(const Vec_3<T> &v) const
    { return x * v.x + y * v.y + z * v.z;}
    Vec_3<T> operator - (const Vec_3<T> &v) const
    { return Vec_3<T>( x - v.x, y - v.y, z - v.z);}
    Vec_3<T> operator + (const  Vec_3<T> &v) const
    { return Vec_3<T>( x + v.x, y + v.y, z + v.z);}        
    Vec_3<T>& operator += (const Vec_3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    } 
    Vec_3<T>& operator *= (const Vec_3<T> &v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vec_3<T> operator - () const
    {
        return Vec_3<T>(-x, -y, -z);    
    }
    T length2() const
    {
        return x * x + y * y + z * z;     
    }
    T length() const
    {
        return sqrt(length2());    
    } 
    Vec_3& normal()
    {
        T nor2= length2();
        if (nor2 > 0)
        {
            T nor2_inv= 1 / sqrt(nor2);
            x *= nor2_inv;
            y *= nor2_inv;
            z *= nor2_inv;
        }
        return *this;
    }
    friend std::ostream & operator << (std::ostream &os, const Vec_3<T> &v)
    {
        os<< "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }    
};

typedef Vec_3<float> Vec_3f;

//Define Sphere Class
class Sphere
{
public:
    Vec_3f center;
    float radius, radius2;
    Vec_3f surfaceColor, emissionColor;
    float transparency, reflection;
    Sphere(
        const Vec_3f &c,
        const float &r,
        const Vec_3f &sc,
        const float &refl = 0,
        const float &transp = 0,
        const Vec_3f &ec = 0):
    center(c), radius(r), radius2(r * r), surfaceColor(sc), emissionColor(ec),
        transparency(transp), reflection(refl)
    {}
    //Use geometric solution to solve a ray-sphere intersection 
    bool intersect(const Vec_3f &rayorigin, const Vec_3f & raydirection, float &t0, float &t1) const
    {
        Vec_3f l = center - rayorigin;
        //Determine whether reverse direction 
        float tca = l.dot(raydirection);
        if  (tca < 0) return false;
        //a^2=b^2+c^2
        float dist = l.dot(l) - tca * tca;
        if (dist > radius2) return false;
        float thc = sqrt(radius2 - dist);
        //t0: first intersection distance, t1: second intersection distance
        t0 = tca - thc;
        t1 = tca + thc;

        return true;
    }
};

//Define the maximum recursion depth
#define MAX_DEPTH 5

//Calculate the mix value for reflection and refraction
float mix(const float &a, const float &b, const float &mix)
{
    return b * mix + a * (1 - mix);
}

//Ray Tracing Function: takes a ray (defined by its origin and direction) as argument.
//Through the function, we can know if the ray intersects any of the geometry in the scene.
//If the ray intersects an object, calculate the intersection point and its normal, then shade the point.
//Shading depends on the surface (transparent, reflective, diffuse)
//If the ray intersects an object, then return the color of the object at the intersection point, otherwise return the backgroud color.
Vec_3f trace(
    const Vec_3f &rayorigin,
    const Vec_3f &raydirection,
    const std::vector<Sphere> &spheres,
    const int &depth
    )
{
    float tnear= INFINITY;
    const Sphere* sphere=NULL;
    //calculate intersection of this ray with the sphere in the scene
    for(unsigned i=0; i < spheres.size(); i++)
    {
        float t0=INFINITY;
        float t1=INFINITY;
        if(spheres[i].intersect(rayorigin, raydirection, t0, t1))
        {
            //If the point in the sphere
            if(t0 < 0) t0= t1;
            if(t0 < tnear)
            {
                tnear = t0;
                sphere = &spheres[i];
            }
        }
    }
    //If there is no intersection, then return backgroud color
    if(!sphere) return Vec_3f(0);
    //Color of ray
    Vec_3f surfaceColor = 0;
    //point of intersect
    Vec_3f phit = rayorigin + raydirection * tnear;
    //normal of the intersection point 
    Vec_3f nhit = phit - sphere->center;
    //normalize the normal direction
    nhit.normal();
    //If the normal and the view direction's dot is positive, means the view point inside sphere
    float bias = 1e-4;
    bool inside = false;
    if(raydirection.dot(nhit) > 0)
    {
        nhit = -nhit;
        inside = true;
    }
    //Tackle with relection and refraction
    if((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_DEPTH)
    {
        //Compute fresnel effect
        float facingratio = - raydirection.dot(nhit);
        float fresneleffect = mix (pow(1 - facingratio, 3), 1, 0.1); 
        //Compute reflection direction
        Vec_3f reflect_direction = raydirection - nhit * 2 * raydirection.dot(nhit);
        reflect_direction.normal();
        Vec_3f next_reflection = trace(phit + nhit * bias, reflect_direction, spheres, depth + 1);
        //Vec_3f next_reflection = trace(phit, reflect_direction, spheres, depth + 1);
        Vec_3f next_refraction = 0;
        //Only if the sphere is transparent, then compute refraction ray
        if(sphere->transparency)
        {
            //judge whether we are inside or outside? ior is the index of two materials
            float ior = 1.1, eta = (inside) ? ior : 1 / ior;
            float cosi = -nhit.dot(raydirection);
            float k = 1 - eta * eta * (1 - cosi * cosi);
            Vec_3f refraction_direction = raydirection * eta + nhit * (eta * cosi - sqrt(k));
            refraction_direction.normal();
            next_refraction = trace(phit - nhit * bias, refraction_direction, spheres, depth+1); 
            //next_refraction = trace(phit, refraction_direction, spheres, depth+1);           
        }
        //The surface is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (next_reflection * fresneleffect + next_refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;      
    }
    //If it is a diffuse object, no need to ray tracing.
    else
    {
        for(unsigned i = 0; i < spheres.size(); i++)
        {
            //This is a light
            if(spheres[i].emissionColor.x > 0)
            {
                Vec_3f transmission = 1;
                Vec_3f lightDirection = spheres[i].center - phit;
                lightDirection.normal();
                //Check whether have an obstacle between light and object, add shadow
                for(unsigned j = 0; j < spheres.size(); ++j)
                {
                    if(i != j)
                    {
                        float t0, t1;
                        if(spheres[j].intersect(phit + nhit * bias, lightDirection, t0, t1))
                            //if(spheres[j].intersect(phit, lightDirection, t0, t1))
                        {
                            transmission = 0;
                            break;
                        }                        
                    }
                }                

                //If nhit and lightDirection's dot is less than 0, then no light.
                surfaceColor += sphere->surfaceColor * transmission * std::max(float(0), nhit.dot(lightDirection)) * spheres[i].emissionColor;
            }
        }
    }

    return surfaceColor + sphere->emissionColor;

}

//Render function, compute each pixel of the image.
void render(const std::vector<Sphere> &spheres)
{
    unsigned width = 640, height = 480;
    Vec_3f *img = new Vec_3f[width * height], *pixel = img;
    float invWidth = 1 / float(width), invHeight = 1 / float(height);
    float fov = 30;
    float aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);
    //Trace all ray
    for(unsigned y = 0; y < height; y++)
    {
        for(unsigned x = 0; x < width; x++, pixel++)
        {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vec_3f raydir(xx, yy, -1);
            raydir.normal();
            *pixel = trace(Vec_3f(0), raydir, spheres, 0);
        }
    }
    //Save the result
    std::ofstream ofs("./1.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for(unsigned i = 0; i < width * height; i++)
    {
        //0,255
        ofs << (unsigned char)(std::min(float(1), img[i].x) * 255) <<
            (unsigned char)(std::min(float(1), img[i].y) * 255) <<
            (unsigned char)(std::min(float(1), img[i].z) * 255);
    }
    ofs.close();
    delete [] img;
}

//Create a sign including 5 spheres and 1 light (which is also a sphere), then render it.
int main()
{
    std::vector<Sphere> spheres;
    //argument: position, radius, surfaceColor, reflectivity, transparency, emissionColor
    spheres.push_back(Sphere(Vec_3f( 0.0,      0, -20),     4, Vec_3f(1.00, 0.00, 0.00), 1, 0.5));
    spheres.push_back(Sphere(Vec_3f( 5.0,     -1, -15),     2, Vec_3f(0.00, 1.00, 0.00), 1, 0.0));
    spheres.push_back(Sphere(Vec_3f( 5.0,      0, -25),     3, Vec_3f(0.00, 0.00, 1.00), 1, 0.0));
    spheres.push_back(Sphere(Vec_3f(-5.5,      0, -15),     3, Vec_3f(0.00, 1.00, 0.00), 1, 0.0));
    //Light
    spheres.push_back(Sphere(Vec_3f(0.0, 20, -30), 3, Vec_3f(0.0, 0.0, 0.0), 0, 0.0, Vec_3f(3)));
    render(spheres);

    return 0;
}
