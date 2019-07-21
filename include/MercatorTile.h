#ifndef __MERCANTILE_H_
#define __MERCANTILE_H_

namespace mercatortile{


// An XYZ web mercator tile
struct Tile
{
    int x;
    int y;
    int z;
};

// A longitude and latitude pair
struct LngLat
{
    float lng;
    float lat;
};

// A geographic bounding box
struct LngLatBbox
{
    float west;
    float south;
    float east;
    float north;
};

// A web mercator bounding box
struct Bbox
{
    float left;
    float bottom;
    float right;
    float top;
};



void truncate_lonlat(float *lng, float *lat);

// Returns the upper left longitude and latitude of a tile
void ul(const Tile &tile, LngLat *lonlat);

void bounds(const Tile &tile, LngLatBbox *llbbox);

// Convert longtitude and latitude to web mercator x, y.
void xy(const float &lng, const float &lat, float *x, float *y);

// Convert  web mercator x, y to longtitude and latitude.
void lonlat(const float &x, const float &y, float *lng, float *lat);



} //namespace mercatortile
#endif // !__MERCANTILE_H_
