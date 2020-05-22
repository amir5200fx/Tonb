#include <boundedBackwardDdtScheme.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{

		defineTypeNameAndDebug(boundedBackwardDdtScheme, 0);

		ddtScheme<scalar>::addIstreamConstructorToTable<boundedBackwardDdtScheme>
			addboundedBackwardDdtSchemeIstreamConstructorToTable_;

	}
}

// ************************************************************************* //