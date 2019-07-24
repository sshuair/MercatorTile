#include "MercatorTile.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <deque>
#include <string>


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


LngLat ul(const Tile &tile)
{
    LngLat lonlat;
    float n = pow(2.0f, tile.z);
    float lat_rad = atan(sinh(M_PI * (1.0f - 2.0f * tile.y / n)));
    lonlat.lat = lat_rad * 180.0f / M_PI;
    lonlat.lng = tile.x / n * 360.0f - 180.0f;
    
    return lonlat;
};


LngLatBbox bounds(const Tile &tile)
{
    LngLatBbox bound;
    Tile tile_br = {tile.x+1, tile.y+1, tile.z};
    LngLat lnglat_ul = ul(tile);
    LngLat lnglat_br = ul(tile_br);
    bound.west = lnglat_ul.lng;
    bound.south = lnglat_br.lat;
    bound.east = lnglat_br.lng;
    bound.north = lnglat_ul.lat;

    return bound;
};


XY xy(const float &lng, const float &lat)
{
    XY out;
    out.x = 6378137.0 * (M_PI*lng/180);
    if (lat <= -90)
    {
        out.y = float(123);
    }
    else if (lat>=90)
    {
        out.y = float(123);
    }
    else
    {
        out.y = 6378137.0 * log(
            tan((M_PI*0.25) + (0.5* (M_PI*lat/180)))
            );
    };
    return out;
};


Bbox xy_bounds(const Tile &tile)
{
    Bbox bbox;

    LngLat lnglat_ul = ul(tile);
    bbox.left = lnglat_ul.lng;
    bbox.top = lnglat_ul.lat;

    Tile tile_br = {tile.x+1, tile.y+1, tile.z};
    LngLat lnglat_br = ul(tile_br);
    bbox.right = lnglat_br.lng;
    bbox.bottom = lnglat_br.lat;

    return bbox;
};


LngLat lnglat(const float &x, const float &y)
{
    LngLat out;
    float R2D = 180/M_PI;
    float A = 6378137.0;
    out.lng = x*R2D/A;
    out.lat = ((M_PI*0.5) - 2.0*atan(exp(-y/A))) * R2D;

    return out;
};


Tile tile(const float &lng, const float &lat, const int &zoom)
{
    Tile out_tile;
    out_tile.x = int(floor((lng+180.0) / 360.0 * pow(2.0, zoom)));

    float lat_ = M_PI*lat/180;
    out_tile.y = int(floor(
            (1.0 - log(
                tan(lat_) + (1.0/cos(lat_))
                )/M_PI
            )/2.0 * pow(2.0, zoom)
    ));
    out_tile.z = zoom;

    return out_tile;
};

Tile parent(const Tile &tile)
{
    Tile return_tile;
    if (tile.x % 2 == 0 && tile.y % 2 == 0)
    {
        return_tile = Tile {tile.x/2, tile.y/2, tile.z - 1};
    }
    else if (tile.x % 2 == 0)
    {
        return_tile = Tile {tile.x/2, (tile.y-1)/2, tile.z - 1};
    }
    else if (!(tile.x % 2 ==0) && (tile.y % 2 == 0))
    {
        return_tile = Tile {(tile.x-1)/2, tile.y/2, tile.z - 1};
    }
    else
    {
        return_tile = Tile {(tile.x-1)/2, (tile.y-1)/2, tile.z - 1};
    }

    return return_tile;
};

Tile parent(const Tile &tile, const int &zoom)
{
    if (tile.z < zoom)
    {
        throw "zoom should be less than tile zoom level.";
    }
    Tile return_tile = tile;
    while (return_tile.z > zoom)
    {
        if (return_tile.x % 2 == 0 && return_tile.y % 2 == 0)
        {
            return_tile = Tile {return_tile.x/2, return_tile.y/2, return_tile.z-1};
        }
        else if (return_tile.x % 2 == 0)
        {
            return_tile = Tile {return_tile.x/2, (return_tile.y-1)/2, return_tile.z-1};
        }
        else if (!(return_tile.x % 2 ==0) && (return_tile.y % 2 == 0))
        {
            return_tile = Tile {(return_tile.x-1)/2, return_tile.y/2, return_tile.z-1};
        }
        else
        {
            return_tile = Tile {(return_tile.x-1)/2, (return_tile.y-1)/2, return_tile.z-1};
        }
    }

    return return_tile;
    
};

vector<Tile> child(const Tile &tile)
{
    vector<Tile> return_tiles;
    return_tiles.push_back(Tile {tile.x * 2, tile.y * 2, tile.z+1});
    return_tiles.push_back(Tile {tile.x * 2 + 1 , tile.y * 2, tile.z+1});
    return_tiles.push_back(Tile {tile.x * 2, tile.y * 2 + 1, tile.z+1});
    return_tiles.push_back(Tile {tile.x * 2 + 1, tile.y * 2 + 1, tile.z+1});
    
    return return_tiles;
};

std::vector<Tile> child(const Tile &tile, const int &zoom)
{
    if (tile.z > zoom)
    {
        throw "zoom should be greater than tile zoom level.";
    };
    std::deque<Tile> return_tiles = {tile};
    while (return_tiles.front().z < zoom)
    {
        Tile front_tile = return_tiles.front();
        return_tiles.pop_front();
        return_tiles.push_back(Tile {front_tile.x * 2, front_tile.y * 2, front_tile.z+1});
        return_tiles.push_back(Tile {front_tile.x * 2 + 1 , front_tile.y * 2, front_tile.z+1});
        return_tiles.push_back(Tile {front_tile.x * 2, front_tile.y * 2 + 1, front_tile.z+1});
        return_tiles.push_back(Tile {front_tile.x * 2 + 1, front_tile.y * 2 + 1, front_tile.z+1});
    }

    //TODO: hight memory, not efficiency, or consider anthoer method.
    vector<Tile> return_vector_tiles(std::make_move_iterator(return_tiles.begin()),
                                     std::make_move_iterator(return_tiles.end()));
    // copy(return_tiles.begin(), return_tiles.end(), back_inserter(return_vector_tiles)); 

    return return_vector_tiles;
};


std::vector<Tile> tiles(const Bbox &bbox, const int &zoom)
{

};


string quadkey(const Tile &tile)
{
    return string("a");
};

} // namespace mercatortile


