#include "MercatorTile.h"
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <numeric>

using namespace std;
namespace mercatortile
{

void truncate_lonlat(double *lng, double *lat)
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
    double n = pow(2.0, tile.z);
    double lat_rad = atan(sinh(M_PI * (1.0 - 2.0 * tile.y / n)));
    lonlat.lat = lat_rad * 180.0 / M_PI;
    lonlat.lng = tile.x / n * 360.0 - 180.0;

    return lonlat;
};

LngLatBbox bounds(const Tile &tile)
{
    LngLatBbox bound;
    LngLat lnglat_ul = ul(tile);
    bound.west = lnglat_ul.lng;
    bound.north = lnglat_ul.lat;
    
    Tile tile_br = {tile.x + 1, tile.y + 1, tile.z};
    LngLat lnglat_br = ul(tile_br);
    bound.south = lnglat_br.lat;
    bound.east = lnglat_br.lng;

    return bound;
};

XY xy(const double &lng, const double &lat)
{
    XY out;
    out.x = 6378137.0 * (M_PI * lng / 180);
    if (lat <= -90)
    {
        out.y = double(123);
    }
    else if (lat >= 90)
    {
        out.y = double(123);
    }
    else
    {
        out.y = 6378137.0 * log(tan((M_PI * 0.25) + (0.5 * (M_PI * lat / 180))));
    };
    return out;
};

Bbox xy_bounds(const Tile &tile)
{
    Bbox bbox;

    LngLat lnglat_ul = ul(tile);
    XY xy_ul = xy(lnglat_ul.lng, lnglat_ul.lat);
    bbox.left = xy_ul.x;
    bbox.top = xy_ul.y;

    Tile tile_br = {tile.x + 1, tile.y + 1, tile.z};
    LngLat lnglat_br = ul(tile_br);
    XY xy_br = xy(lnglat_br.lng, lnglat_br.lat);
    bbox.right = xy_br.x;
    bbox.bottom = xy_br.y;

    return bbox;
};

LngLat lnglat(const double &x, const double &y)
{
    LngLat out;
    double R2D = 180 / M_PI;
    double A = 6378137.0;
    out.lng = x * R2D / A;
    out.lat = ((M_PI * 0.5) - 2.0 * atan(exp(-y / A))) * R2D;

    return out;
};

Tile tile(const double &lng, const double &lat, const int &zoom)
{
    Tile out_tile;
    out_tile.x = int(floor((lng + 180.0) / 360.0 * pow(2.0, zoom)));

    double lat_ = M_PI * lat / 180;
    out_tile.y = int(floor(
        (1.0 - log(
                   tan(lat_) + (1.0 / cos(lat_))) /
                   M_PI) /
        2.0 * pow(2.0, zoom)));
    out_tile.z = zoom;

    return out_tile;
};

Tile parent(const Tile &tile)
{
    Tile return_tile;
    if (tile.x % 2 == 0 && tile.y % 2 == 0)
    {
        return_tile = Tile{tile.x / 2, tile.y / 2, tile.z - 1};
    }
    else if (tile.x % 2 == 0)
    {
        return_tile = Tile{tile.x / 2, (tile.y - 1) / 2, tile.z - 1};
    }
    else if (!(tile.x % 2 == 0) && (tile.y % 2 == 0))
    {
        return_tile = Tile{(tile.x - 1) / 2, tile.y / 2, tile.z - 1};
    }
    else
    {
        return_tile = Tile{(tile.x - 1) / 2, (tile.y - 1) / 2, tile.z - 1};
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
            return_tile = Tile{return_tile.x / 2, return_tile.y / 2, return_tile.z - 1};
        }
        else if (return_tile.x % 2 == 0)
        {
            return_tile = Tile{return_tile.x / 2, (return_tile.y - 1) / 2, return_tile.z - 1};
        }
        else if (!(return_tile.x % 2 == 0) && (return_tile.y % 2 == 0))
        {
            return_tile = Tile{(return_tile.x - 1) / 2, return_tile.y / 2, return_tile.z - 1};
        }
        else
        {
            return_tile = Tile{(return_tile.x - 1) / 2, (return_tile.y - 1) / 2, return_tile.z - 1};
        }
    }

    return return_tile;
};

