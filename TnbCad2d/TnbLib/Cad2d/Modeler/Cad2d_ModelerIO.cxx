#include <Cad2d_Modeler.hxx>

DECLARE_SAVE_IMP(tnbLib::Cad2d_Modeler)
{
	ar & boost::serialization::base_object<cad2dLib::Modeler_SrchEng>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Counter>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Plane>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Registry>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Segments>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Cad2d_Modeler)
{
	ar & boost::serialization::base_object<cad2dLib::Modeler_SrchEng>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Counter>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Plane>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Registry>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Segments>(*this);
}