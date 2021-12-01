#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_Model.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<Aft2d_MetricPrcsr> myPrcssr;

	static std::shared_ptr<Aft2d_Model> myAlg;

	static bool loadTag = false;

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		

	}
}