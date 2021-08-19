#pragma once
#ifndef _PtdModel_SolidMaker_PropHub_Header
#define _PtdModel_SolidMaker_PropHub_Header

#include <Global_Done.hxx>
#include <PtdModel_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Cad_Shape;
	class PtdModel_PropHub;

	namespace ptdModel
	{

		// Forward Declarations
		class Shape_PropHub;

		class SolidMaker_PropHub
			: public Global_Done
		{

			/*Private Data*/

			std::shared_ptr<PtdModel_PropHub> theHub_;

			std::shared_ptr<Shape_PropHub> theShape_;

			Standard_Real theTolerance_;


			void SetShape(std::shared_ptr<Shape_PropHub>&& theShape)
			{
				theShape_ = std::move(theShape);
			}

		public:

			static TnbPtdModel_EXPORT const Standard_Real DEFAULT_TOLERANCE;

			//- default constructor

			SolidMaker_PropHub()
				: theTolerance_(DEFAULT_TOLERANCE)
			{}


			//- constructors

			SolidMaker_PropHub(const std::shared_ptr<PtdModel_PropHub>& theHub)
				: theHub_(theHub)
				, theTolerance_(DEFAULT_TOLERANCE)
			{}

			SolidMaker_PropHub(std::shared_ptr<PtdModel_PropHub>&& theHub)
				: theHub_(std::move(theHub))
				, theTolerance_(DEFAULT_TOLERANCE)
			{}


			//- public functions and operators

			const auto& Hub() const
			{
				return theHub_;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			auto Tolerance() const
			{
				return theTolerance_;
			}

			TnbPtdModel_EXPORT void Perform();

			void LoadHub(const std::shared_ptr<PtdModel_PropHub>& theHub)
			{
				theHub_ = theHub;
			}

			void LoadHub(std::shared_ptr<PtdModel_PropHub>&& theHub)
			{
				theHub_ = std::move(theHub);
			}

			void SetTolerance(const Standard_Real tol)
			{
				theTolerance_ = tol;
			}

		};
	}
}

#endif // !_PtdModel_SolidMaker_PropHub_Header
