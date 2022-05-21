#include "Level.hpp"

#include <fstream>
#include <iostream>
#include <cstdlib>

Level::Level()
{
    mState = Uninitialized;
    mMoveCount = 0;
    mPushCount = 0;
}

void Level::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "No se puede abrir: " << filename << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line))
    {
        mLevel.push_back(line);
    }
    removeEndPoints();
    mState = Running;
}

void Level::removeEndPoints()
{
    for (int i = 0; i < int(mLevel.size()); ++i)
    {
        for (int j = 0; j < int(mLevel[i].size()); ++j)
        {
            char &current = mLevel[i][j];
            if (current == BOXENDPOINT)
            {
                current = BOX;
                mEndPoints.push_back({i, j});
            }
            else if (current == MANENDPOINT)
            {
                current = MAN;
                mEndPoints.push_back({i, j});
                mManPoint = {i, j};
            }
            else if (current == ENDPOINT)
            {
                current = EMPTY;
                mEndPoints.push_back({i, j});
            }
            else if (current == MAN)
            {
                mManPoint = {i, j};
            }
        }
    }
}

void Level::updateState()
{
    for (const auto &point : mEndPoints)
    {
        if (mLevel[point.row][point.col] != BOX)
        {
            return;
        }
    }
    mState = Win;
}

void Level::showInConsole() const
{
    auto level = mLevel;
    std::cout << "Movimientos: " << mMoveCount << "\n";
    std::cout << "  Enpujones: " << mPushCount << "\n";
    for (const auto &point : mEndPoints)
    {
        if (level[point.row][point.col] == BOX)
        {
            level[point.row][point.col] = BOXENDPOINT;
        }
        else if (level[point.row][point.col] == MAN)
        {
            level[point.row][point.col] = MANENDPOINT;
        }
        else
        {
            level[point.row][point.col] = ENDPOINT;
        }
    }
    for (const auto &line : level)
    {
        std::cout << line << "\n";
    }
}

void Level::move(Direction direction)
{
    if (mState != Running)
    {
        return;
    }
    Point next = mManPoint + STEP[direction];
    if (mLevel[next.row][next.col] == EMPTY)
    {
        onMove(mManPoint, next);
        mLevel[mManPoint.row][mManPoint.col] = EMPTY;
        mLevel[next.row][next.col] = MAN;
        mManPoint = next;
        ++mMoveCount;
    }
    else if (mLevel[next.row][next.col] == BOX)
    {
        Point nextNext = next + STEP[direction];
        if (mLevel[nextNext.row][nextNext.col] == EMPTY)
        {
            onMove(next, nextNext);
            onMove(mManPoint, next);
            mLevel[nextNext.row][nextNext.col] = BOX;
            mLevel[next.row][next.col] = MAN;
            mLevel[mManPoint.row][mManPoint.col] = EMPTY;
            mManPoint = next;
            ++mMoveCount;
            ++mPushCount;
            updateState();
        }
    }
}

void Level::onMove(Point, Point) {}
