#include <Cad2d_Modeler_CornerAdaptor.hxx>

#include <Cad2d_Modeler_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_CornerAdaptor)
{
	ar & Segments();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_CornerAdaptor)
{
	ar & ChangeSegments();
}