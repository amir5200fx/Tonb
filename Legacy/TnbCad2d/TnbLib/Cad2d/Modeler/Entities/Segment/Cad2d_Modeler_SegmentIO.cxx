#include <Cad2d_Modeler_Segment.hxx>

#include <Cad2d_Modeler_Corner.hxx>
#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Segment)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);

	ar & Crn0();
	ar & Crn1();
	ar & Edges();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Segment)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);

	ar & ChangeCrn0();
	ar & ChangeCrn1();
	ar & ChangeEdges();
}

TNB_SAVE_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Ring)
{
	ar & boost::serialization::base_object<Modeler_Segment>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::cad2dLib::Modeler_Ring)
{
	ar & boost::serialization::base_object<Modeler_Segment>(*this);
}