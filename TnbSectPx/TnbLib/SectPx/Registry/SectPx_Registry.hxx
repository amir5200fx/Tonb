#pragma once
#ifndef _SectPx_Registry_Header
#define _SectPx_Registry_Header

#include <Global_Serialization.hxx>
#include <Geo_ItemCounter.hxx>
#include <SectPx_Module.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	//- Forward Declarations
	class SectPx_CountRegistry;
	class SectPx_ScatterRegistry;
	class SectPx_ParRegistry;
	class SectPx_FrameRegistry;
	class SectPx_ShapeRegistry;

	class SectPx_Registry
	{

		/*Private Data*/

		mutable Geo_ItemCounter theFrameCounter_;

		std::shared_ptr<SectPx_CountRegistry> theCounter_;
		std::shared_ptr<SectPx_ScatterRegistry> theScatter_;

		std::shared_ptr<SectPx_ParRegistry> theParameter_;
		std::shared_ptr<SectPx_ShapeRegistry> theShape_;
		std::map<Standard_Integer, std::shared_ptr<SectPx_FrameRegistry>> theFrames_;


		//- private functions and operators

		friend class boost::serialization::access;

		TNB_SERIALIZATION(TnbSectPx_EXPORT);


		auto& FrameCounter() const
		{
			return theFrameCounter_;
		}

		TnbSectPx_EXPORT void AllocateMemory();


	public:

		SectPx_Registry()
		{
			AllocateMemory();
		}

		auto NbFrames() const
		{
			return (Standard_Integer)theFrames_.size();
		}

		const auto& Counter() const
		{
			return theCounter_;
		}

		const auto& Scatter() const
		{
			return theScatter_;
		}

		const auto& Parameter() const
		{
			return theParameter_;
		}

		const auto& Frames() const
		{
			return theFrames_;
		}

		const auto& Shape() const
		{
			return theShape_;
		}

		TnbSectPx_EXPORT std::shared_ptr<SectPx_FrameRegistry>
			SelectFrame(const Standard_Integer theIndex) const;

		TnbSectPx_EXPORT Standard_Integer
			CreateFrame();

		TnbSectPx_EXPORT std::shared_ptr<SectPx_FrameRegistry>
			RemoveFrame(const Standard_Integer theIndex);
	};

}

#endif // !_SectPx_Registry_Header
