#include "camera.h"

Camera::Camera()
    :colors(0)
{
}

Camera::~Camera()
{
    delete[] colors;
}

void Camera::Position_And_Aim_Camera(const vec3& position_input,
    const vec3& look_at_point,const vec3& pseudo_up_vector)
{
    position=position_input;
    look_vector=(look_at_point-position).normalized();
    horizontal_vector=cross(look_vector,pseudo_up_vector).normalized();
    vertical_vector=cross(horizontal_vector,look_vector).normalized();
}

void Camera::Focus_Camera(double focal_distance,double aspect_ratio,
    double field_of_view)
{
    film_position=position+look_vector*focal_distance;
    double width=2.0*focal_distance*tan(.5*field_of_view);
    double height=width/aspect_ratio;
    image_size=vec2(width,height);
}

void Camera::Set_Resolution(const ivec2& number_pixels_input)
{
    number_pixels=number_pixels_input;
    delete[] colors;
    colors=new Pixel[number_pixels[0]*number_pixels[1]];
    min=-0.5*image_size;
    max=0.5*image_size;
    pixel_size = image_size/vec2(number_pixels);
}

// Find the world position of the input pixel
vec3 Camera::World_Position(const ivec2& pixel_index)
{
    vec3 result;
    //TODO;
    //TA office hour notes
    /*
    we have to start with main
    from a general view, need to implement render_pixel
        which is in render world
        did that
    gonna use that file a lot more    
    render pixel is directly related to written assignment
    takes a ray, takes index of pixel, and creates a ray from camera to that ray
    passes that ray (gets the color of it) casts ray from camera to pixel and sets the color for that pixel in output.png
    what we have is our input (index i and j)
    we need to find a ray from the camera to that position
        so we need to find position of camera
        find position of pixel
        define the ray
    i have almost all of these
    just need to find the position of pixel
    oh yeah and debug pixel
    -t files are debug info (like 00-t.txt)

    ok its starting to make sense
    so what cell center is is that it basically tells us where it is in 2d
    i got this
    film position is p
    */
    result = film_position;
    vec2 tempVec = Cell_Center(pixel_index);
    result += horizontal_vector * (tempVec[0]);
    result += vertical_vector * (tempVec[1]);
    return result;
}
