#pragma once
#ifndef _SectPx_Pole_CornerAdaptor_Header
#define _SectPx_Pole_CornerAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>

#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_PoleController;
	class SectPx_ShapeModifier;

	class SectPx_Pole_CornerAdaptor
	{

		friend class SectPx_ShapeModifier;

		/*Private Data*/

		std::map<Standard_Integer, std::weak_ptr<SectPx_PoleController>>
			theControllers_;

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_Pole_CornerAdaptor()
		{}

	public:

		auto NbControllers() const
		{
			return (Standard_Integer)theControllers_.size();
		}

		const auto& Controllers() const
		{
			return theControllers_;
		}

		Standard_Boolean HasController() const
		{
			return (Standard_Boolean)NbControllers();
		}

		TnbSectPx_EXPORT std::weak_ptr<SectPx_PoleController> 
			RemoveController
			(
				const Standard_Integer theIndex
			);

		TnbSectPx_EXPORT void InsertToControllers
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<SectPx_PoleController>& theController
		);


	};
}

#endif // !_SectPx_Pole_CornerAdaptor_Header