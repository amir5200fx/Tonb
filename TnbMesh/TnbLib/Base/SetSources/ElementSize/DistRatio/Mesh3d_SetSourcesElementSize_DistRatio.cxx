#include <Mesh3d_SetSourcesElementSize_DistRatio.hxx>

#include <Mesh3d_SizeMapTool.hxx>
#include <Mesh3d_ReferenceValues.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::Mesh3d_SetSourcesElementSize_DistRatio::CalcElementSize
(
	const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap,
	const Standard_Real theRadius,
	const Pnt3d & theCoord, 
	const Pnt3d & theSource
) const
{
	Debug_Null_Pointer(theSizeMap);

	const auto elemSize = theSizeMap->GetTargetSurfaceSize();
	const auto& refValues = theSizeMap->ReferenceValues();

	return CalcElementSize(refValues->BaseSize(), elemSize, theRadius, theCoord, theSource);
}

Standard_Real 
tnbLib::Mesh3d_SetSourcesElementSize_DistRatio::CalcElementSize
(
	const Standard_Real theBase,
	const Standard_Real theTarget, 
	const Standard_Real theRadius,
	const Pnt3d & theSource,
	const Pnt3d & theCoord
)
{
	if (theRadius < gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< " Invalid radius has been detected" << endl
			<< " - Radius: " << theRadius << endl
			<< abort(FatalError);
	}
	const auto dH = theBase - theTarget;
	if (dH < 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid target size has been detected." << endl
			<< " - Base: " << theBase << endl
			<< " - Target: " << theTarget << endl
			<< abort(FatalError);
	}
	const auto dis = theSource.Distance(theCoord);
	return (dis / theRadius)*dH + theTarget;
}