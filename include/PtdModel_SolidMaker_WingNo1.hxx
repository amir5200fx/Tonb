#pragma once
#ifndef _PtdModel_SolidMaker_WingNo1_Header
#define _PtdModel_SolidMaker_WingNo1_Header

#include <PtdModel_SolidMaker_Wing.hxx>
#include <PtdModel_IO_Wing.hxx>

#include <TopoDS_Face.hxx>

namespace tnbLib
{

	namespace ptdModel
	{

		namespace solidMaker
		{

			class WingNo1
				: public SolidMaker_Wing
			{

				/*Private Data*/

				Standard_Boolean LeadingPatch_;
				Standard_Boolean TrailingPatch_;


				TopoDS_Face theLeading_;
				TopoDS_Face theTrailing_;
				TopoDS_Face theTip_;
				TopoDS_Face theRoot_;
				TopoDS_Face theUpper_;
				TopoDS_Face theLower_;

				Standard_Real theTolerance_;

			public:

				//- default constructor

				WingNo1();


				//- constructors



				//- public functions and operators

				auto Tolerance() const
				{
					return theTolerance_;
				}

				auto LeadingPatch() const
				{
					return LeadingPatch_;
				}

				auto TrailingPatch() const
				{
					return TrailingPatch_;
				}

				const auto& LeadingFace() const
				{
					return theLeading_;
				}

				const auto& TrailingFace() const
				{
					return theTrailing_;
				}

				const auto& TipFace() const
				{
					return theTip_;
				}

				const auto& RootFace() const
				{
					return theRoot_;
				}

				const auto& UpperFace() const
				{
					return theUpper_;
				}

				const auto& LowerFace() const
				{
					return theLower_;
				}

				void Perform() override;

				void SetLeadingPatch(const Standard_Boolean);
				void SetTrailingPatch(const Standard_Boolean);

				void SetTolerance(const Standard_Real);

				
			};
		}
	}
}

#endif // !_PtdModel_SolidMaker_WingNo1_Header
