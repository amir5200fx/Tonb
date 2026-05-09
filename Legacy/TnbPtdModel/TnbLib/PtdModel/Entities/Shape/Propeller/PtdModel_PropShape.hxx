#pragma once
#ifndef _PtdModel_PropShape_Header
#define _PtdModel_PropShape_Header

#include <PtdModel_Shape.hxx>

namespace tnbLib
{

	namespace ptdModel
	{
		
		//- Forward Declarations

		class Shape_PropBlades;
		class Shape_PropHub;
	}

	class PtdModel_PropShape
		: public PtdModel_Shape
	{

		/*private Data*/

		std::shared_ptr<ptdModel::Shape_PropBlades> theBlades_;
		std::shared_ptr<ptdModel::Shape_PropHub> theHub_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	public:


		//- default constructor

		PtdModel_PropShape()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_PropShape
		(
			const std::shared_ptr<ptdModel::Shape_PropHub>& theHub, 
			const std::shared_ptr<ptdModel::Shape_PropBlades>& theBlades
		);

		TnbPtdModel_EXPORT PtdModel_PropShape
		(
			std::shared_ptr<ptdModel::Shape_PropHub>&& theHub, 
			std::shared_ptr<ptdModel::Shape_PropBlades>&& theBlades
		);

		//- public functions and operators

		const auto& Blades() const
		{
			return theBlades_;
		}

		const auto& Hub() const
		{
			return theHub_;
		}

		TnbPtdModel_EXPORT void SetBlades(const std::shared_ptr<ptdModel::Shape_PropBlades>&);
		TnbPtdModel_EXPORT void SetBlades(std::shared_ptr<ptdModel::Shape_PropBlades>&&);

		TnbPtdModel_EXPORT void SetHub(const std::shared_ptr<ptdModel::Shape_PropHub>&);
		TnbPtdModel_EXPORT void SetHub(std::shared_ptr<ptdModel::Shape_PropHub>&&);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdModel_PropShape);

#endif // !_PtdModel_PropShape_Header
