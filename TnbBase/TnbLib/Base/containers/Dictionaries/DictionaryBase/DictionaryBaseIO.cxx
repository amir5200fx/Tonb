#include <IOstreams.hxx>
#include <DictionaryBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * * //

	template<class IDLListType, class T>
	Ostream& operator<<(Ostream& os, const DictionaryBase<IDLListType, T>& dict)
	{
		for
			(
				typename IDLListType::const_iterator iter = dict.begin();
				iter != dict.end();
				++iter
				)
		{
			os << *iter;

			// Check stream before going to next entry.
			if (!os.good())
			{
				Info
					<< "operator<<(Ostream& os, const DictionaryBase&) : "
					<< "Can't write entry for DictionaryBase"
					<< endl;

				return os;
			}
		}

		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //