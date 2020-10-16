#pragma once
#ifndef _SectPx_ConstParCloud_Header
#define _SectPx_ConstParCloud_Header

#include <SectPx_ParCloud.hxx>
#include <SectPx_Values.hxx>

namespace tnbLib
{

	class SectPx_ConstParCloud
		: public SectPx_ParCloud
	{

		/*Private Data*/

		realValues theValues_;

	public:

		static const char* typeName_;

		explicit SectPx_ConstParCloud(realValues&& theValues)
			: theValues_(std::move(theValues))
		{}

		SectPx_ConstParCloud
		(
			const Standard_Integer theIndex,
			realValues&& theValues
		)
			: SectPx_ParCloud(theIndex)
			, theValues_(std::move(theValues))
		{}

		SectPx_ConstParCloud
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			realValues&& theValues
		)
			: SectPx_ParCloud(theIndex, theName)
			, theValues_(std::move(theValues))
		{}

		const auto& Xs() const
		{
			return theValues_;
		}

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsConstant() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		realValues Values() const override;

		void SetValue(realValues&& x);
	};
}

#endif // !_SectPx_ConstParCloud_Header
