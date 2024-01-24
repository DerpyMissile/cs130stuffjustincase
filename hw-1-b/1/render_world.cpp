#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool enable_acceleration;

Render_World::~Render_World()
{
    for(auto a:all_objects) delete a;
    for(auto a:all_shaders) delete a;
    for(auto a:all_colors) delete a;
    for(auto a:lights) delete a;
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
std::pair<Shaded_Object,Hit> Render_World::Closest_Intersection(const Ray& ray) const
{
    TODO;
    Shaded_Object obj;
    Hit finalHit;
    finalHit.dist = 99999;
    for(Shaded_Object s : objects){
        Hit tempHit = s.object->Intersection(ray, -1);
        if(tempHit.dist < finalHit.dist){
            finalHit.dist = tempHit.dist;
            obj = s;
        }
        delete s.object;
    }
    return {obj, finalHit};
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    vec3 direc = camera.World_Position(pixel_index) - camera.position;
    direc = direc.normalized();
    Ray ray(camera.position, direc);
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
    Debug_Scope scope; 
    Pixel_Print("cast ray ",ray);
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth) const
{
    vec3 color;
    //TODO; // determine the color here
    // std::pair<Shaded_Object,Hit> objectHit = Closest_Intersection(ray);
    // if(objectHit.second.dist < 0){
    //     color = background_shader->Shade_Surface(*this, ray, objectHit.second, ray.Point(objectHit.second.dist), objectHit.first.object->Normal(ray, objectHit.second), recursion_depth);
    //     delete objectHit.first.object;
    //     delete background_shader;
    // }else{
    //     color = objectHit.first.shader->Shade_Surface(*this, ray, objectHit.second, ray.Point(objectHit.second.dist), objectHit.first.object->Normal(ray, objectHit.second), recursion_depth);
    //     delete objectHit.first.object;
    //     delete objectHit.first.shader;
    // }
    return color;
}
