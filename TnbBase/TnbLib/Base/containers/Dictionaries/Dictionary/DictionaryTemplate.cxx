#include <DictionaryTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::Dictionary<T>::Dictionary()
{}


template<class T>
tnbLib::Dictionary<T>::Dictionary(const Dictionary& dict)
	: DictionaryBase<IDLList<T>, T>(dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::Dictionary<T>::erase(const word& keyword)
{
	T* tPtr;
	if (tPtr = this->remove(keyword))
	{
		delete tPtr;
		return true;
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //