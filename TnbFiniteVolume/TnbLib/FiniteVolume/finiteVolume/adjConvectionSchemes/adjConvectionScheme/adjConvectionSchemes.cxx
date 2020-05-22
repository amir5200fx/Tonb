#include <adjConvectionScheme.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
		// Define the constructor function hash tables

#define makeBaseAdjConvectionScheme(Type)                                     \
                                                                              \
defineTemplateRunTimeSelectionTable                                           \
(                                                                             \
    adjConvectionScheme<Type>,                                                \
    Istream                                                                   \
);                                                                            \
                                                                              \

		makeBaseAdjConvectionScheme(vector)


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //