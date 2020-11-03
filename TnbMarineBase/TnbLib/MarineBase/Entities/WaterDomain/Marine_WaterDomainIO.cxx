#include <Marine_WaterDomain.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Water.hxx>
#include <Marine_Wave.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_WaterDomain)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWater_;
	ar & theWave_;
}

DECLARE_LOAD_IMP(tnbLib::Marine_WaterDomain)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWater_;
	ar & theWave_;
}