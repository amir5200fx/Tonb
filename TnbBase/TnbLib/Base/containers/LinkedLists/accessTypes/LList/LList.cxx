#include <LList.hxx>

#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::LList<LListBase, T>::LList(const LList<LListBase, T>& lst)
	:
	LListBase()
{
	for (const_iterator iter = lst.begin(); iter != lst.end(); ++iter)
	{
		this->append(iter());
	}
}


template<class LListBase, class T>
tnbLib::LList<LListBase, T>::~LList()
{
	this->clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::clear()
{
	label oldSize = this->size();
	for (label i = 0; i < oldSize; ++i)
	{
		this->removeHead();
	}

	LListBase::clear();
}


template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::transfer(LList<LListBase, T>& lst)
{
	clear();
	LListBase::transfer(lst);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::operator=(const LList<LListBase, T>& lst)
{
	this->clear();

	for (const_iterator iter = lst.begin(); iter != lst.end(); ++iter)
	{
		this->append(iter());
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

#include <LListIO.cxx>