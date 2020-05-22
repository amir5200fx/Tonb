#include <adjConvectionScheme.hxx>

#include <HashTable.hxx>
#include <linear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class Type>
		adjConvectionScheme<Type>::adjConvectionScheme(const adjConvectionScheme& cs)
			:
			refCount(),
			mesh_(cs.mesh_)
		{}


		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<adjConvectionScheme<Type> > adjConvectionScheme<Type>::New
		(
			const fvMesh& mesh,
			const volVectorField& Up,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				Info << "adjConvectionScheme<Type>::New"
					"(const fvMesh&, const volVectorField&, Istream&) : "
					"constructing adjConvectionScheme<Type>"
					<< endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorIn
				(
					"adjConvectionScheme<Type>::New"
					"(const fvMesh&, const volVectorField&, Istream&)",
					schemeData
				) << "AdjConvection scheme not specified" << endl << endl
					<< "Valid adjConvection schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename IstreamConstructorTable::iterator cstrIter =
				IstreamConstructorTablePtr_->find(schemeName);

			if (cstrIter == IstreamConstructorTablePtr_->end())
			{
				FatalIOErrorIn
				(
					"adjConvectionScheme<Type>::New"
					"(const fvMesh&, const volVectorField&, Istream&)",
					schemeData
				) << "unknown adjConvection scheme " << schemeName << endl << endl
					<< "Valid adjConvection schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, Up, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		adjConvectionScheme<Type>::~adjConvectionScheme()
		{}


		// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

		template<class Type>
		void adjConvectionScheme<Type>::operator=(const adjConvectionScheme<Type>& cs)
		{
			if (this == &cs)
			{
				FatalErrorIn
				(
					"adjConvectionScheme<Type>::operator="
					"(const adjConvectionScheme<Type>&)"
				) << "attempted assignment to self"
					<< abort(FatalError);
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //