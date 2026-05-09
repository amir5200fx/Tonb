#include <Mesh3d_SetSourcesCalcRadius_GrowthRate.hxx>

#include <Mesh3d_ReferenceValues.hxx>
#include <Mesh3d_SizeMapTool.hxx>
#include <Mesh_VariationRateInfo.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Mesh3d_SetSourcesCalcRadius_GrowthRate::CalcRadius
(
	const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap
) const
{
	Debug_Null_Pointer(theSizeMap);

	const auto elemSize = theSizeMap->GetTargetSurfaceSize();

	const auto& refValues = theSizeMap->ReferenceValues();
	const auto& values = theSizeMap->MeshValues();
	const auto& conditions = theSizeMap->MeshConditions();

	Debug_Null_Pointer(refValues);
	if (conditions->CustomBoundaryGrowthRate())
		return CalcRadius(Mesh_VariationRate::Rate(values->BoundaryGrowthRate()), elemSize, refValues->BaseSize());
	else
		return CalcRadius(Mesh_VariationRate::Rate(refValues->BoundaryGrowthRate()), elemSize, refValues->BaseSize());
}

Standard_Real 
tnbLib::Mesh3d_SetSourcesCalcRadius_GrowthRate::CalcRadius
(
	const Standard_Real theGrowthRate, 
	const Standard_Real theTarget,
	const Standard_Real theBase
)
{
	const auto H = theBase - theTarget;
	if (H < 0.0)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid element size has been detected." << endl
			<< " - Target: " << theTarget << endl
			<< " - Base: " << theBase << endl
			<< abort(FatalError);
	}
	const auto theta = std::asin(theGrowthRate);
	return H / std::tan(theta);
}