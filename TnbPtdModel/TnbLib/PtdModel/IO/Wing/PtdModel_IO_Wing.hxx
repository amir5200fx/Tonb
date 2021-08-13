#pragma once
#ifndef _PtdModel_IO_Wing_Header
#define _PtdModel_IO_Wing_Header

#include <Global_Serialization.hxx>
#include <PtdModel_Module.hxx>

#include <gp_Ax2.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_Face;

	namespace ptdModel
	{

		namespace io
		{

			class Wing
			{

				/*Private Data*/

				std::shared_ptr<PtdModel_Face> theUpper_;
				std::shared_ptr<PtdModel_Face> theLower_;

				gp_Ax2 theSystem_;


				//- private functions and operators

				TNB_SERIALIZATION(TnbPtdModel_EXPORT);

			public:

				//- default constructor

				Wing()
				{}


				//- constructors


				//- public functions and operators

				const auto& Upper() const
				{
					return theUpper_;
				}

				const auto& Lower() const
				{
					return theLower_;
				}

				const auto& Ax() const
				{
					return theSystem_;
				}

				void SetUpper(const std::shared_ptr<PtdModel_Face>& theFace)
				{
					theUpper_ = theFace;
				}

				void SetLower(const std::shared_ptr<PtdModel_Face>& theFace)
				{
					theLower_ = theFace;
				}

				void SetAx(const gp_Ax2& ax)
				{
					theSystem_ = ax;
				}
			};
		}
	}
}

#endif // !_PtdModel_IO_Wing_Header
