#include <fourthSnGrad.hxx>

#include <fvMesh.hxx>
#include <GeometricFields.hxx>
#include <surfaceMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		makeSnGradTypeScheme(fourthSnGrad, scalar)
			makeSnGradTypeScheme(fourthSnGrad, vector)
	}
}

// ************************************************************************* //