#include "MercatorTile.h"
#include <iostream>
#include <deque>
#include <math.h>
#include <numeric>

using namespace std;
using namespace mercatortile;

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{

    cout.setf(ios::right); 
    cout.width(8); 
    cout.flags(ios::fixed);
    cout.precision(12); 

    Tile stile{3425, 1549, 12};
    double lng = 120.0;
    double lat = 40.032;
    double x = 13358338.895192828;
    double y = 4870593.5225044815;
    LngLatBbox bbox{121.0, 40.0, 121.1, 40.1};
    string qk = "132101102203";

    // ul
    cout << "example - [ul] .........." << endl;
    LngLat uplt = ul(stile);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} up left lng lat is: " \
    << uplt.lng << " " << uplt.lat << endl;

    // bounds
    cout << "\nexample - [bounds] .........." << endl;
    LngLatBbox llbbox = bounds(stile);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} bounds is: " \
    << llbbox.west << " " << llbbox.south << " " << llbbox.east << " " << llbbox.north << endl;

    // xy
    cout << "\nexample - [xy] .........." << endl;
    XY rxy = xy(lng, lat);
    cout<<"the web mercator coord of "<<lng<<" "<<lat<<" is "<<rxy.x<<" "<<rxy.y<<endl;

    // lonlat: Convert  web mercator x, y to longtitude and latitude.
    cout << "\nexample - [lnglat] .........." << endl;
    LngLat rlnglat = lnglat(x,y);
    cout<<"the geographic coord of "<<x<<" "<<y<<" is "<<rlnglat.lng<<" "<<rlnglat.lat<<endl;


    // xy_bounds: Get the web mercator bounding box of a tile
    cout << "\nexample - [xy_bounds] .........." << endl;
    Bbox rbbox = xy_bounds(stile);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} xy bounds is: " \
    << rbbox.left << " " << rbbox.bottom << " " << rbbox.right << " " << rbbox.top << endl;

    // tile
    cout << "\nexample - [tile] .........." << endl;
    Tile ttile = tile(lng, lat, 4);
    cout<<"the lng lat "<<lng<<" "<<lat<<" at zoom 4 tile is "<<ttile.x<<" "<<ttile.y<<" "<<ttile.z<<endl;

    // tiles
    cout << "\nexample - [tiles] .........." << endl;
    std::vector<Tile> contained_tiles = mercatortile::tiles(bbox, 13);
    cout<<"the 13 zoom level of bbox {"<<bbox.west<< " "<<bbox.south<< " "<<bbox.east<< " "<<bbox.north<<"} contained tiles is: "<<endl;
    for (const auto &child : contained_tiles)
    {
        cout << child.x << " "<< child.y<< " " <<child.z<<endl;
    };

    // parent - 1 level
    cout << "\nexample - [parent] 1 level .........." << endl;
    Tile parent_tile = mercatortile::parent(stile);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} parent tile is: " \
    << parent_tile.x << " " << parent_tile.y << " " << parent_tile.z <<endl;

    // parent - n upper level
    cout << "\nexample - [parent] upper n level .........." << endl;
    Tile parent2_tile = mercatortile::parent(stile, 4);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} at parent zoom 4 tile is: " \
    << parent2_tile.x << " " << parent2_tile.y << " " << parent2_tile.z <<endl;

    // children - 1 level
    cout << "\nexample - [child] 1 level: " << endl;
    vector<Tile> child_tiles = mercatortile::children(stile);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} children tile is: "<<endl;
    for (const auto &child : child_tiles)
    {
        cout << child.x << " "<< child.y<< " " <<child.z<<endl;
    };

    // children - n level
    cout << "\nexample - [child] n level: " << endl;
    std::vector<Tile> child2_tiles = mercatortile::children(stile, 14);
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} at parent zoom 14 tile is: "<<endl;
    for (const auto &child : child2_tiles)
    {
        cout << child.x << " "<< child.y<< " " <<child.z<<endl;
    };

    // quadkey
    cout << "\nexample - [quadkey] .........." << endl;
    string quad_key = mercatortile::quadkey(Tile{3425, 1549, 12});
    cout << "the tile {" << stile.x << " " << stile.y << " " << stile.z << "} quadkey is: "<<endl;
    cout << quad_key << endl;

    // quadkey_to_tile
    cout << "\nexample - [quadkey_to_tile] .........." << endl;
    Tile quad_key_tile = mercatortile::quadkey_to_tile(qk);
    cout << "quadkey {" << qk << "} corresponding tile is: "<<endl;
    cout << quad_key_tile.x << " " << quad_key_tile.y << " " << quad_key_tile.z << endl;

    // truncate_lonlat
    double trunc_lng = 190.5;
    double trunc_lat = -93.2;
    truncate_lonlat(&trunc_lng, &trunc_lat);
    cout<<"the input out bounds lng lat "<< trunc_lng<< " "<< trunc_lat<< " trucated result is" <<endl;
    cout<<trunc_lng<< " " <<trunc_lat<<endl;

    return 0;
};