#include "Mesh.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include "Vector.h"
#include "Triangle.h"


Mesh::Mesh(const Vec3f &surfaceColor, const Vec3f &emissionColor, const float transparency, const float reflection)
    :GeometryUnion(surfaceColor, emissionColor, transparency, reflection)
{
}


// 切割字符串
std::vector<std::string> stringSplit(const std::string &string, const std::string &separator)
{
    std::string str(string);  // 待切割字符串的拷贝
    std::vector<std::string> strList;  // 存放分割后的字符串
    int separatorPosition = 0;
    while(true)
    {
        std::string strTemp;
        separatorPosition = str.find(separator);
        if(separatorPosition == -1)
        {
            strTemp = str.substr(0, str.length());
            strList.push_back(strTemp);
            break;
        }
        strTemp = str.substr(0, separatorPosition);
        str.erase(0, separatorPosition + 1);
        if (strTemp.length() > 0)
        {
            strList.push_back(strTemp);
        }
    }

    return strList;
}


int Mesh::loadObj(const std::string filename)
{
    std::vector<Vec3f> vertices;
    std::vector<Vec3i> faces;
    // 模型的包围盒
    Vec3f boundingBoxOrigin;
    Vec3f boundingBoxSize;
    // 模型的包围球
    Vec3f boundingSphereCenter;
    float boundingSphereRadius;

    // 打开obj文件
    std::ifstream in(filename);
    if(!in.is_open())
    {
        std::cout << "ERROR: Failed to open obj file:(" << filename << ")" << std::endl;
        return -1;
    }

    // 逐行读取顶点或三角面片信息
    std::string bufferLine;
    while(!in.eof())
    {
        std::getline(in, bufferLine);
        std::vector<std::string> bufferLineSplit = stringSplit(bufferLine, " ");

        if (bufferLineSplit[0] == "v")  // 顶点
        {
            if (bufferLineSplit.size() != 4)
            {
                std::cout << "ERROR: Vertex not in wanted format in obj file." << std::endl;
                return -1;
            }
            vertices.push_back(Vec3f(atof(bufferLineSplit[1].c_str()), atof(bufferLineSplit[2].c_str()), atof(bufferLineSplit[3].c_str())));
        }
        else if (bufferLineSplit[0] == "f")  // 三角面片
        {
            if (bufferLineSplit.size() != 4)
            {
                std::cout << "ERROR: Face not in wanted format in obj file." << std::endl;
                return -1;
            }
            Vec3i face;
            for (unsigned i = 0; i < 3; i++)
            {
                face.val[i] = atoi(stringSplit(bufferLineSplit[i + 1], "/")[0].c_str());
            }
            faces.push_back(face);
        }
    }

    // 将所有三角面片加入_geometries
    for (unsigned i = 0; i < faces.size(); i++)
    {
        unsigned vertexIndices[3];
        for (unsigned j = 0; j < 3; j++)
        {
            vertexIndices[j] = faces[i].val[j] - 1;
        }
        addGeometry(new Triangle(Vec3f(vertices[vertexIndices[0]].x, vertices[vertexIndices[0]].y, vertices[vertexIndices[0]].z), Vec3f(vertices[vertexIndices[1]].x, vertices[vertexIndices[1]].y, vertices[vertexIndices[1]].z), Vec3f(vertices[vertexIndices[2]].x, vertices[vertexIndices[2]].y, vertices[vertexIndices[2]].z)));
    }

    float xmin, ymin, zmin, xmax, ymax, zmax;
    int Pxmin, Pxmax, Pymin, Pymax, Pzmin, Pzmax;

    // calculate the bounding sphere
    xmin = xmax = vertices[0].x;
    ymin = ymax = vertices[0].y;
    zmin = zmax = vertices[0].z;
    Pxmin = Pxmax = Pymin = Pymax = Pzmin = Pzmax = 0;

    // calculate the bounding box
    boundingBoxOrigin = Vec3f(vertices[0].x, vertices[0].y, vertices[0].z);
    boundingBoxSize = Vec3f(vertices[0].x, vertices[0].y, vertices[0].z);

    for(unsigned i = 1; i < vertices.size(); i++)
    {
        // update min value
        boundingBoxOrigin.x = std::min(vertices[i].x, boundingBoxOrigin.x);
        boundingBoxOrigin.y = std::min(vertices[i].y, boundingBoxOrigin.y);
        boundingBoxOrigin.z = std::min(vertices[i].z, boundingBoxOrigin.z);

        // update max value
        boundingBoxSize.x = std::max(vertices[i].x, boundingBoxSize.x);
        boundingBoxSize.y = std::max(vertices[i].y, boundingBoxSize.y);
        boundingBoxSize.z = std::max(vertices[i].z, boundingBoxSize.z);

        // update the  x min and max
        if (vertices[i].x < xmin)
        {
            xmin = vertices[i].x;
            Pxmin = i;
        }
        else if(vertices[i].x > xmax)
        {
            xmax = vertices[i].x;
            Pxmax = i;
        }
        // update the y min and max
        if (vertices[i].y < ymin)
        {
            ymin = vertices[i].y;
            Pymin = i;
        }
        else if(vertices[i].y > ymax)
        {
            ymax = vertices[i].y;
            Pymax = i;
        }
        // update the z min and max
        if(vertices[i].z < zmin)
        {
            zmin = vertices[i].z;
            Pzmin = i;
        }
        else if(vertices[i].z > zmax)
        {
            zmax = vertices[i].z;
            Pzmax = i;
        }
    }

    // calculate the bounding sphere
    Vec3f dVx = vertices[Pxmax] - vertices[Pxmin];
    Vec3f dVy = vertices[Pymax] - vertices[Pymin];
    Vec3f dVz = vertices[Pzmax] - vertices[Pzmin];
    float dx2 = dVx.length2();
    float dy2 = dVy.length2();
    float dz2 = dVz.length2();

    Vec3f center;
    float radius2;
    float radius;

    if (dx2 >= dy2 && dx2>=dz2)  // x direction is largest extent
    {
        center = vertices[Pxmin] + (dVx * 0.5);  // Center = midpoint of extremes
        radius2 = (vertices[Pxmax] - center).length2();  // radius squared
    }
    else if (dy2 >= dx2  && dy2>=dz2)  // y direction is largest extent
    {
        center = vertices[Pymin] + (dVy * 0.5);  // Center = midpoint of extremes
        radius2 = (vertices[Pymax] - center).length2();  // radius squared
    }
    else
    {
        center = vertices[Pzmin] + (dVz * 0.5);  // Center = midpoint of extremes
        radius2 = (vertices[Pzmax] - center).length2();  // radius squared
    }

    radius = sqrt(radius2);

    // now check that all points V[i] are in the ball
    // and if not, expand the ball just enough to include them
    Vec3f dV;
    float dist2,dist;
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        dV = vertices[i] - center;
        dist2 = dV.length2();
        if (dist2 <= radius2)  // V[i] is inside the ball already
        {
            continue;
        }

        // V[i] not in ball, so expand ball to include it
        dist = sqrt(dist2);
        radius = (radius + dist) / 2.0;  // enlarge radius just enough
        radius2 = radius * radius;
        center = center + dV * ((dist-radius)/dist);  // shift Center toward V[i]
    }

    boundingSphereCenter = center;
    boundingSphereRadius = radius;

    std::cout << "----------obj file loaded-------------" << std::endl;
    std::cout << "number of faces:" << faces.size() << std::endl;
    std::cout << "number of vertices:" << vertices.size() << std::endl;
    std::cout << "obj bounding box: min:("
        << boundingBoxOrigin.x << "," << boundingBoxOrigin.y << "," << boundingBoxOrigin.z << ") max:("
        << boundingBoxSize.x << "," << boundingBoxSize.y << "," << boundingBoxSize.z << ")" << std::endl
        << "obj bounding sphere center:" << boundingSphereCenter.x << "," << boundingSphereCenter.y << "," << boundingSphereCenter.z << std::endl
        << "obj bounding sphere radius:" << boundingSphereRadius << std::endl;

    return 0;
}
