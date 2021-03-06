#include <Cad2d_Modeler.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_Modeler)
{
	if (verbose)
	{
		Info << " - saving the engine..." << endl;
	}
	ar & boost::serialization::base_object<cad2dLib::Modeler_SrchEng>(*this);
	if (verbose)
	{
		Info << " - saving the counter..." << endl;
	}
	ar & boost::serialization::base_object<cad2dLib::Modeler_Counter>(*this);
	if (verbose)
	{
		Info << " - saving the planes..." << endl;
	}
	ar & boost::serialization::base_object<cad2dLib::Modeler_Plane>(*this);
	if (verbose)
	{
		Info << " - saving the registry..." << endl;
	}
	ar & boost::serialization::base_object<cad2dLib::Modeler_Registry>(*this);
	if (verbose)
	{
		Info << " - saving the segments..." << endl;
	}
	ar & boost::serialization::base_object<cad2dLib::Modeler_Segments>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_Modeler)
{
	ar & boost::serialization::base_object<cad2dLib::Modeler_SrchEng>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Counter>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Plane>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Registry>(*this);
	ar & boost::serialization::base_object<cad2dLib::Modeler_Segments>(*this);
}