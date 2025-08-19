#include <SectPx_CurveQMaker.hxx>

#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Poles.hxx>
#include <SectPx_CurveQ.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::SectPx_Pole> 
tnbLib::maker::CurveQ::SelectBoundary
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto pole = std::dynamic_pointer_cast<SectPx_Pole>(item);
	if (NOT pole)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pole> SelectPole(const Standard_Integer theIndex) const")
			<< "the item is not a pole!" << endl
			<< abort(FatalError) << endl;
	}
	if (NOT pole->IsBoundary())
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pole> SelectPole(const Standard_Integer theIndex) const")
			<< "the pole is not boundary!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(pole);
}

std::shared_ptr<tnbLib::SectPx_Pole> 
tnbLib::maker::CurveQ::SelectSlider
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto pole = std::dynamic_pointer_cast<SectPx_Pole>(item);
	if (NOT pole)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pole> SelectPole(const Standard_Integer theIndex) const")
			<< "the item is not a pole!" << endl
			<< abort(FatalError) << endl;
	}
	if (NOT std::dynamic_pointer_cast<sectPxLib::Pole_Slider>(pole))
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pole> SelectPole(const Standard_Integer theIndex) const")
			<< "the pole is not slider!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(pole);
}

std::shared_ptr<tnbLib::SectPx_CurveQ> 
tnbLib::maker::CurveQ::SelectCurve
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->SelectObj(theIndex);
	Debug_Null_Pointer(item);

	auto curve = std::dynamic_pointer_cast<SectPx_CurveQ>(item);
	if (NOT curve)
	{
		FatalErrorIn("std::shared_ptr<SectPx_Pole> SelectPole(const Standard_Integer theIndex) const")
			<< "the item is not a curve!" << endl
			<< abort(FatalError) << endl;
	}
	return std::move(curve);
}

Standard_Integer 
tnbLib::maker::CurveQ::CreateCurve
(
	const std::shared_ptr<SectPx_Pole>& thePole0,
	const std::shared_ptr<SectPx_Pole>& thePole1
)
{
	auto item = std::make_shared<SectPx_CurveQ>(thePole0, thePole1);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(item);

	return id;
}

Standard_Integer 
tnbLib::maker::CurveQ::CreateCurve
(
	const word & name, 
	const std::shared_ptr<SectPx_Pole>& thePole0, 
	const std::shared_ptr<SectPx_Pole>& thePole1
)
{
	auto item = std::make_shared<SectPx_CurveQ>(0, name, thePole0, thePole1);
	Debug_Null_Pointer(item);

	Debug_Null_Pointer(Registry());
	const auto id = Registry()->Import(item);

	return id;
}