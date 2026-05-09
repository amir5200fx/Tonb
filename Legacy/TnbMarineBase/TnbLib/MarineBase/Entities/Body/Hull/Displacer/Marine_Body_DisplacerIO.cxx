#include <Marine_Body_Displacer.hxx>

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_Shape<tnbLib::marineLib::Body_Displacer>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::BodyConstructor_noShape<tnbLib::marineLib::Body_Displacer>);

#include <Marine_Shape.hxx>

namespace tnbLib
{
	namespace marineLib
	{

		template<>
		template<>
		void BodyConstructor_Shape<Body_Displacer>::serialize<TNB_iARCH_TYPE>
			(
				TNB_iARCH_TYPE& ar, 
				const unsigned int file_vertion
				)
		{
			ar & boost::serialization::base_object<Body_Displacer>(*this);
			ar & theShape_;
			ar & IsSymmetric_;
		}

		template<>
		template<>
		void BodyConstructor_Shape<Body_Displacer>::serialize<TNB_oARCH_TYPE>
			(
				TNB_oARCH_TYPE& ar, 
				const unsigned int file_vertion
				)
		{			
			ar & boost::serialization::base_object<Body_Displacer>(*this);		
			ar & theShape_;		
			ar & IsSymmetric_;
		}
	}
}