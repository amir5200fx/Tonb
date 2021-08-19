#include <PtdModel_Shape_PropBlades.hxx>

#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_Shape_PropBladeChild.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::ptdModel::Shape_PropBlades::CheckParent
(
	const std::shared_ptr<Shape_PropBlade>& theBlade
)
{
	if (NOT std::dynamic_pointer_cast<Shape_PropBladeParent>(theBlade))
	{
		FatalErrorIn(FunctionSIG)
			<< "the blade is not parent!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::ptdModel::Shape_PropBlades::CheckChild
(
	const std::shared_ptr<Shape_PropBlade>& theBlade
)
{
	if (NOT std::dynamic_pointer_cast<Shape_PropBladeChild>(theBlade))
	{
		FatalErrorIn(FunctionSIG)
			<< "the blade is not child!" << endl
			<< abort(FatalError);
	}
}


tnbLib::ptdModel::Shape_PropBlades::Shape_PropBlades
(
	const std::shared_ptr<Shape_PropBlade>& theParent,
	const std::vector<std::shared_ptr<Shape_PropBlade>>& theChildren
)
	: theParent_(theParent)
	, theChildren_(theChildren)
{
	CheckParent(Parent());

	for (const auto& x : Children())
	{
		Debug_Null_Pointer(x);
		CheckChild(x);
	}
}

tnbLib::ptdModel::Shape_PropBlades::Shape_PropBlades
(
	std::shared_ptr<Shape_PropBlade>&& theParent,
	std::vector<std::shared_ptr<Shape_PropBlade>>&& theChildren
)
	: theParent_(std::move(theParent))
	, theChildren_(std::move(theChildren))
{
	CheckParent(Parent());

	for (const auto& x : Children())
	{
		Debug_Null_Pointer(x);
		CheckChild(x);
	}
}

Standard_Integer 
tnbLib::ptdModel::Shape_PropBlades::NbBlades() const
{
	return (Standard_Integer)theChildren_.size() + 1;
}

void tnbLib::ptdModel::Shape_PropBlades::SetParent
(
	const std::shared_ptr<Shape_PropBlade>& theBlade
)
{
	theParent_ = theBlade;
	CheckParent(Parent());
}

void tnbLib::ptdModel::Shape_PropBlades::SetParent
(
	std::shared_ptr<Shape_PropBlade>&& theBlade
)
{
	theParent_ = std::move(theBlade);
	CheckParent(Parent());
}

void tnbLib::ptdModel::Shape_PropBlades::SetChildren
(
	const std::vector<std::shared_ptr<Shape_PropBlade>>& theBlades
)
{
	theChildren_ = theBlades;
	for (const auto& x : Children())
	{
		Debug_Null_Pointer(x);
		CheckChild(x);
	}
}

void tnbLib::ptdModel::Shape_PropBlades::SetChildren
(
	std::vector<std::shared_ptr<Shape_PropBlade>>&& theBlades
)
{
	theChildren_ = std::move(theBlades);
	for (const auto& x : Children())
	{
		Debug_Null_Pointer(x);
		CheckChild(x);
	}
}