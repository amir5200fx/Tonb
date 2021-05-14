#include <Marine_DiscretePlane.hxx>

#include <Geo2d_ApprxCurve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_Plane.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	const std::shared_ptr<Geo_ApprxCurve_Info> Marine_DiscretePlane::gl_approx_curve_info =
		std::make_shared<Geo_ApprxCurve_Info>();

	class Marine_DiscretePlaneRunTime
	{
		/*Private Data*/

	public:

		Marine_DiscretePlaneRunTime()
		{
			Marine_DiscretePlane::gl_approx_curve_info_init();
		}


	};
}

tnbLib::Marine_DiscretePlaneRunTime myMarine_DiscretePlaneRunTimeObject;

void tnbLib::Marine_DiscretePlane::gl_approx_curve_info_init()
{
	auto& inf = *gl_approx_curve_info;
	inf.SetNbSamples(5);
	inf.SetAngle(5.0);
	inf.SetApprox(1.0E-4);
	inf.SetMinSize(1.0E-4);
	inf.SetMaxNbSubdivision(20);
}

void tnbLib::Marine_DiscretePlane::Perform()
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto edges = Plane()->RetrieveEntities(Pln_EntityType::EDGE);
	for (const auto& x : edges)
	{
		auto edge = std::dynamic_pointer_cast<Pln_Edge>(x);
		Debug_Null_Pointer(edge);

		const auto& curve = edge->Curve();
		Geo2d_ApprxCurve alg
		(
			curve->Geometry(), 
			curve->FirstParameter(),
			curve->LastParameter(),
			ApproxCurveInfo()
		);
		alg.Perform();
		Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

		edge->Mesh() = alg.Chain();
	}
	Change_IsDone() = Standard_True;
}