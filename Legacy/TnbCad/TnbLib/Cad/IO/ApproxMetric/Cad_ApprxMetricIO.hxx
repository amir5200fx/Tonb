#pragma once
#ifndef _Cad_ApprxMetricIO_Header
#define _Cad_ApprxMetricIO_Header

#include <Cad_Module.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations [4/8/2022 Amir]
	class Cad_Shape;
	class GModel_Surface;

	class Cad_ApprxMetricIO
	{

		/*Private Data*/

		// inputs [4/8/2022 Amir]
		std::shared_ptr<Cad_Shape> theModel_;

		// outputs [4/8/2022 Amir]
		std::map<Standard_Integer, std::shared_ptr<Entity2d_Triangulation>>
			theApprox_;


		// private functions and operators [4/8/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT const std::string extension;

		// default constructor [4/8/2022 Amir]

		Cad_ApprxMetricIO()
		{}


		// constructors [4/8/2022 Amir]


		// public functions and operators [4/8/2022 Amir]

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& Approx() const
		{
			return theApprox_;
		}

		auto& ApproxRef()
		{
			return theApprox_;
		}

		void SetModel(const std::shared_ptr<Cad_Shape>& theModel)
		{
			theModel_ = theModel;
		}

	};
}

#endif // !_Cad_ApprxMetricIO_Header
