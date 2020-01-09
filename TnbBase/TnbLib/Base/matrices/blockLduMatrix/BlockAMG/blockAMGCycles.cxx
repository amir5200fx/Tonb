#include <blockAMGCycles.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	template<>
	const char* tnbLib::NamedEnum<tnbLib::blockAMGCycleName::cycleType, 3>::names[] =
	{
		"V-cycle",
		"W-cycle",
		"F-cycle"
	};


	const tnbLib::NamedEnum<tnbLib::blockAMGCycleName::cycleType, 3>
		tnbLib::blockAMGCycleName::cycleNames_;


	// KRJ: 2012-12-15: Is this enough to have the templating?

	defineNamedTemplateTypeNameAndDebug(blockAMGScalarCycle, 0);
	defineNamedTemplateTypeNameAndDebug(blockAMGVectorCycle, 0);
	defineNamedTemplateTypeNameAndDebug(blockAMGTensorCycle, 0);
#define makeNamedTemplateTypeNameAndDebug(type, Type, args)      \
    defineNamedTemplateTypeNameAndDebug(blockAMG##Type##Cycle, 0);

	forAllVectorNTypes(makeNamedTemplateTypeNameAndDebug);

#undef makeNamedTemplateTypeNameAndDebug

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //