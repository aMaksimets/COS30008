#pragma once
#include <iostream>
#include "TreeVisitor.h"

template<class T>
class LinearVisitor : public TreeVisitor <T>
{
public:
	virtual void visit(const T& aKey) const
	{
		std::cout << aKey;
	}

	virtual void preVisit(const T& aKey) const
	{
		std::cout << "[";
		visit(aKey);
	}

	virtual void postVisit(const T& aKey) const
	{
		std::cout << "]";
	}
};