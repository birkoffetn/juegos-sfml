#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__

#include <vector>
#include <string>

struct Point
{
    int row, col;
    Point operator+(Point other)
    {
        return {row + other.row, col + other.col};
    }
};

const char ENDPOINT = '.', MANENDPOINT = '+', BOXENDPOINT = '*';
const char WALL = '#', EMPTY = ' ', MAN = '@', BOX = '$';

class Level
{
public:
    enum Direction
    {
        Up,
        Down,
        Left,
        Right,
        Node
    };
    enum State
    {
        Running,
        Win,
        Uninitialized
    };
    const std::vector<Point> STEP = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};

    Level();
    ~Level() {}
    virtual void loadFromFile(const std::string &filename);
    void showInConsole() const;
    void move(Direction direction);

    const std::vector<std::string> &getLevel() const { return mLevel; }
    State getState() const { return mState; }
    int getMoveCount() const { return mMoveCount; }
    int getPushCount() const { return mPushCount; }
    std::vector<Point> &getEndPoints() { return mEndPoints; }

protected:
    virtual void onMove(Point point, Point next);

private:
    void removeEndPoints();
    void updateState();

    std::vector<std::string> mLevel;
    std::vector<Point> mEndPoints;
    Point mManPoint;
    State mState;
    int mMoveCount, mPushCount;
};

#endif
