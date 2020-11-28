#include <Marine_WaterDomain.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Water.hxx>
#include <Marine_Wave.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_WaterDomain)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWater_;
	ar & theWave_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_WaterDomain)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWater_;
	ar & theWave_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Marine_WaterDomain);