
// COS30008, Final Exam, 2020

#pragma once

#include <stdexcept>
#include <iostream>
    
#ifdef P3
#include "LinearVisitor.h"
#endif

template<class T>
class TTree
{
private:
    
    T fKey;
    TTree<T>* fLeft;
    TTree<T>* fMiddle;
    TTree<T>* fRight;
    
    TTree() : fKey()        // use default constructor to initialize fKey
    {
        fLeft = &NIL;       // loop-back: The sub-trees of a TTree object with
        fMiddle = &NIL;     //            no children point to NIL.
        fRight = &NIL;
    }
    
    void addSubTree( TTree<T>** aBranch, const TTree<T>& aTTree )
    {
        if ( *aBranch != &NIL )
        {
            delete *aBranch;
        }

        *aBranch = (TTree<T>*)&aTTree;
    }

    const TTree<T>& removeSubTree(TTree<T>** aBranch)
    {
        if ( *aBranch == &NIL)
        {
            throw std::domain_error("Empty TTree");
        }
        else 
        {
            //constant refference 
            const TTree<T> &ref = aBranch;
            *aBranch = &NIL;
            return ref;
        }
    }
    
public:

    static TTree<T> NIL;    // sentinel

    // TTree constructor (takes one argument)
    TTree(const T& aKey) : fKey(aKey)
    {
        fLeft = &NIL;
        fMiddle = &NIL;
        fRight = &NIL;
    }
    
    // destructor (free sub-trees, must not free empty TTree)
    ~TTree();
    
    // copy constructor, must not copy empty TTree
    TTree( const TTree<T>& aOtherTTree );
    
    // assignment operator, must not copy empty TTree
    TTree<T>& operator=( const TTree<T>& aOtherTTree );
    
    // clone TTree, must not copy empty TTree
    TTree<T>* clone() const;

    // return key value, may throw domain_error if empty
    const T& getKey() const;

    // returns true if this TTree is empty
    bool isEmpty() const;
    
    // getters for subtrees
    const TTree<T>& getLeft() const
    {
        if (isEmpty())
        {
            throw std::domain_error("Empty TTree");
        }
        else
        {
            return *fLeft;
        }
    }
    
    const TTree<T>& getMiddle() const
    {
        if (isEmpty())
        {
            throw std::domain_error("Empty TTree");
        }
        else
        {
            return *fMiddle;
        }
    }
    
    const TTree<T>& getRight() const
    {
        if (isEmpty())
        {
            throw std::domain_error("Empty TTree");
        }
        else
        {
            return *fRight;
        }
    }

    // add a subtree
    void addLeft( const TTree<T>& aTTree )
    {
        addSubTree( &fLeft, aTTree );
    }
    
    void addMiddle( const TTree<T>& aTTree )
    {
        addSubTree( &fMiddle, aTTree );
    }
    
    void addRight( const TTree<T>& aTTree )
    {
        addSubTree( &fRight, aTTree );
    }
        
    // remove a subtree, may through a domain error
    const TTree<T>& removeLeft()
    {
        if (isEmpty())
        {
            throw std::domain_error("Cant remove child-tree/branch ; empty");
        }
        else
        {
            return removeSubTree(&fLeft);
        }
    }
    
    const TTree<T>& removeMiddle()
    {
        if (isEmpty())
        {
            throw std::domain_error("Cant remove child-tree/branch ; empty");
        }
        else
        {
            return removeSubTree(&fMiddle);
        }
    }
    
    const TTree<T>& removeRight()
    {
        if (isEmpty())
        {
            throw std::domain_error("Cant remove child-tree/branch ; empty");
        }
        else
        {
            return removeSubTree(&fRight);
        }
    }
    
    void traverseDepthFirst( TreeVisitor<T>& aVisitor ) const;
};

template<class T> TTree<T>::~TTree()
{
    if (fLeft != &NIL)
        delete fLeft;
    if (fMiddle != &NIL)
        delete fMiddle;
    if (fRight != &NIL)
        delete fRight;
}

template<class T>
inline TTree<T>::TTree(const TTree<T>& aOtherTTree)
{
    if (&aOtherTTree == &NIL)
    {
        throw std::domain_error("Copying NIL.");
    }

    fKey = aOtherTTree.fKey;

    fLeft = aOtherTTree.fLeft->clone();
    fMiddle = aOtherTTree.fMiddle->clone();
    fRight = aOtherTTree.fRight->clone();

}

template<class T>
inline TTree<T>& TTree<T>::operator=(const TTree<T>& aOtherTTree)
{
    if (&aOtherTTree == &NIL)
    {
        throw std::domain_error("Copying NIL.");
    }
    if (this != &aOtherTTree)
    {
        fKey = aOtherTTree.fKey;

        if (!isEmpty())
        {
            delete fLeft;
            delete fMiddle;
            delete fRight;
        }
        fLeft = aOtherTTree.fLeft->clone();
        fMiddle = aOtherTTree.fMiddle->clone();
        fRight = aOtherTTree.fRight->clone();
    }
    return *this;
}

template<class T>
inline TTree<T>* TTree<T>::clone() const
{
    if (!isEmpty())
    {
        return new TTree(*this);
    }
    else
    {
        return &NIL;
    }
}

template<class T>
inline const T& TTree<T>::getKey() const
{
    if (isEmpty())
    {
        throw std::domain_error("Empty TTree");
    }
    else
    {
        return fKey;
    }
}

template<class T>
inline bool TTree<T>::isEmpty() const
{
    return (this == &NIL);
}

template<class T>
inline void TTree<T>::traverseDepthFirst(TreeVisitor<T>& aVisitor) const
{
    //use recursion to traverse each node
    if(!isEmpty())
    {
        aVisitor.preVisit(getKey());

        getLeft().traverseDepthFirst(aVisitor);
        getMiddle().traverseDepthFirst(aVisitor);
        getRight().traverseDepthFirst(aVisitor);

        aVisitor.postVisit(getKey());
    }
    else 
    {
        aVisitor.emitNIL();
    }
}

template<class T>
TTree<T> TTree<T>::NIL;