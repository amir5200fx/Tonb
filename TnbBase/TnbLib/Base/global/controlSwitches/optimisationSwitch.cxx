#include <optimisationSwitch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	namespace debug
	{
		// Hashtables to static class attributes addresses holding the
		// runtime optimisationSwitch values.
		// This needs to go on the heap so the destructor will not get
		//  called before the objects' destructor it is overseeing
		ListOptimisationControlSwitches* optimisationSwitchValues_(NULL);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace debug


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}