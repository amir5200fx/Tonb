#include <FastDiscrete_System.hxx>

#include <FastDiscrete_Params.hxx>

namespace tnbLib
{

	std::shared_ptr<FastDiscrete_Params> sysLib::gl_fast_discrete_parameters =
		std::make_shared<FastDiscrete_Params>();
}