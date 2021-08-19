#pragma once
#ifndef _PtdModel_SolidMaker_PropBlades_Header
#define _PtdModel_SolidMaker_PropBlades_Header

#include <Global_Done.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations

	namespace ptdModel
	{

		// Forward Declarations

		class Shape_PropBlades;
		class Shape_PropBladeParent;

		class SolidMaker_PropBlades
			: public Global_Done
		{

			/*Private Data*/

			Standard_Integer theNbBlades_;

			std::shared_ptr<Shape_PropBladeParent> theBlade_;

			std::shared_ptr<Shape_PropBlades> theShape_;

		public:


			static TnbPtdModel_EXPORT Standard_Integer DEFAULT_NB_BLADES;

			//- default constructor

			SolidMaker_PropBlades()
				: theNbBlades_(DEFAULT_NB_BLADES)
			{}


			//- constructors

			SolidMaker_PropBlades
			(
				const Standard_Integer theNbBlades, 
				const std::shared_ptr<Shape_PropBladeParent>& theBlade
			)
				: theNbBlades_(theNbBlades)
				, theBlade_(theBlade)
			{}

			SolidMaker_PropBlades
			(
				const Standard_Integer theNbBlades,
				std::shared_ptr<Shape_PropBladeParent>&& theBlade
			)
				: theNbBlades_(theNbBlades)
				, theBlade_(std::move(theBlade))
			{}


			//- public functions and operators

			auto NbBlades() const
			{
				return theNbBlades_;
			}

			const auto& Blade() const
			{
				return theBlade_;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			TnbPtdModel_EXPORT void Perform();

			void SetNbBaldes(const Standard_Integer n)
			{
				theNbBlades_ = n;
			}

			void LoadBlade(const std::shared_ptr<Shape_PropBladeParent>& theBlade)
			{
				theBlade_ = theBlade;
			}

			void LoadBlade(std::shared_ptr<Shape_PropBladeParent>&& theBlade)
			{
				theBlade_ = std::move(theBlade);
			}

		};
	}
}

#endif // !_PtdModel_SolidMaker_PropBlades_Header
