#include <Cad2d_Modeler_Corner.hxx>

#include <Pln_Vertex.hxx>

DECLARE_SAVE_IMP(tnbLib::cad2dLib::Modeler_Corner)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);
	ar & boost::serialization::base_object<Modeler_CornerAdaptor>(*this);

	double radius = Radius();
	double tol = Tolerance();
	ar & Vertices();
	ar & radius;
	ar & tol;
	ar & Coord();
}

DECLARE_LOAD_IMP(tnbLib::cad2dLib::Modeler_Corner)
{
	ar & boost::serialization::base_object<Modeler_Entity>(*this);
	ar & boost::serialization::base_object<Modeler_CornerAdaptor>(*this);

	ar & ChangeVertices();
	ar & ChangeRadius();
	ar & ChangeTolerance();
	ar & ChangeCoord();
}