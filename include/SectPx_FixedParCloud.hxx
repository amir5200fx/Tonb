#pragma once
#ifndef _SectPx_FixedParCloud_Header
#define _SectPx_FixedParCloud_Header

#include <SectPx_ParCloud.hxx>

namespace tnbLib
{

	class SectPx_FixedParCloud
		: public SectPx_ParCloud
	{

		/*Private Data*/

		std::vector<Standard_Real> theValues_;

	public:

		static const char* typeName_;

		explicit SectPx_FixedParCloud
		(
			std::vector<Standard_Real>&& x
		)
			: theValues_(std::move(x))
		{}

		SectPx_FixedParCloud
		(
			const Standard_Integer theIndex, 
			std::vector<Standard_Real>&& x
		)
			: SectPx_ParCloud(theIndex)
			, theValues_(std::move(x))
		{}

		SectPx_FixedParCloud
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<Standard_Real>&& x
		)
			: SectPx_ParCloud(theIndex, theName)
			, theValues_(std::move(x))
		{}

		const auto& Xs() const
		{
			return theValues_;
		}

		auto& Xs()
		{
			return theValues_;
		}

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsFixed() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		std::vector<Standard_Real> Values() const override;

		void SetValue(std::vector<Standard_Real>&& x);
	};
}

#endif // !_SectPx_FixedParCloud_Header
