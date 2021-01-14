#include <SectPx_CurveQ.hxx>

#include <SectPx_Poles.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SectPx_CurveQ::CheckPole(const std::shared_ptr<SectPx_Pole>& thePole, const char * name)
{
	if (thePole->IsInterior())
	{
		auto interior = std::dynamic_pointer_cast<SectPx_InterPole>(thePole);
		Debug_Null_Pointer(interior);

		if (interior->IsCorner())
		{
			FatalErrorIn(FunctionSIG)
				<< "no corner pole is not permitted to be an end point of a curve" << endl
				<< abort(FatalError);
		}
	}
}

const char* tnbLib::SectPx_CurveQ::typeName_ = "curveQ";

tnbLib::SectPx_CurveQ::SectPx_CurveQ
(
	const Standard_Integer theIndex,
	const word & theName
)
	: SectPx_RegObj(theIndex, theName)
{
	// empty body
}

tnbLib::SectPx_CurveQ::SectPx_CurveQ
(
	const std::shared_ptr<SectPx_Pole>& thePole0,
	const std::shared_ptr<SectPx_Pole>& thePole1
)
	: thePole0_(thePole0)
	, thePole1_(thePole1)
{
	CheckPole(Pole0(), FunctionSIG);
	CheckPole(Pole1(), FunctionSIG);
}

tnbLib::SectPx_CurveQ::SectPx_CurveQ
(
	const Standard_Integer theIndex,
	const word & theName, 
	const std::shared_ptr<SectPx_Pole>& thePole0,
	const std::shared_ptr<SectPx_Pole>& thePole1
)
	: SectPx_RegObj(theIndex, theName)
	, thePole0_(thePole0)
	, thePole1_(thePole1)
{
	CheckPole(Pole0(), FunctionSIG);
	CheckPole(Pole1(), FunctionSIG);
}

tnbLib::word 
tnbLib::SectPx_CurveQ::RegObjTypeName() const
{
	return typeName_;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_CurveQ::RegObjType() const
{
	return sectPxLib::regObjType::curveQ;
}

Standard_Boolean 
tnbLib::SectPx_CurveQ::IsCurveQ() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_CurveQ::IsFrameRegObj() const
{
	return Standard_True;
}

void tnbLib::SectPx_CurveQ::LoadPole0
(
	const std::shared_ptr<SectPx_Pole>& thePole
)
{
	thePole0_ = thePole;
	CheckPole(Pole0(), FunctionSIG);
}

void tnbLib::SectPx_CurveQ::LoadPole1
(
	const std::shared_ptr<SectPx_Pole>& thePole
)
{
	thePole1_ = thePole;
	CheckPole(Pole1(), FunctionSIG);
}