#include <wallPointData.hxx>

#include <point.hxx>
#include <scalar.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	template <class Type>
	Ostream& operator<<
		(
			Ostream& os,
			const wallPointData<Type>& wDist
			)
	{
		operator<<(os, static_cast<const wallPoint&>(wDist));

		return os << wDist.data();
	}

	template <class Type>
	Istream& operator>>
		(
			Istream& is,
			wallPointData<Type>& wDist
			)
	{
		operator>>(is, static_cast<wallPoint&>(wDist));

		return is >> wDist.data_;
	}

	// ************************************************************************* //

} // End namespace tnbLib

// ************************************************************************* //