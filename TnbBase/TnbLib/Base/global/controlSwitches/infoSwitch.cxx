#include <infoSwitch.hxx>

namespace tnbLib
{

	namespace debug
	{
		// Hashtables to static class attributes addresses holding the
		// runtime InfoSwitches values.
		// This needs to go on the heap so the destructor will not get
		//  called before the objects' destructor it is overseeing
		ListInfoControlSwitches* infoSwitchValues_(NULL);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace debug


} // End namespace tnbLib