#pragma once
#ifndef _SectPx_Pole_CornerAdaptor_Header
#define _SectPx_Pole_CornerAdaptor_Header

#include <Standard_TypeDef.hxx>

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

		std::weak_ptr<SectPx_PoleController> RemoveController(const Standard_Integer theIndex);

		void InsertToControllers(const Standard_Integer theIndex, const std::shared_ptr<SectPx_PoleController>& theController);


	};
}

#endif // !_SectPx_Pole_CornerAdaptor_Header