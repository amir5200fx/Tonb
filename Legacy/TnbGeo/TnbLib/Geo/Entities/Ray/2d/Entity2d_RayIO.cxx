#include <Entity2d_Ray.hxx>

#include <token.hxx>

namespace tnbLib
{

	TnbGeo_EXPORT std::ostream& operator<<
		(std::ostream& os, const Entity2d_Ray& theRay)
	{
		os << token::BEGIN_BLOCK
			<< token::BEGIN_LIST
			<< theRay.Coord()
			<< token::END_LIST
			<< token::COMMA
			<< token::BEGIN_LIST
			<< theRay.Direction()
			<< token::END_LIST
			<< token::END_BLOCK;
		return os;
	}
}