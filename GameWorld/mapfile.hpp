#ifndef MAPFILE_HPP_INCLUDE
#define MAPFILE_HPP_INCLUDE

#include "GameUtil/filebase.hpp"

#include "map.hpp"
#include "mapwarp.hpp"

class MapFile : public FileBase
{
protected:
    void DoReadV1(Map* map);
    void DoWriteV1(Map* map);

    virtual std::string GetExtension() { return ".aomf"; }

public:
    MapFile();
    MapFile(std::string filename);
    virtual ~MapFile();

    void Read(Map* map);
    void Write(Map* map);
};
#endif // MAPFILE_HPP_INCLUDE
