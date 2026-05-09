#include <Discret2d_Wire.hxx>

#include <Discret2d_PlnCurve.hxx>
#include <Discret2d_Curve_Function.hxx>
#include <Discret_CurveInfo.hxx>
#include <Cad_ParaCurve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Discret2d_Wire::Perform()
{
	if (NOT Wire())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no wire has been loaded." << endl
			<< abort(FatalError);
	}
	if (NOT Function())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no function has been found." << endl
			<< abort(FatalError);
	}
	if (NOT ApprxInfo())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no info has been found." << endl
			<< abort(FatalError);
	}
	const auto& edges = Wire()->Edges();
	Pnt2d last;
	std::vector<Pnt2d> pts;
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		const auto& curve = x->Curve();

		auto alg = std::make_shared<Discret2d_PlnCurve>();
		alg->SetCurve(curve);
		alg->SetFunction(Function());
		alg->SetInfo(ApprxInfo());
		alg->SetU0(curve->FirstParameter());
		alg->SetU1(curve->LastParameter());

		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not done!");

		auto xs = alg->Mesh();
		if (NOT x->Sense())
		{
			std::reverse(xs->begin(), xs->end());
		}
		std::vector<Pnt2d> coords;
		coords.reserve(xs->size());
		for (auto u : *xs)
		{
			auto pt = curve->Value(u);
			coords.push_back(std::move(pt));
		}
		for (size_t i = 0; i < coords.size() - 1; i++)
		{
			auto& pt = coords.at(i);
			pts.push_back(std::move(pt));
		}
		last = coords.at(coords.size() - 1);
	}
	pts.push_back(std::move(last));
	thePolygon_ = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	Change_IsDone() = Standard_True;
}