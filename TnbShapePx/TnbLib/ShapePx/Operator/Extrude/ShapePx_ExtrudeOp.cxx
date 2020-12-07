#include <ShapePx_ExtrudeOp.hxx>

#include <SectPx_TopoSegment.hxx>
#include <SectPx_Tools.hxx>
#include <ShapePx_Spacing.hxx>
#include <ShapePx_Section.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::ShapePx_ExtrudeOp::IsExtrude() const
{
	return Standard_True;
}

void tnbLib::ShapePx_ExtrudeOp::Perform()
{
	if (NOT Patch())
	{
		FatalErrorIn(FunctionSIG)
			<< "no patch has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Spacing())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometric spacing has been found!" << endl
			<< abort(FatalError);
	}

	auto Xs = Spacing()->Sections();
	const auto x0 = Patch()->Lower();
	const auto x1 = Patch()->Upper();

	//- update profiles before retrieving the values
	Patch()->UpdateProfiles();

	for (auto x : Xs)
	{
		auto xs = x0 + Spacing()->NormalizedParameter(x)*(x1 - x0);
		auto paraList = Patch()->RetrieveParValues(xs);

		const auto& section = Patch()->Section();
		Debug_Null_Pointer(section);

		section->SetValues(paraList);

		auto profiles = section->RetrieveProfiles();
		for (const auto& p : profiles)
		{
			Debug_Null_Pointer(p);
			auto pnts = SectPx_Tools::RetrieveControlPoints(p);
		}

	}
}