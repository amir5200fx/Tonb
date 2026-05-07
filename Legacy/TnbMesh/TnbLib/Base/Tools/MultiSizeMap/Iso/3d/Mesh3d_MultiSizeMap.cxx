#include <Mesh3d_MultiSizeMap.hxx>

#include <GeoMesh3d_Background.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Standard_Real tnbLib::Mesh3d_MultiSizeMap::InterpolateAt
(
	const Pnt3d& theCoord
) const
{
#ifdef _DEBUG
	if (SizeMaps().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size map has been detected!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Standard_Real h = RealLast();
	for (const auto& x : SizeMaps())
	{
		Debug_Null_Pointer(x);
		auto hi = x->InterpolateAt(theCoord);
		if (hi < h) h = hi;
	}
	return h;
}

template<>
Standard_Real tnbLib::Mesh3d_MultiSizeMap::InterpolateAt
(
	const Pnt3d& theCoord,
	Standard_Boolean& theSense
) const
{
#ifdef _DEBUG
	if (SizeMaps().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size map has been detected!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	Standard_Real h = RealLast();
	theSense = Standard_False;
	for (const auto& x : SizeMaps())
	{
		Debug_Null_Pointer(x);
		Standard_Boolean sense;
		auto hi = x->InterpolateAt(theCoord, sense);
		if (NOT sense)
		{			
			return RealFirst();
		}
		if (hi < h) h = hi;
	}
	theSense = Standard_True;
	return h;
}

template<>
void tnbLib::Mesh3d_MultiSizeMap::ConnectTopology()
{
	for (const auto& x : this->SizeMaps())
	{
		Debug_Null_Pointer(x);
		x->ConnectTopology();
	}
}