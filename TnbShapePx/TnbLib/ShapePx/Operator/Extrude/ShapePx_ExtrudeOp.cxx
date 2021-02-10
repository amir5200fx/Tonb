#include <ShapePx_ExtrudeOp.hxx>

#include <SectPx_TopoSegment.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_Pole.hxx>
#include <SectPx_Spacing.hxx>
#include <ShapePx_Section.hxx>
#include <ShapePx_ExtrudedPatch.hxx>
#include <ShapePx_CtrlNet.hxx>
#include <ShapePx_Tools.hxx>
#include <ShapePx_ParValue.hxx>
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

	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been found!" << endl
			<< abort(FatalError);
	}

	auto Xs = Spacing()->Sections();
	const auto x0 = Spacing()->Lower();
	const auto x1 = Spacing()->Upper();

	//- update profiles before retrieving the values
	Patch()->UpdateProfiles();

	const auto& section = Patch()->Section();
	Debug_Null_Pointer(section);

	auto net = std::make_shared<ShapePx_CtrlNet>();
	net->RowsRef().reserve(Xs.size());

	auto poles = section->RetrievePoles(Curve());
	auto profile = SectPx_Tools::RetrieveInnerSegments(poles);

	auto knots = SectPx_Tools::Knots(profile, DegreeU());

	net->KnotsRef() = std::move(knots);

	for (auto x : Xs)
	{
		auto paraList = Patch()->RetrieveParValues(x);

		section->SetValues(paraList);

		auto Qs = SectPx_Tools::RetrieveControlPoints(profile);
		auto Ws = SectPx_Tools::RetrieveWeights(profile);

		auto paired = ShapePx_Tools::CtrlRow(Qs, Ws);
		ShapePx_CtrlRow row(std::move(paired), x);
		net->RowsRef().push_back(std::move(row));
	}

	SetNet(std::move(net));
	Change_IsDone() = Standard_True;
}