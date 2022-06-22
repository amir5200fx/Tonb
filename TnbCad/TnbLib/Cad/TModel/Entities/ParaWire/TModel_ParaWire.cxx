#include <TModel_ParaWire.hxx>

#include <TModel_ParaCurve.hxx>
#include <TModel_Tools.hxx>
#include <Entity2d_Box.hxx>

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const std::shared_ptr<curveList>& theCurves
)
	: theCurves_(theCurves)
{
	// empty body [6/21/2022 Amir]
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	std::shared_ptr<curveList>&& theCurves
)
	: theCurves_(std::move(theCurves))
{
	// empty body [6/21/2022 Amir]
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const Standard_Integer theIndex,
	const std::shared_ptr<curveList>& theCurves
)
	: Global_Indexed(theIndex)
	, theCurves_(theCurves)
{
	// empty body [6/21/2022 Amir]
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const Standard_Integer theIndex,
	const word& theName,
	const std::shared_ptr<curveList>& theCurves
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theCurves_(theCurves)
{
	// empty body [6/21/2022 Amir]
}

tnbLib::TModel_ParaWire::TModel_ParaWire
(
	const Standard_Integer theIndex, 
	const word & theName, 
	std::shared_ptr<curveList>&& theCurves
)
	: Global_Indexed(theIndex)
	, Global_Named(theName)
	, theCurves_(std::move(theCurves))
{
	// empty body [6/21/2022 Amir]
}

Standard_Integer
tnbLib::TModel_ParaWire::NbCurves() const
{
	Debug_Null_Pointer(theCurves_);
	return (Standard_Integer)theCurves_->size();
}

Standard_Integer 
tnbLib::TModel_ParaWire::NbEdges() const
{
	Debug_Null_Pointer(theCurves_);
	return (Standard_Integer)theCurves_->size();
}

tnbLib::Entity2d_Box
tnbLib::TModel_ParaWire::CalcBoundingBox() const
{
	auto b = TModel_Tools::CalcBoundingBox(*this);
	return std::move(b);
}

std::shared_ptr<tnbLib::TModel_ParaWire>
tnbLib::TModel_ParaWire::Copy() const
{
	auto curves = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>();
	Debug_Null_Pointer(curves);

	curves->reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		auto c = x->Copy();
		curves->push_back(std::move(c));
	}
	auto wire = std::make_shared<TModel_ParaWire>(Index(), Name(), std::move(curves));
	return std::move(wire);
}

std::shared_ptr<tnbLib::TModel_ParaWire>
tnbLib::TModel_ParaWire::Copy(const gp_Trsf2d & t) const
{
	auto curves = std::make_shared<std::vector<std::shared_ptr<TModel_ParaCurve>>>();
	Debug_Null_Pointer(curves);

	curves->reserve(NbCurves());
	for (const auto& x : Curves())
	{
		Debug_Null_Pointer(x);
		auto c = x->Copy(t);
		curves->push_back(std::move(c));
	}
	auto wire = std::make_shared<TModel_ParaWire>(Index(), Name(), std::move(curves));
	return std::move(wire);
}