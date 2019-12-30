#include <UDictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Null constructor
	template<class T>
	UDictionary<T>::UDictionary()
	{}


	// Copy constructor
	template<class T>
	UDictionary<T>::UDictionary(const UDictionary& dict)
		:
		DictionaryBase<UIDLList<T>, T>(dict)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //