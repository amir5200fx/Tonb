#include <gradScheme.hxx>

#include <fv.hxx>
#include <HashTable.hxx>
#include <primitiveFields.hxx>
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<gradScheme<Type> > gradScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				Info << "gradScheme<Type>::New"
					"(const fvMesh& mesh, Istream& schemeData) : "
					"constructing gradScheme<Type>"
					<< endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorIn
				(
					"gradScheme<Type>::New"
					"(const fvMesh& mesh, Istream& schemeData)",
					schemeData
				) << "Grad scheme not specified" << endl << endl
					<< "Valid grad schemes are :" << endl
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
					"gradScheme<Type>::New"
					"(const fvMesh& mesh, Istream& schemeData)",
					schemeData
				) << "Unknown grad scheme " << schemeName << nl << nl
					<< "Valid grad schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		gradScheme<Type>::~gradScheme()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class Type>
		tnbLib::tmp
			<
			tnbLib::GeometricField
			<
			typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
			tnbLib::fvPatchField,
			tnbLib::volMesh
			>
			>
			tnbLib::fv::gradScheme<Type>::grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vsf,
				const word& name
			) const
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			typedef GeometricField<GradType, fvPatchField, volMesh> GradFieldType;

			if (!this->mesh().changing() && this->mesh().solutionDict().cache(name))
			{
				if (!mesh().objectRegistry::template foundObject<GradFieldType>(name))
				{
					solution::cachePrintMessage("Calculating and caching", name, vsf);
					tmp<GradFieldType> tgGrad = calcGrad(vsf, name);
					regIOobject::store(tgGrad.ptr());
				}

				solution::cachePrintMessage("Retrieving", name, vsf);
				GradFieldType& gGrad = const_cast<GradFieldType&>
					(
						mesh().objectRegistry::template lookupObject<GradFieldType>(name)
						);

				if (gGrad.upToDate(vsf.name()))
				{
					if (solution::debug)
					{
						Info << ": up-to-date." << endl;
					}

					return gGrad;
				}
				else
				{
					if (solution::debug)
					{
						Info << ": not up-to-date." << endl;
						solution::cachePrintMessage("Deleting", name, vsf);
					}
					gGrad.release();
					delete &gGrad;

					solution::cachePrintMessage("Recalculating", name, vsf);
					tmp<GradFieldType> tgGrad = calcGrad(vsf, name);

					solution::cachePrintMessage("Storing", name, vsf);
					regIOobject::store(tgGrad.ptr());
					GradFieldType& gGrad = const_cast<GradFieldType&>
						(
							mesh().objectRegistry::template lookupObject<GradFieldType>
							(
								name
								)
							);

					return gGrad;
				}
			}
			else
			{
				if (mesh().objectRegistry::template foundObject<GradFieldType>(name))
				{
					GradFieldType& gGrad = const_cast<GradFieldType&>
						(
							mesh().objectRegistry::template lookupObject<GradFieldType>
							(
								name
								)
							);

					if (gGrad.ownedByRegistry())
					{
						solution::cachePrintMessage("Deleting", name, vsf);
						gGrad.release();
						delete &gGrad;
					}
				}

				solution::cachePrintMessage("Calculating", name, vsf);
				return calcGrad(vsf, name);
			}
		}


		template<class Type>
		tnbLib::tmp
			<
			tnbLib::GeometricField
			<
			typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
			tnbLib::fvPatchField,
			tnbLib::volMesh
			>
			>
			tnbLib::fv::gradScheme<Type>::grad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vsf
			) const
		{
			return grad(vsf, "grad(" + vsf.name() + ')');
		}


		template<class Type>
		tnbLib::tmp
			<
			tnbLib::GeometricField
			<
			typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
			tnbLib::fvPatchField,
			tnbLib::volMesh
			>
			>
			tnbLib::fv::gradScheme<Type>::grad
			(
				const tmp<GeometricField<Type, fvPatchField, volMesh> >& tvsf
			) const
		{
			typedef typename outerProduct<vector, Type>::type GradType;
			typedef GeometricField<GradType, fvPatchField, volMesh> GradFieldType;

			tmp<GradFieldType> tgrad = grad(tvsf());
			tvsf.clear();
			return tgrad;
		}


		template<class Type>
		tmp
			<
			BlockLduSystem<vector, typename outerProduct<vector, Type>::type>
			>
			gradScheme<Type>::fvmGrad
			(
				const GeometricField<Type, fvPatchField, volMesh>& vf
			) const
		{
			FatalErrorIn
			(
				"tmp<BlockLduSystem> gradScheme<Type>::fvmGrad\n"
				"(\n"
				"    GeometricField<Type, fvPatchField, volMesh>&"
				")\n"
			) << "Implicit gradient operator currently defined only for "
				<< "Gauss linear and leastSquares "
				<< "(cell and face limiters are optional)."
				<< abort(FatalError);

			typedef typename outerProduct<vector, Type>::type GradType;

			tmp<BlockLduSystem<vector, GradType> > tbs
			(
				new BlockLduSystem<vector, GradType>(vf.mesh())
			);

			return tbs;
		}


		template<class Type>
		void gradScheme<Type>::correctBoundaryConditions
		(
			const GeometricField<Type, fvPatchField, volMesh>& vsf,
			GeometricField
			<
			typename outerProduct<vector, Type>::type, fvPatchField, volMesh
			>& gGrad
		)
		{
			forAll(vsf.boundaryField(), patchi)
			{
				if (!vsf.boundaryField()[patchi].coupled())
				{
					vectorField n = vsf.mesh().boundary()[patchi].nf();

					gGrad.boundaryField()[patchi] += n *
						(
							vsf.boundaryField()[patchi].snGrad()
							- (n & gGrad.boundaryField()[patchi])
							);
				}
			}

			// Note: coupled boundaries provide patchNeighbourField, which is only
			// updated on correct boundary conditions.  Therefore, evaluateCoupled()
			// should be called here. HJ, Apr/2013
			gGrad.boundaryField().evaluateCoupled();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //