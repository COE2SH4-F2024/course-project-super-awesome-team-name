#include "objPosArrayList.h"
#include <stdexcept>

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        for (int i = listSize; i > 0; --i)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        listSize++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize < arrayCapacity)
    {
        aList[listSize] = thisPos;
        listSize++;
    }
}

void objPosArrayList::removeHead()
{
    if (listSize > 0)
    {
        for (int i = 0; i < listSize - 1; ++i)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if (listSize > 0)
    {
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize > 0)
    {
        return aList[0];
    }
    throw std::out_of_range("List is empty");
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize > 0)
    {
        return aList[listSize - 1];
    }
    throw std::out_of_range("List is empty");
}

objPos objPosArrayList::getElement(int index) const
{
    if (index >= 0 && index < arrayCapacity)
    {
        if (index < listSize)
        {
            return aList[index];
        }
        return objPos();
    }
    throw std::out_of_range("Index out of bounds");
}
