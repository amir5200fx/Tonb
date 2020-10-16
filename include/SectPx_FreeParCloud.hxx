#pragma once
#ifndef _SectPx_FreeParCloud_Header
#define _SectPx_FreeParCloud_Header

#include <SectPx_ParCloud.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FieldFun;

	class SectPx_FreeParCloud
		: public SectPx_ParCloud
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FieldFun> theFun_;


		auto& ChangeFun()
		{
			return theFun_;
		}

	public:

		static const char* typeName_;

		explicit SectPx_FreeParCloud
		(
			const std::shared_ptr<SectPx_FieldFun>& theFun
		)
			: theFun_(theFun)
		{}

		explicit SectPx_FreeParCloud
		(
			std::shared_ptr<SectPx_FieldFun>&& theFun
		)
			: theFun_(std::move(theFun))
		{}

		SectPx_FreeParCloud
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_FieldFun>& theFun
		)
			: SectPx_ParCloud(theIndex)
			, theFun_(theFun)
		{}

		SectPx_FreeParCloud
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_FieldFun>& theFun
		)
			: SectPx_ParCloud(theIndex, theName)
			, theFun_(theFun)
		{}


		const auto& FieldFun() const
		{
			return theFun_;
		}

		Standard_Boolean HasFieldFun() const;

		word RegObjTypeName() const override;

		sectPxLib::parType ParType() const override;

		Standard_Boolean IsFree() const override;

		Standard_Boolean IsComplete() const override;

		Standard_Boolean InCycle() const override;

		realValues Values() const override;

	};
}

#endif // !_SectPx_FreeParCloud_Header
