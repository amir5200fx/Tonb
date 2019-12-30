#include <UPtrDictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Null constructor
	template<class T>
	UPtrDictionary<T>::UPtrDictionary()
	{}


	// Copy constructor
	template<class T>
	UPtrDictionary<T>::UPtrDictionary(const UPtrDictionary& dict)
		:
		DictionaryBase<DLList<T*>, T>(dict)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //