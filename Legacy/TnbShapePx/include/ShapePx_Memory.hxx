#pragma once
#ifndef _ShapePx_Memory_Header
#define _ShapePx_Memory_Header

#include <ShapePx_Entity.hxx>
#include <Geo_ItemCounter.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_ScatterRegistry;
	class SectPx_CountRegistry;
	class SectPx_ParRegistry;
	class SectPx_FrameRegistry;

	class ShapePx_Memory
		: public ShapePx_Entity
	{

		/*Private Data*/

		mutable Geo_ItemCounter theFrameCounter_;

		std::shared_ptr<SectPx_CountRegistry> theCounter_;
		std::shared_ptr<SectPx_ScatterRegistry> theScatter_;
		std::shared_ptr<SectPx_ParRegistry> theParRegistry_;

		std::map<Standard_Integer, std::shared_ptr<SectPx_FrameRegistry>> theFrames_;


		//- private functions and operators

		auto& FrameCounter() const
		{
			return theFrameCounter_;
		}

	public:

		ShapePx_Memory()
		{}

		ShapePx_Memory(const Standard_Integer theIndex, const word& theName);


		const auto& Counter() const
		{
			return theCounter_;
		}

		const auto& Scatter() const
		{
			return theScatter_;
		}

		const auto& ParRegistry() const
		{
			return theParRegistry_;
		}

		Standard_Integer NewFrame();

		std::shared_ptr<SectPx_FrameRegistry> SelectFrame(const Standard_Integer theIndex) const;

		std::shared_ptr<SectPx_FrameRegistry> RemoveFrame(const Standard_Integer theIndex);
	};
}

#endif // !_ShapePx_Memory_Header
