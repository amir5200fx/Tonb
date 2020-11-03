#include <Cad2d_Modeler_CornerAdaptor.hxx>

#include <Cad2d_Modeler_Segment.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_CornerAdaptor)
{
	ar & Segments();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_CornerAdaptor)
{
	ar & ChangeSegments();
}