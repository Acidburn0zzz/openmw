#include "cellcoordinates.hpp"

#include <ostream>
#include <sstream>

CSMWorld::CellCoordinates::CellCoordinates() : mX (0), mY (0) {}

CSMWorld::CellCoordinates::CellCoordinates (int x, int y) : mX (x), mY (y) {}

int CSMWorld::CellCoordinates::getX() const
{
    return mX;
}

int CSMWorld::CellCoordinates::getY() const
{
    return mY;
}

CSMWorld::CellCoordinates CSMWorld::CellCoordinates::move (int x, int y) const
{
    return CellCoordinates (mX + x, mY + y);
}

std::string CSMWorld::CellCoordinates::getId (const std::string& worldspace) const
{
    // we ignore the worldspace for now, since there is only one (will change in 1.1)
    std::ostringstream stream;

    stream << "#" << mX << " " << mY;

    return stream.str();
}

std::pair<CSMWorld::CellCoordinates, bool> CSMWorld::CellCoordinates::fromId (
    const std::string& id)
{
    // no worldspace for now, needs to be changed for 1.1
    if (!id.empty() && id[0]=='#')
    {
        int x, y;
        char ignore;

        std::istringstream stream (id);
        if (stream >> ignore >> x >> y)
            return std::make_pair (CellCoordinates (x, y), true);
    }

    return std::make_pair (CellCoordinates(), false);
}

bool CSMWorld::operator== (const CellCoordinates& left, const CellCoordinates& right)
{
    return left.getX()==right.getX() && left.getY()==right.getY();
}

bool CSMWorld::operator!= (const CellCoordinates& left, const CellCoordinates& right)
{
    return !(left==right);
}

bool CSMWorld::operator< (const CellCoordinates& left, const CellCoordinates& right)
{
    if (left.getX()<right.getX())
        return true;

    if (left.getX()>right.getX())
        return false;

    return left.getY()<right.getY();
}

std::ostream& CSMWorld::operator<< (std::ostream& stream, const CellCoordinates& coordiantes)
{
    return stream << coordiantes.getX() << ", " << coordiantes.getY();
}
