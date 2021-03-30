#include <TModel_EdgeAdaptor.hxx>

#include <TModel_Surface.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Wire.hxx>
#include <TModel_Edge.hxx>

#include <TopoDS.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_EdgeAdaptor)
{
	ar & theSurface_;
	ar & thePaired_;
	ar & theWire_;
	ar & thePairedEdge_;

	//TopoDS_Shape sh = theTEdge_;
	//ar & sh;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_EdgeAdaptor)
{
	ar & theSurface_;
	ar & thePaired_;
	ar & theWire_;
	ar & thePairedEdge_;

	//TopoDS_Shape sh;
	//ar & sh;

	//theTEdge_ = TopoDS::Edge(sh);
}