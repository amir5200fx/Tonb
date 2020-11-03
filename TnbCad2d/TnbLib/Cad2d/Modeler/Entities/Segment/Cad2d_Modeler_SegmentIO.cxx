#include <Cad2d_Modeler_Segment.hxx>

#include <Cad2d_Modeler_Corner.hxx>
#include <Pln_Edge.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Segment)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);

	ar & Crn0();
	ar & Crn1();
	ar & Edges();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Segment)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);

	ar & ChangeCrn0();
	ar & ChangeCrn1();
	ar & ChangeEdges();
}

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Ring)
{
	ar & boost::serialization::base_object<Modeler_Segment>(*this);
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Ring)
{
	ar & boost::serialization::base_object<Modeler_Segment>(*this);
}