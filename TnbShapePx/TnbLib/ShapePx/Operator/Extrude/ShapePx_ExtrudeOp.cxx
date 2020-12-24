#include <ShapePx_ExtrudeOp.hxx>

#include <SectPx_TopoSegment.hxx>
#include <SectPx_Tools.hxx>
#include <ShapePx_Spacing.hxx>
#include <ShapePx_Section.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_CtrlNet.hxx>
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

	const auto& section = Patch()->Section();
	Debug_Null_Pointer(section);
	const auto nbProfiles = section->NbProfiles();

	std::vector<std::shared_ptr<ShapePx_CtrlNet>> nets;
	nets.reserve(nbProfiles);
	for (auto& x : nets)
	{
		x = std::make_shared<ShapePx_CtrlNet>();
		x->RowsRef().reserve(Xs.size());
	}

	for (auto x : Xs)
	{
		auto xs = x0 + Spacing()->NormalizedParameter(x)*(x1 - x0);
		auto paraList = Patch()->RetrieveParValues(xs);

		const auto& section = Patch()->Section();
		Debug_Null_Pointer(section);

		section->SetValues(paraList);

		auto profiles = section->RetrieveCurveQs();

		Standard_Integer k = 0;
		for (const auto& p : profiles)
		{
			Debug_Null_Pointer(p);
			auto pnts = SectPx_Tools::RetrieveControlPoints(p);

			auto& row = nets[k++]->RowsRef();
			row.push_back(std::move(pnts));
		}
	}
	Change_IsDone() = Standard_True;
}