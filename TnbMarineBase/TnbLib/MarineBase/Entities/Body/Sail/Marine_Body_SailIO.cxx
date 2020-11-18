#include <Marine_Body_Sail.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Sail>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Sail>);

#include <Marine_Shape.hxx>

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		template<>
		void BodyConstructor_Shape<Body_Sail>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Marine_Body>(*this);
			ar & theShape_;
		}

		template<>
		template<>
		void BodyConstructor_Shape<Body_Sail>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar,
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Marine_Body>(*this);
			ar & theShape_;
		}
	}
}