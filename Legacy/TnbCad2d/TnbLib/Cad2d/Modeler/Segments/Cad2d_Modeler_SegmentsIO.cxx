#include <Cad2d_Modeler_Segments.hxx>

#include <Cad2d_Modeler_Segment.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Segments)
{
	ar & Segments();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Segments)
{
	ar & ChangeSegments();
}