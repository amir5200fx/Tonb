#include <Marine_Body_Tank.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Tank>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Tank>);

#include <Marine_Shape.hxx>

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		template<>
		void BodyConstructor_Shape<Body_Tank>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Body_Tank>(*this);
			ar & theShape_;
		}

		template<>
		template<>
		void BodyConstructor_Shape<Body_Tank>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Body_Tank>(*this);
			ar & theShape_;
		}
	}
}