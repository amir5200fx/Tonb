#include <PtrDictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class T>
	PtrDictionary<T>::PtrDictionary()
	{}


	template<class T>
	PtrDictionary<T>::PtrDictionary(const PtrDictionary& dict)
		:
		DictionaryBase<DLPtrList<T>, T>(dict)
	{}


	template<class T>
	template<class INew>
	PtrDictionary<T>::PtrDictionary(Istream& is, const INew& iNew)
		:
		DictionaryBase<DLPtrList<T>, T>(is, iNew)
	{}


	template<class T>
	PtrDictionary<T>::PtrDictionary(Istream& is)
		:
		DictionaryBase<DLPtrList<T>, T>(is)
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //