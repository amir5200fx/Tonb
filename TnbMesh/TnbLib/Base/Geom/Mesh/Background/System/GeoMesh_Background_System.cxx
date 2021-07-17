#include <GeoMesh_Background_System.hxx>

#include <GeoMesh_Background_Info.hxx>

namespace tnbLib
{
	TnbMesh_EXPORT std::shared_ptr<GeoMesh_Background_SmoothingHvCorrection_Info> sysLib::gl_background_hv_correction_info =
		std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
}

void tnbLib::sysLib::init_gl_background_hv_correction_info()
{
	auto& info = *gl_background_hv_correction_info;
	info.SetMaxNbIters(3);
	info.SetFactor(0.85);
}

namespace tnbLib
{

	class RunInitSmoothingHvCorrection_Info
	{
	public:

		RunInitSmoothingHvCorrection_Info()
		{
			tnbLib::sysLib::init_gl_background_hv_correction_info();
		}
	};
}

tnbLib::RunInitSmoothingHvCorrection_Info runIt;