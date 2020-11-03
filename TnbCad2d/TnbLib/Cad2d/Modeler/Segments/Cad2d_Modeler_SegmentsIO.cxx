#include <Cad2d_Modeler_Segments.hxx>

#include <Cad2d_Modeler_Segment.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Segments)
{
	ar & Segments();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Segments)
{
	ar & ChangeSegments();
}