#ifndef _GLOBJECT_H_
#define _GLOBJECT_H_

class glObject{
    public:
        glObject();
        virtual ~glObject();
    private:
        bool generateMeshObject();
    
    /*
        struct vec3d{
            float x, y, z;
        };
        struct triangle{
            vec3d p[3];
        };
        struct mesh{
            // this tells the code that the float vec3d in triangle are vertices (parsing vector template)
            std::vector<triangle> tris;
        };
    */
};

#endif 