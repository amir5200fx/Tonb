#include <GModel_ParaWire.hxx>

#include <GModel_ParaCurve.hxx>
#include <GModel_Tools.hxx>
#include <Entity2d_Box.hxx>

tnbLib::GModel_ParaWire::GModel_ParaWire
(
	const std::shared_ptr<curveList>& theCurves
)
	: theCurves_(theCurves)
{
	// empty body
}

tnbLib::GModel_ParaWire::GModel_ParaWire
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const std::shared_ptr<curveList>& theCurves
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theCurves_(theCurves)
{
	// empty body
}

tnbLib::GModel_ParaWire::GModel_ParaWire
(
	std::shared_ptr<curveList>&& theCurves
)
	: theCurves_(std::move(theCurves))
{
	// empty body
}

tnbLib::GModel_ParaWire::GModel_ParaWire
(
	const Standard_Integer theIndex,
	const word & theName,
	std::shared_ptr<curveList>&& theCurves
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theCurves_(std::move(theCurves))
{
	// empty body
}

Standard_Integer 
tnbLib::GModel_ParaWire::NbCurves() const
{
	return (Standard_Integer)theCurves_->size();
}

tnbLib::Entity2d_Box 
tnbLib::GModel_ParaWire::CalcBoundingBox() const
{
	auto b = GModel_Tools::CalcBoundingBox(*this);
	return std::move(b);
}

std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::GModel_ParaWire::Copy() const
{
	auto curves = std::make_shared<std::vector<std::shared_ptr<GModel_ParaCurve>>>();
	Debug_Null_Pointer(curves);

	curves->reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		auto c = x->Copy();
		curves->push_back(std::move(c));
	}
	auto wire = std::make_shared<GModel_ParaWire>(Index(), Name(), std::move(curves));
	return std::move(wire);
}

std::shared_ptr<tnbLib::GModel_ParaWire> 
tnbLib::GModel_ParaWire::Copy(const gp_Trsf2d & t) const
{
	auto curves = std::make_shared<std::vector<std::shared_ptr<GModel_ParaCurve>>>();
	Debug_Null_Pointer(curves);

	curves->reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		auto c = x->Copy(t);
		curves->push_back(std::move(c));
	}
	auto wire = std::make_shared<GModel_ParaWire>(Index(), Name(), std::move(curves));
	return std::move(wire);
}