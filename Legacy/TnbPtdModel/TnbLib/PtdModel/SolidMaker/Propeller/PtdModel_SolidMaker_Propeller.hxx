#pragma once
#ifndef _PtdModel_SolidMaker_Propeller_Header
#define _PtdModel_SolidMaker_Propeller_Header

#include <Global_Done.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropShape;

	namespace ptdModel
	{

		// Forward Declarations
		class Shape_PropBlades;
		class Shape_PropHub;

		class SolidMaker_Propeller
			: public Global_Done
		{

			/*Private Data*/

			std::shared_ptr<ptdModel::Shape_PropBlades> theBlades_;
			std::shared_ptr<ptdModel::Shape_PropHub> theHub_;

			std::shared_ptr<PtdModel_PropShape> theShape_;

		public:

			//- default constructor

			SolidMaker_Propeller()
			{}


			//- constructors

			SolidMaker_Propeller
			(
				const std::shared_ptr<ptdModel::Shape_PropBlades>& theBlades,
				const std::shared_ptr<ptdModel::Shape_PropHub>& theHub
			)
				: theBlades_(theBlades)
				, theHub_(theHub)
			{}

			SolidMaker_Propeller
			(
				std::shared_ptr<ptdModel::Shape_PropBlades>&& theBlades,
				std::shared_ptr<ptdModel::Shape_PropHub>&& theHub
			)
				: theBlades_(std::move(theBlades))
				, theHub_(std::move(theHub))
			{}


			//- public functions and operators

			const auto& Blades() const
			{
				return theBlades_;
			}

			const auto& Hub() const
			{
				return theHub_;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			TnbPtdModel_EXPORT void Perform();

			TnbPtdModel_EXPORT void LoadBlades(const std::shared_ptr<ptdModel::Shape_PropBlades>&);
			TnbPtdModel_EXPORT void LoadBlades(std::shared_ptr<ptdModel::Shape_PropBlades>&&);

			TnbPtdModel_EXPORT void LoadHub(const std::shared_ptr<ptdModel::Shape_PropHub>&);
			TnbPtdModel_EXPORT void LoadHub(std::shared_ptr<ptdModel::Shape_PropHub>&&);

		};
	}
}

#endif // !_PtdModel_SolidMaker_Propeller_Header
