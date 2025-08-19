#pragma once
#ifndef _ShapePx_CustomSpacing_Header
#define _ShapePx_CustomSpacing_Header

#include <ShapePx_Spacing.hxx>

namespace tnbLib
{

	//class ShapePx_CustomSpacing
	//	: public ShapePx_Spacing
	//{

	//	/*Private Data*/

	//	std::vector<Standard_Real> theXs_;

	//public:

	//	ShapePx_CustomSpacing()
	//	{}

	//	ShapePx_CustomSpacing
	//	(
	//		const std::vector<Standard_Real>& theXs
	//	)
	//		: theXs_(theXs)
	//	{}

	//	ShapePx_CustomSpacing
	//	(
	//		std::vector<Standard_Real>&& theXs
	//	)
	//		: theXs_(std::move(theXs))
	//	{}

	//	ShapePx_CustomSpacing
	//	(
	//		const Standard_Integer theIndex, 
	//		const word& theName, 
	//		const std::vector<Standard_Real>& theXs
	//	)
	//		: ShapePx_Spacing(theIndex, theName)
	//		, theXs_(theXs)
	//	{}

	//	ShapePx_CustomSpacing
	//	(
	//		const Standard_Integer theIndex, 
	//		const word& theName, 
	//		std::vector<Standard_Real>&& theXs
	//	)
	//		: ShapePx_Spacing(theIndex, theName)
	//		, theXs_(std::move(theXs))
	//	{}

	//	const auto& Xs() const
	//	{
	//		return theXs_;
	//	}

	//	Standard_Integer NbSections() const override
	//	{
	//		return (Standard_Integer)theXs_.size();
	//	}

	//	std::vector<Standard_Real> Sections() const override
	//	{
	//		return theXs_;
	//	}
	//};
}

#endif // !_ShapePx_CustomSpacing_Header
