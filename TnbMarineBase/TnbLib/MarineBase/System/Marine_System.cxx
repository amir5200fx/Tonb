#include <Marine_System.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

namespace tnbLib
{

	TnbMarine_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> sysLib::gl_marine_integration_info =
		std::make_shared<NumAlg_AdaptiveInteg_Info>();
}

void tnbLib::sysLib::init_gl_marine_integration_info()
{
	auto& info = *gl_marine_integration_info;
	info.SetMaxNbIterations(50);
	info.SetNbInitIterations(4);
	info.SetTolerance(1.0E-4);
}

namespace tnbLib
{

	class RunInitMarineIntegration
	{
	public:
		RunInitMarineIntegration()
		{
			tnbLib::sysLib::init_gl_marine_integration_info();
		}
	};

	RunInitMarineIntegration runIt;
}