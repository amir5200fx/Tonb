#include <dimensionedConstants.hxx>

#include <NamedEnum.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	dictionary* dimensionedConstantsPtr_(NULL);

	dictionary& dimensionedConstants()
	{
		// Cannot use static NamedEnum in static initialisation
		// Making local copy
		const NamedEnum
			<
			debug::globalControlDictSwitchSet,
			debug::DIM_GLOBAL_CONTROL_DICT_SWITCH_SET
			> globalControlDictSwitchSetNames;

		return debug::controlDict().subDict
		(
			globalControlDictSwitchSetNames[debug::DIMENSIONED_CONSTANTS]
		);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}