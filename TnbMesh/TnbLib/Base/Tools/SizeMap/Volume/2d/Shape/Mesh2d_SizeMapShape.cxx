#include <Mesh2d_SizeMapShape.hxx>

#include <Discret2d_Wire.hxx>
#include <Discret_CurveInfo.hxx>
#include <Discret_Curve_UniformSamples.hxx>
#include <Discret2d_PlnCurve_UniLengthFun.hxx>
#include <Cad2d_Plane.hxx>
#include <Entity2d_Box.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

std::shared_ptr<tnbLib::Discret_CurveInfo> tnbLib::Mesh2d_SizeMapShape::DEFAULT_INFO =
std::make_shared<tnbLib::Discret_CurveInfo>();

const Standard_Integer tnbLib::Mesh2d_SizeMapShape::DEFAULT_NB_SAMPLES = 5;

namespace tnbLib
{

	class Mesh2d_SizeMapShape_RunTime_Settings
	{
		/*Private Data*/

	public:

		// default constructor

		Mesh2d_SizeMapShape_RunTime_Settings()
		{
			SetConfigs();
		}

		// Public functions and operators

		static void SetConfigs();
	};
}

void tnbLib::Mesh2d_SizeMapShape_RunTime_Settings::SetConfigs()
{
	const auto& myInfo = Mesh2d_SizeMapShape::DEFAULT_INFO;
	myInfo->SetMaxSubdivide(10);
	myInfo->SetMinSubdivide(4);
}


tnbLib::Entity2d_Box
tnbLib::Mesh2d_SizeMapShape::CalcBoundingBox() const
{
	return theVolume_->BoundingBox(0);
}

Standard_Boolean tnbLib::Mesh2d_SizeMapShape::IsShape() const
{
	return Standard_True;
}

void tnbLib::Mesh2d_SizeMapShape::Perform()
{
	const auto& discretCrvInfo = DiscretInfo();
	Debug_Null_Pointer(discretCrvInfo);
	const auto samplesPoints = std::make_shared<Discret_Curve_UniformSamples>();
	samplesPoints->SetNbSamples(NbSamples());

	const auto elemSize = Size();

	const auto discretFun = std::make_shared<Discret2d_PlnCurve_UniLengthFun>();
	discretFun->SetSamples(samplesPoints);
	discretFun->SetSize(elemSize);

	const auto& wire = Volume()->OuterWire();
	Debug_Null_Pointer(wire);
	const auto alg = std::make_shared<Discret2d_Wire>();
	alg->SetWire(wire);
	alg->SetInfo(discretCrvInfo);
	alg->SetFunction(discretFun);
	
	alg->Perform();
	Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");
	BoundaryRef() = alg->Polygon();
	Mesh2d_SizeMapVolume::Perform();
}
