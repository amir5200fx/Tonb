#pragma once
#ifndef _ShapePx_ArcSectionIterInfo_Header
#define _ShapePx_ArcSectionIterInfo_Header

#include <NumAlg_Secant_Info.hxx>
#include <NumAlg_FalsePos_Info.hxx>

#include <memory>

namespace tnbLib
{

	class ShapePx_ArcSectionIterInfo
	{

		/*Private Data*/

	protected:

		//- default constructor

		ShapePx_ArcSectionIterInfo()
		{}


		//- constructors

	public:

		virtual ~ShapePx_ArcSectionIterInfo()
		{}

	};

	class ShapePx_ArcSectionIterInfo_FalsePos
		: public ShapePx_ArcSectionIterInfo
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_FalsePos_Info> theInfo_;

	public:

		//- constructors

		ShapePx_ArcSectionIterInfo_FalsePos(const std::shared_ptr<NumAlg_FalsePos_Info>& theInfo)
			: theInfo_(theInfo)
		{}

		const auto& Info() const
		{
			return theInfo_;
		}
	};

	class ShapePx_ArcSectionIterInfo_Secant
		: public ShapePx_ArcSectionIterInfo
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_Secant_Info> theInfo_;

	public:

		//- constructors

		ShapePx_ArcSectionIterInfo_Secant(const std::shared_ptr<NumAlg_Secant_Info>& theInfo)
			: theInfo_(theInfo)
		{}

		const auto& Info() const
		{
			return theInfo_;
		}
	};
}

#endif // !_ShapePx_ArcSectionIterInfo_Header
