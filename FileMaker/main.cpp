#include <iostream>
#include <string>
#include <sstream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "GameUtil/resourcefile.hpp"

std::list<Resource*> GetResourceList(std::string path, std::string extension, int num)
{
    std::list<Resource*> rlist;

    ALLEGRO_BITMAP* bitmap;

    for (int i = 0; i < num; i++)
    {
        std::stringstream ss;
        ss << path;

        if (i < 100) ss << "0";
        if (i < 10) ss << "0";
        ss << i << extension;

        std::cout << "Trying to open file: '" << ss.str() << "'" << std::endl;
        bitmap = al_load_bitmap(ss.str().c_str());
        if (bitmap)
        {
            uint32_t width = al_get_bitmap_width(bitmap);
            uint32_t height = al_get_bitmap_height(bitmap);

            Resource* resource = new Resource(width, height);
            Pixel pixel;

            al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

            for (uint32_t w = 0 ; w < width; w++)
            {
                for (uint32_t h = 0; h < height; h++)
                {
                    // RGBA for these are returned as floats from 0~1
                    ALLEGRO_COLOR p = al_get_pixel(bitmap, w, h);
                    pixel.r = 255 * p.r;
                    pixel.g = 255 * p.g;
                    pixel.b = 255 * p.b;
                    pixel.a = 255 * p.a;

                    resource->SetPixel(w, h, pixel);
                }
            }

            rlist.push_back(resource);
            std::cout << "\t" << "Bitmap loaded. Adding to resource list." << std::endl;

            al_unlock_bitmap(bitmap);
            al_destroy_bitmap(bitmap);
        }
    }

    return rlist;
}

void CreateResourceFile(int id, std::string path, std::string extension, int num)
{
    std::cout << std::endl << std::endl;

    std::stringstream ss;
    ss << "resource";
    if (id < 10) ss << 0;
    ss << id;

    ResourceFile rfile;
    std::list<Resource*> rlist;

    rlist = GetResourceList(path, extension, num);
    rfile.Create(ss.str());
    rfile.Write(rlist);
    rfile.Close();
}

int main(int argc, char** argv)
{
    if (!al_init()) return -1;
    al_init_image_addon();

    ResourceFile rfile;
    std::list<Resource*> rlist;

    std::string basepath;
    //basepath = "B:/AdventureOnline/AO-Resource/image/";
    basepath = "C:/Users/Jacob/Documents/GitHub/AO-Resource/image/";

    CreateResourceFile(0, basepath + "background/", ".png", 1);
    CreateResourceFile(1, basepath + "tile/", ".png", 13);
    CreateResourceFile(2, basepath + "character/", ".png", 3);

    return 0;
}
