#include <ggiAMGInterface.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<Field<Type> > ggiAMGInterface::fastReduce(const UList<Type>& ff) const
	{
		// Algorithm
		// Local processor contains faceCells part of the zone and requires
		// zoneAddressing part.
		// For fast communications, each processor will send the faceCells and
		// zoneAddressing to the master.  Master will assemble global zone
		// and send off messages to all processors containing only
		// the required data
		// HJ, 24/Jun/2011

		if (ff.size() != this->size())
		{
			FatalErrorIn
			(
				"tmp<Field<Type> > ggiAMGInterface::fastReduce"
				"("
				"    const UList<Type>& ff"
				") const"
			) << "Wrong field size.  ff: " << ff.size()
				<< " interface: " << this->size()
				<< abort(FatalError);
		}

		if (localParallel() || !Pstream::parRun())
		{
			// Field remains identical: no parallel communications required
			tmp<Field<Type> > tresult(new Field<Type>(ff));

			return tresult;
		}
		else
		{
			// Optimised mapDistribute

			// Execute init reduce to calculate addressing if not already done
			map();

			// Prepare for distribute: field will be expanded to zone size
			List<Type> expand = ff;

			map().distribute(expand);

			const labelList& shadowZa = shadowInterface().zoneAddressing();

			// Prepare return field: zone size
			tmp<Field<Type> > tresult
			(
				new Field<Type>(shadowZa.size())
			);
			Field<Type>& result = tresult();

			// Filter from expanded field to zone size
			forAll(shadowZa, shadowZaI)
			{
				result[shadowZaI] = expand[shadowZa[shadowZaI]];
			}

			return tresult;
		}
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //