#include <SectPx_GeoMap_LinearInterpl.hxx>

#include <SectPx_Macros.hxx>
#include <SectPx_Coord.hxx>
#include <SectPx_Par.hxx>
#include <SectPx_ParTools.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const char* tnbLib::sectPxLib::GeoMap_LinearInterpl::typeName_ = "linear_interpl";

void tnbLib::sectPxLib::GeoMap_LinearInterpl::SetQ0
(
	const std::shared_ptr<SectPx_Coord>& theQ0
)
{
	theQ0_ = theQ0;
}

void tnbLib::sectPxLib::GeoMap_LinearInterpl::SetQ1
(
	const std::shared_ptr<SectPx_Coord>& theQ1
)
{
	theQ1_ = theQ1;
}

void tnbLib::sectPxLib::GeoMap_LinearInterpl::SetPar
(
	const std::shared_ptr<SectPx_Par>& thePar
)
{
	AddParameterToParent
	(
		thePar_, thePar,
		"void SetPar(const std::shared_ptr<SectPx_Par>& thePar)"
	);
}

tnbLib::word 
tnbLib::sectPxLib::GeoMap_LinearInterpl::RegObjTypeName() const
{
	return typeName_;
}

tnbLib::Pnt2d 
tnbLib::sectPxLib::GeoMap_LinearInterpl::CalcCoord() const
{
	if (NOT IsComplete())
	{
		FatalErrorIn("Pnt2d CalcCoord() const")
			<< "the map is not complete!" << endl
			<< abort(FatalError);
	}
	const auto par = Par().lock();
	Debug_Null_Pointer(par);

	const auto x = par->Value();

	const auto& q0 = Q0();
	Debug_Null_Pointer(q0);

	const auto& q1 = Q1();
	Debug_Null_Pointer(q1);

	auto pt = q0->Coord() + x * (q1->Coord() - q0->Coord());
	return std::move(pt);
}

Standard_Integer 
tnbLib::sectPxLib::GeoMap_LinearInterpl::NbChildren() const
{
	return 1;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_LinearInterpl::IsComplete() const
{
	if (NOT Q0()) return Standard_False;
	if (NOT Q1()) return Standard_False;
	ReturnFalseIfNull(Par());

	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_LinearInterpl::HasChildren() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::sectPxLib::GeoMap_LinearInterpl::HasChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	ReturnTrueIfParBelongsToThisParent(Par(), thePar);
	return Standard_False;
}


void tnbLib::sectPxLib::GeoMap_LinearInterpl::RemoveThisFromChildren() const
{
	auto par = Par().lock();
	if (par)
	{
		RemoveThisFromChild(par);
	}
}

void tnbLib::sectPxLib::GeoMap_LinearInterpl::AddThisToChildren() const
{
	AddThisParentToChildren(Par());
}

void tnbLib::sectPxLib::GeoMap_LinearInterpl::AddThisToChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	AddThisParentToChild(thePar);
}

void tnbLib::sectPxLib::GeoMap_LinearInterpl::RemoveThisFromChild
(
	const std::shared_ptr<SectPx_Child>& thePar
) const
{
	RemoveThisParentFromChild(thePar);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::sectPxLib::GeoMap_LinearInterpl::RetrieveChildren() const
{
	DefineChildList(childs);
	AddParToChildList(Par(), childs);
	return std::move(childs);
}

std::shared_ptr<tnbLib::sectPxLib::GeoMap_LinearInterpl>
tnbLib::sectPxLib::GeoMap_LinearInterpl::MakeLinearInterpl
(
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
{
	const auto geoMap = 
		std::make_shared<GeoMap_LinearInterpl>
		(
			0,
			GeoMap_LinearInterpl::typeName_
			);
	Debug_Null_Pointer(geoMap);

	theReg->Import(geoMap);
	return std::move(geoMap);
}