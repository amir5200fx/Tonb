#include <Aft2d_OptNodeSurface_Calculator.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft2d_OptNodeSurface_Calculator::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);
		ar & boost::serialization::base_object<Global_Done>(*this);

		//ar & theFront_;
		//ar & theMetricMap_;

		//ar & theSize_;

		//ar & theCoord_;

		//ar & IsConverged_;
	}

	template<>
	template<>
	void Aft2d_OptNodeSurface_Calculator::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & boost::serialization::base_object<Global_Indexed>(*this);
		ar & boost::serialization::base_object<Global_Named>(*this);
		ar & boost::serialization::base_object<Global_Done>(*this);

		//ar & theFront_;
		//ar & theMetricMap_;

		//ar & theSize_;

		//ar & theCoord_;

		//ar & IsConverged_;
	}
}