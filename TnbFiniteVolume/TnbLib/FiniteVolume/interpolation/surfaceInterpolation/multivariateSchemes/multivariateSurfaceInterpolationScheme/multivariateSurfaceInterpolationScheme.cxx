#include <multivariateSurfaceInterpolationScheme.hxx>

#include <fv.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	//- Construct from face-flux field and coefficient
	template<class Type>
	multivariateSurfaceInterpolationScheme<Type>::
		multivariateSurfaceInterpolationScheme
		(
			const fvMesh& mesh,
			const multivariateSurfaceInterpolationScheme<Type>::fieldTable& vtfs,
			const surfaceScalarField&,
			Istream&
		)
		:
		mesh_(mesh),
		fields_(vtfs)
	{}


	// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

	// Return weighting factors for scheme given by name in dictionary
	template<class Type>
	tmp<multivariateSurfaceInterpolationScheme<Type> >
		multivariateSurfaceInterpolationScheme<Type>::New
		(
			const fvMesh& mesh,
			const multivariateSurfaceInterpolationScheme<Type>::fieldTable& vtfs,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
	{
		if (fv::debug)
		{
			Info << "multivariateSurfaceInterpolationScheme<Type>::New"
				"(const fvMesh& mesh, const fieldTable&, "
				"const surfaceScalarField&, Istream&) : "
				"constructing surfaceInterpolationScheme<Type>"
				<< endl;
		}

		const word schemeName(schemeData);

		typename IstreamConstructorTable::iterator constructorIter =
			IstreamConstructorTablePtr_->find(schemeName);

		if (constructorIter == IstreamConstructorTablePtr_->end())
		{
			FatalIOErrorIn
			(
				"multivariateSurfaceInterpolationScheme<Type>::New"
				"(const fvMesh& mesh, const fieldTable&, "
				"const surfaceScalarField&, Istream&)",
				schemeData
			) << "unknown discretisation scheme " << schemeName << endl << endl
				<< "Valid schemes are :" << endl
				<< IstreamConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return constructorIter()(mesh, vtfs, faceFlux, schemeData);
	}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	template<class Type>
	multivariateSurfaceInterpolationScheme<Type>::
		~multivariateSurfaceInterpolationScheme()
	{}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //