#pragma once
#ifndef _Cad_tModelMaker_PairCrvCriterion_Header
#define _Cad_tModelMaker_PairCrvCriterion_Header

#include <Standard_TypeDef.hxx>
//#include <Standard_Handle.hxx>

#include <Global_Serialization.hxx>
#include <Cad_Module.hxx>

#include <memory>

// Forward Declarations [1/7/2022 Amir]
//class Geom_Curve;

namespace tnbLib
{

	// Forward Declarations [1/7/2022 Amir]
	class TModel_Curve;

	class Cad_tModelMaker_PairCrvCriterion
	{

		/*Private Data*/


		// private functions and operators [1/7/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [1/7/2022 Amir]
		}

	protected:

		// default constructor [1/7/2022 Amir]

		Cad_tModelMaker_PairCrvCriterion()
		{}

		// constructors [1/7/2022 Amir]

	public:

		virtual ~Cad_tModelMaker_PairCrvCriterion()
		{}

		// public functions and operators [1/7/2022 Amir]

		virtual Standard_Boolean 
			ArePaired
			(
				const std::shared_ptr<TModel_Curve>& theCurve0,
				const std::shared_ptr<TModel_Curve>& theCurve1
			) const = 0;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tModelMaker_PairCrvCriterion);

#endif // !_Cad_tModelMaker_PairCrvCriterion_Header
