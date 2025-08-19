#pragma once
#ifndef _PtdModel_SolidMaker_Wing_Header
#define _PtdModel_SolidMaker_Wing_Header

#include <Global_Done.hxx>
#include <PtdModel_IO_WingFwd.hxx>

#include <memory>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Wing;

	namespace ptdModel
	{

		class SolidMaker_Wing
			: public Global_Done
		{

			/*Private Data*/

			std::shared_ptr<ptdModel::io::Wing> theWing_;

			TopoDS_Shape theShape_;

			Standard_Boolean trimmed_;

		protected:


			//- default constructor

			SolidMaker_Wing()
				: trimmed_(Standard_False)
			{}


			//- constructors

			SolidMaker_Wing(const std::shared_ptr<ptdModel::io::Wing>& theWing)
				: theWing_(theWing)
				, trimmed_(Standard_False)
			{}


			//- protected functions and operators

			void SetShape(const TopoDS_Shape& theShape)
			{
				theShape_ = theShape;
			}

			void SetShape(TopoDS_Shape&& theShape)
			{
				theShape_ = std::move(theShape);
			}

		public:


			//- public functions and operators

			auto Trimmed() const
			{
				return trimmed_;
			}

			const auto& Wing() const
			{
				return theWing_;
			}

			const auto& Shape() const
			{
				return theShape_;
			}

			virtual void Perform() = 0;

			void LaodWing(const std::shared_ptr<ptdModel::io::Wing>& theWing)
			{
				theWing_ = theWing;
			}

			void SetTrimmed(const Standard_Boolean t)
			{
				trimmed_ = t;
			}
		};
	}
}

#endif // !_PtdModel_SolidMaker_Wing_Header
