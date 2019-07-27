#include "MercatorTile.h"
#include <iostream>
#include <deque>
#include <math.h>
#include <numeric>

using namespace std;
using namespace mercatortile;

using std::cout;
using std::endl;

void print(const std::string& input)
{
    cout << input[4] << endl;
}

int main(int argc, char const *argv[])
{

    print("1233445");
// ul
    cout<<"example - [ul] .........."<<endl;
    LngLat ul_result = ul(Tile{3425, 1549, 12});
    cout<<"lng: "<<ul_result.lng<<" lat:"<<ul_result.lat<<"\n"<<endl;

// xy
    // LngLat aa;
    // cout<<aa.lng<<endl;
    // float lng = 120;
    // float lat = 40;
    // float x;
    // float y;
    // mercatortile::xy(lng, lat, &x, &y);
    // std::cout<<x<<std::endl;
    // std::cout<<y<<std::endl;
// truncate_lonlat
    // float truct_lng = 120;
    // float truct_lat = 120;
    // mercatortile::truncate_lonlat(&truct_lng, &truct_lat);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;
// lonlat
    // float truct_lng = 120;
    // float truct_lat = 120;
    // // mercatortile::lonlat(&x, &y,);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;
// ul
    // // check function ul
    // mercatortile::Tile tile = {0,0,1};
    // mercatortile::LngLat lnglat = {0,0};
    // mercatortile::ul(tile, &lnglat);
    // cout<<lnglat.lng<<"  "<<lnglat.lat<<endl;
// bounds
    // check function bounds
    // mercatortile::Tile tile = {0,0,0};
    // mercatortile::LngLatBbox llbbox = {0,0};
    // mercatortile::bounds(tile, &llbbox);
    // cout<<llbbox.west<<"  "<<llbbox.south<<" "<< llbbox.east <<" "<<llbbox.north<<endl;
// parent
    // Tile tile {230,439,8};
    // Tile parent_tile = mercatortile::parent(tile, 4);
    // cout<<parent_tile.x<<endl;
    // cout<<parent_tile.y<<endl;
    // cout<<parent_tile.z<<endl;

// child - 1 level
    // cout<<"example - [child]: "<<endl;
    // Tile tile {230,439,8};
    // vector<Tile> child_tiles = mercatortile::child(tile);
    // for (const auto &child:child_tiles){
    //     cout<<child.x<<endl;
    //     cout<<child.y<<endl;
    //     cout<<child.z<<endl;
    //     cout<<endl;
    // };

// child - n level
    // cout<<"example - [child]: "<<endl;
    // Tile tile {1,1,5};
    // std::vector<Tile> child_tiles = mercatortile::child(tile, 18);
    // for (const auto &child:child_tiles){
    //     cout<<child.x<<endl;
    //     cout<<child.y<<endl;
    //     cout<<child.z<<endl;
    //     cout<<endl;
    // };

// tiles
    cout<<"example - [tiles] .........."<<endl;
    LngLatBbox bbox {121.0, 40.0, 121.1, 40.1};
    std::vector<Tile> child_tiles = mercatortile::tiles(bbox, 13);
    for (const auto &child:child_tiles){
        cout<<child.x<<endl;
        cout<<child.y<<endl;
        cout<<child.z<<endl;
        cout<<endl;
    };

// quadkey
    cout<<"example - [quadkey] .........."<<endl;
    string quad_key = mercatortile::quadkey(Tile{3425, 1549, 12});
    cout<<quad_key<<endl;

// quadkey_to_tile
    cout<<"example - [quadkey_to_tile] .........."<<endl;
    Tile quad_key_tile = mercatortile::quadkey_to_tile("132101102203");
    cout<<quad_key_tile.x<<" "<<quad_key_tile.y<<" "<<quad_key_tile.z<<endl;

    return 0;
};