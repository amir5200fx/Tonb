#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class gCurveType, class MetricPrcsrType>
inline Standard_Real 
tnbLib::Mesh_CurveOptmPoint_BisectCorrection<gCurveType, MetricPrcsrType>::Mesh_CurveOptmPoint_BisectCorrection_Function::Value
(
	const Standard_Real x
) const
{
	const auto& map = theCurve_.SizeMap();
	const auto& curve = theCurve_.Curve();

	auto P0 = curve.Value(theU0_);
	return map.CalcUnitDistance(P0, curve.Value(x)) / theLen_ - 1.0;
}

template<class gCurveType, class MetricPrcsrType>
inline void tnbLib::Mesh_CurveOptmPoint_BisectCorrection<gCurveType, MetricPrcsrType>::Perform()
{
	Mesh_CurveOptmPoint_BisectCorrection_Function bisectFunc(Entity(), U0(), Len());
	typedef NumAlg_BisectionSolver<Mesh_CurveOptmPoint_BisectCorrection_Function, true> bisectAlgType;

	bisectAlgType bisectAlg(bisectFunc, *this->Info());
	bisectAlg.Perform(this->Guess0(), this->Guess1());

	Debug_If_Condition_Message(NOT bisectAlg.IsDone(), "the application is not performed!");

	this->CorrectedRef() = MEAN(this->Info()->X0(), this->Info()->X1());
	Change_IsDone() = Standard_True;
}