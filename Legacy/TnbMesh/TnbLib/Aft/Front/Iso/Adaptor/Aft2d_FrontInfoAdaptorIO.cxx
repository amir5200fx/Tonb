#include <Aft2d_FrontInfoAdaptor.hxx>

#include <Aft2d_Edge.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft2d_FrontInfoAdaptor::serialize<TNB_iARCH_TYPE>(TNB_iARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & thePaired0_;
		ar & thePaired1_;

		ar & theCreated0_;
		ar & theCreated1_;
	}

	template<>
	template<>
	void Aft2d_FrontInfoAdaptor::serialize<TNB_oARCH_TYPE>(TNB_oARCH_TYPE& ar, const unsigned int file_version)
	{
		ar & thePaired0_;
		ar & thePaired1_;

		ar & theCreated0_;
		ar & theCreated1_;
	}
}