vector<Tile> children(const Tile &tile)
{
    vector<Tile> return_tiles;
    return_tiles.push_back(Tile{tile.x * 2, tile.y * 2, tile.z + 1});
    return_tiles.push_back(Tile{tile.x * 2 + 1, tile.y * 2, tile.z + 1});
    return_tiles.push_back(Tile{tile.x * 2, tile.y * 2 + 1, tile.z + 1});
    return_tiles.push_back(Tile{tile.x * 2 + 1, tile.y * 2 + 1, tile.z + 1});

    return return_tiles;
};

std::vector<Tile> children(const Tile &tile, const int &zoom)
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
        return_tiles.push_back(Tile{front_tile.x * 2, front_tile.y * 2, front_tile.z + 1});
        return_tiles.push_back(Tile{front_tile.x * 2 + 1, front_tile.y * 2, front_tile.z + 1});
        return_tiles.push_back(Tile{front_tile.x * 2, front_tile.y * 2 + 1, front_tile.z + 1});
        return_tiles.push_back(Tile{front_tile.x * 2 + 1, front_tile.y * 2 + 1, front_tile.z + 1});
    }

    //TODO: hight memory, not efficiency, or consider anthoer method.
    vector<Tile> return_vector_tiles(std::make_move_iterator(return_tiles.begin()),
                                     std::make_move_iterator(return_tiles.end()));
    // copy(return_tiles.begin(), return_tiles.end(), back_inserter(return_vector_tiles));

    return return_vector_tiles;
};

std::vector<Tile> tiles(const LngLatBbox &llbbox, const int &zoom)
{
    vector<LngLatBbox> bboxes;
    if (llbbox.west > llbbox.east)
    {
        bboxes.push_back(LngLatBbox{-180.0, llbbox.south, llbbox.east, llbbox.north});
        bboxes.push_back(LngLatBbox{llbbox.west, llbbox.south, 180.0, llbbox.north});
    }
    else
    {
        bboxes.push_back(llbbox);
    }

    vector<Tile> return_tiles;
    for (auto bbox : bboxes)
    {
        double w = max(-180.0, bbox.west);
        double s = max(-85.051129, bbox.south);
        double e = min(180.0, bbox.east);
        double n = min(85.051129, bbox.north);

        Tile ll = tile(w, s, zoom);
        Tile ur = tile(e, n, zoom);

        // Clamp left x and top y at 0.
        int llx = (ll.x < 0) ? 0 : ll.x;
        int ury = (ur.y < 0) ? 0 : ur.y;

        std::vector<int> x(min(ur.x + 1, int(pow(2, zoom))) - llx);
        std::iota(std::begin(x), std::end(x), llx);
        std::vector<int> y(min(ll.y + 1, int(pow(2, zoom))) - ury);
        std::iota(std::begin(y), std::end(y), ury);

        for (auto i : x)
        {
            for (auto j : y)
            {
                return_tiles.push_back(Tile{i, j, zoom});
            }
        }
    }
    return return_tiles;
};

string quadkey(const Tile &tile)
{
    string qk;
    for (int z=tile.z; z>0; z--)
    {
        int digit = 0;
        int mask = 1 << (z-1);
        if ((tile.x & mask) != 0)
        {
            digit++;
        }
        if ((tile.y & mask) != 0)
        {
            digit++;
            digit++;
        }
        qk.append(std::to_string(digit));
    }

    return qk;
};


Tile quadkey_to_tile(const std::string &qk)
{
    int zoom = qk.length();
    if (zoom == 0)
    {
        return Tile{0,0,0};
    } 
    int xtile = 0;
    int ytile = 0;
    for (int i = zoom; i>0; i--)
    {
        int mask = 1 << (zoom-i);
        int digit = qk[i-1]-'0';
        switch (digit)
        {
            
            case 0:
                break;
            case 1:
                xtile = xtile | mask;
                break;
            case 2:
                ytile = ytile | mask;
                break;
            case 3:
                xtile = xtile | mask;
                ytile = ytile | mask;
                break;
            default:
                throw "Unexpected quadkey digit.";
                break;
        }
    }
    
    return Tile{xtile, ytile, zoom};
}

} // namespace mercatortile
