#include <CrankNicolsonDdtScheme.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		makeFvDdtScheme(CrankNicolsonDdtScheme)
	}
}

// ************************************************************************* //