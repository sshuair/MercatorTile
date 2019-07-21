#include "MercatorTile.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace mercatortile;

using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    float n = pow(2,3);
    std::cout<<n<<endl;

    LngLat aa;
    cout<<aa.lng<<endl;
    // 
    // float lng = 120;
    // float lat = 40;
    // float x;
    // float y;
    // mercatortile::xy(lng, lat, &x, &y);
    // std::cout<<x<<std::endl;
    // std::cout<<y<<std::endl;

    // float truct_lng = 120;
    // float truct_lat = 120;
    // mercatortile::truncate_lonlat(&truct_lng, &truct_lat);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;

    // float truct_lng = 120;
    // float truct_lat = 120;
    // // mercatortile::lonlat(&x, &y,);
    // std::cout<<truct_lng<<std::endl;
    // std::cout<<truct_lat<<std::endl;

    // check function ul
    mercatortile::Tile tile = {1,1,0};
    mercatortile::LngLat lnglat = {0,0};
    mercatortile::ul(tile, &lnglat);
    cout<<lnglat.lng<<"  "<<lnglat.lat<<endl;



    return 0;
};