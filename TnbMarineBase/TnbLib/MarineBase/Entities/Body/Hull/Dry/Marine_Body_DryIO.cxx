#include <Marine_Body_Dry.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Dry>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Dry>);

#include <Marine_Shape.hxx>

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		template<>
		void BodyConstructor_Shape<Body_Dry>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Marine_HullBody>(*this);
			ar & theShape_;
		}

		template<>
		template<>
		void BodyConstructor_Shape<Body_Dry>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Marine_HullBody>(*this);
			ar & theShape_;
		}
	}
}