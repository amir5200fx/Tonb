#include <pureMixture.hxx>

#include <error.hxx>
#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	template<class ThermoType>
	pureMixture<ThermoType>::pureMixture
	(
		const dictionary& thermoDict,
		const fvMesh& mesh,
		const objectRegistry& obj
	)
		:
		basicMixture(thermoDict, mesh, obj),
		mixture_(thermoDict.lookup("mixture"))
	{}


	// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

	template<class ThermoType>
	pureMixture<ThermoType>::~pureMixture()
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class ThermoType>
	void pureMixture<ThermoType>::read(const dictionary& thermoDict)
	{
		mixture_ = ThermoType(thermoDict.lookup("mixture"));
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //