#pragma once
#ifndef _ShapePx_TopoSectNode_Header
#define _ShapePx_TopoSectNode_Header

#include <ShapePx_TopoSectEntity.hxx>
#include <ShapePx_TopoSectPolesFwd.hxx>
#include <ShapePx_TopoSectNodeAdaptor.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	

	class ShapePx_TopoSectNode
		: public ShapePx_TopoSectEntity
		, public ShapePx_TopoSectNodeAdaptor
	{

		/*Private Data*/

		std::shared_ptr<shapePxLib::TopoSectPole_Bnd> thePole_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	protected:


		//- default constructor

		ShapePx_TopoSectNode()
		{}

	public:

		//- constructors

		ShapePx_TopoSectNode
		(
			const std::shared_ptr<shapePxLib::TopoSectPole_Bnd>& thePole
		)
			: thePole_(thePole)
		{}

		ShapePx_TopoSectNode
		(
			std::shared_ptr<shapePxLib::TopoSectPole_Bnd>&& thePole
		)
			: thePole_(std::move(thePole))
		{}

		ShapePx_TopoSectNode
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<shapePxLib::TopoSectPole_Bnd>& thePole
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, thePole_(thePole)
		{}


		//- public functions and operators

		const auto& Pole() const
		{
			return thePole_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_TopoSectNode);

#endif // !_ShapePx_TopoSectNode_Header
