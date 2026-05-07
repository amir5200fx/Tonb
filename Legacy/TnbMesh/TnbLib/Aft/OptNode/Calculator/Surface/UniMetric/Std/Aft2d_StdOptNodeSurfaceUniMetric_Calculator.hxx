#pragma once
#ifndef _Aft2d_StdOptNodeSurfaceUniMetric_Calculator_Header
#define _Aft2d_StdOptNodeSurfaceUniMetric_Calculator_Header

#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>

namespace tnbLib
{

	class Aft2d_StdOptNodeSurfaceUniMetric_Calculator
		: public Aft2d_OptNodeSurfaceUniMetric_Calculator
	{

		/*Private Data*/

		// private functions and operators [3/6/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Aft2d_OptNodeSurfaceUniMetric_Calculator>(*this);
		}

	public:

		// default constructor [3/6/2022 Amir]

		Aft2d_StdOptNodeSurfaceUniMetric_Calculator()
		{}


		// constructors [3/6/2022 Amir]


		// override functions and operators [3/6/2022 Amir]

		TnbMesh_EXPORT void Perform() override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_StdOptNodeSurfaceUniMetric_Calculator);

#endif // !_Aft2d_StdOptNodeSurfaceUniMetric_Calculator_Header
