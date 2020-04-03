
#include "ArraySorter.h"
#include <iostream>
using namespace std;

void ArraySorter::stepCompleted(std::ostream& aOStream)
{
    aOStream << "State: [ ";
    for (int i = 0; i < fArraySize; i++)
    {
        aOStream << fArrayOfNumbers[i];
        if (i < fArraySize - 1)
            aOStream << ", ";
    }
    aOStream << " ]" << endl;
}

void ArraySorter::swapElements(unsigned int aSourcIndex, unsigned int aTargetIndex)
{
    swap(fArrayOfNumbers[aSourcIndex], fArrayOfNumbers[aTargetIndex]);
}

ArraySorter::ArraySorter( const int aArrayOfNumbers[], unsigned int aArraySize )
{
    // copy array into sorter
    fArrayOfNumbers = new int[aArraySize];

    for ( unsigned int i = 0; i < aArraySize; i++ )
    {
        fArrayOfNumbers[i] = aArrayOfNumbers[i];
    }
    
    fArraySize = aArraySize;
}

ArraySorter::~ArraySorter()
{
    // delete memory associated with array
    delete [] fArrayOfNumbers;
}

const unsigned int ArraySorter::at(unsigned int aIndex) const
{
    if (aIndex > fArraySize) {
     throw range_error("Index does not correspond to a valid point in array");
    }
    else 
    {
        return fArrayOfNumbers[aIndex];
    }
}

const unsigned int ArraySorter::getRange() const
{
    return fArraySize;
}

void ArraySorter::sort(std::ostream& aOStream)
{
    return stepCompleted(aOStream);
}

std::ostream& operator<<(std::ostream& aOStream, const ArraySorter& aObject)
{
    // TODO: insert return statement here
    aOStream << "[ "; 
    for (int i = 0; i < aObject.getRange(); i++)
    {
        aOStream << aObject.at(i);
        if (i < aObject.getRange()-1) 
        {
            aOStream << ", ";
        }
    }
    aOStream << " ]";
    return aOStream;
}
