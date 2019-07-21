#include "MercatorTile.h"
#include <math.h>
#include <iostream>
#include <vector>


using namespace std;
namespace mercatortile{

void truncate_lonlat(float *lng, float *lat)
{
    if (*lng > 180.0)
    {
        *lng = 180.0;
    }
    else if (*lng < -180.0)
    {
        *lng = -180.0;
    }

    if (*lat > 90.0)
    {
        *lat = 90.0;
    }
    else if (*lat < -90.0)
    {
        *lat = -90.0;
    }
    
};


void ul(const Tile & tile, LngLat *lonlat)
{
    float n = pow(2.0f, tile.z);
    float lat_rad = atan(sinh(M_PI * (1.0f - 2.0f * tile.y / n)));
    lonlat->lat = lat_rad * 180.0f / M_PI;
    lonlat->lng = tile.x / n * 360.0f - 180.0f;
};


// void bounds(const Tile & tile, LngLatBbox *llbbox)
// {
//     Tile tile_right
//     LngLat lnglat_ul;
//     LngLat lnglat_br;
//     ul(tile, lnglat_ul);
//     ul(tile, lnglat_br);
//     llbbox->west = lnglat_ul.lng;
//     llbbox->west = lnglat_ul.lng;
// };

void xy(const float &lng, const float &lat, float *x, float *y)
{
    *x = 6378137.0 * (M_PI*lng/180);
    if (lat <= -90)
    {
        *y = float(123);
    }
    else if (lat>=90)
    {
        *y = float(123);
    }
    else
    {
        *y = 6378137.0 * log(
            tan((M_PI*0.25) + (0.5* (M_PI*lat/180)))
            );
    };
};


void lnglat(const float &x, const float &y, float *lng, float *lat)
{
    float R2D = 180/M_PI;
    float A = 6378137.0;
    *lng = x*R2D/A;
    *lat = ((M_PI*0.5) - 2.0*atan(exp(-y/A))) * R2D;
};


} // namespace mercatortile


