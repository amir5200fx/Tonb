#include <Cad_CharLength.hxx>

#include <Cad_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Surface.hxx>
#include <opencascade/Geom2d_Curve.hxx>

const std::shared_ptr<tnbLib::Cad_CharLength_Info> tnbLib::Cad_CharLength::DEFAULT_INFO =
std::make_shared<tnbLib::Cad_CharLength_Info>();

Standard_Real 
tnbLib::Cad_CharLength::CalcCharLengthU() const
{
	Debug_Null_Pointer(Domain());
	Debug_Null_Pointer(Patch());
	const auto& b = *Domain();

	const auto& P0 = b.P0();
	const auto& P1 = b.P1();

	const auto vmin = P0.Y();
	const auto vmax = P1.Y();

	const auto umin = P0.X();
	const auto du = (P1.X() - P0.X()) / (Standard_Real)AlgInfo()->NbU();
	auto maxLen = (Standard_Real)0;

	forThose(Index, 0, AlgInfo()->NbU())
	{
		auto x = umin + Index * du;

		Pnt2d Q0(x, vmin);
		Pnt2d Q1(x, vmax);

		auto line = Pln_CurveTools::MakeSegment(Q0, Q1);
		auto len = Cad_Tools::CalcLength(line, Patch(), AlgInfo()->IntegInfo());

		if (len > maxLen) maxLen = len;
	}
	return maxLen;
}

Standard_Real 
tnbLib::Cad_CharLength::CalcCharLengthV() const
{
	Debug_Null_Pointer(Domain());
	Debug_Null_Pointer(Patch());
	const auto& b = *Domain();

	const auto& P0 = b.P0();
	const auto& P1 = b.P1();

	const auto umin = P0.X();
	const auto umax = P1.X();

	const auto vmin = P0.Y();
	const auto dv = (P1.Y() - P0.Y()) / (Standard_Real)AlgInfo()->NbV();
	auto maxLen = (Standard_Real)0;

	forThose(Index, 0, AlgInfo()->NbV())
	{
		auto x = vmin + Index * dv;

		Pnt2d Q0(umin, x);
		Pnt2d Q1(umax, x);

		auto line = Pln_CurveTools::MakeSegment(Q0, Q1);
		auto len = Cad_Tools::CalcLength(line, Patch(), AlgInfo()->IntegInfo());

		if (len > maxLen) maxLen = len;
	}
	return maxLen;
}

void tnbLib::Cad_CharLength::Perform()
{
	Debug_Null_Pointer(Patch());
	Debug_Null_Pointer(AlgInfo());

	theLenU_ = CalcCharLengthU();
	theLenV_ = CalcCharLengthV();

	Change_IsDone() = Standard_True;
}