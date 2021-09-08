#pragma once
#ifndef _ShapePx_TopoSectProfile_Header
#define _ShapePx_TopoSectProfile_Header

#include <ShapePx_TopoSectEntity.hxx>

#include <memory>

#include <gp_Pln.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSectNode;

	class ShapePx_TopoSectProfile
		: public ShapePx_TopoSectEntity
	{

		/*Private Data*/

		gp_Pln thePlane_;

		std::shared_ptr<ShapePx_TopoSectNode> theNode0_;
		std::shared_ptr<ShapePx_TopoSectNode> theNode1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	public:

		//- default constructor

		ShapePx_TopoSectProfile()
		{}


		//- constructors

		ShapePx_TopoSectProfile
		(
			const std::shared_ptr<ShapePx_TopoSectNode>& theNode0,
			const std::shared_ptr<ShapePx_TopoSectNode>& theNode1,
			const gp_Pln& thePlane
		)
			: theNode0_(theNode0)
			, theNode1_(theNode1)
			, thePlane_(thePlane)
		{}

		ShapePx_TopoSectProfile
		(
			std::shared_ptr<ShapePx_TopoSectNode>&& theNode0, 
			std::shared_ptr<ShapePx_TopoSectNode>&& theNode1, 
			gp_Pln&& thePlane
		)
			: theNode0_(std::move(theNode0))
			, theNode1_(std::move(theNode1))
			, thePlane_(std::move(thePlane))
		{}

		ShapePx_TopoSectProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<ShapePx_TopoSectNode>& theNode0, 
			const std::shared_ptr<ShapePx_TopoSectNode>& theNode1,
			const gp_Pln& thePlane
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theNode0_(theNode0)
			, theNode1_(theNode1)
			, thePlane_(thePlane)
		{}

		ShapePx_TopoSectProfile
		(
			const Standard_Integer theIndex,
			const word& theName, 
			std::shared_ptr<ShapePx_TopoSectNode>&& theNode0, 
			std::shared_ptr<ShapePx_TopoSectNode>&& theNode1, 
			gp_Pln&& thePlane
		)
			: ShapePx_TopoSectEntity(theIndex, theName)
			, theNode0_(std::move(theNode0))
			, theNode1_(std::move(theNode1))
			, thePlane_(std::move(thePlane))
		{}


		//- public functions and operators

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Node0() const
		{
			return theNode0_;
		}

		const auto& Node1() const
		{
			return theNode1_;
		}

		void SetNode0(const std::shared_ptr<ShapePx_TopoSectNode>& theNode)
		{
			theNode0_ = theNode;
		}

		void SetNode0(std::shared_ptr<ShapePx_TopoSectNode>&& theNode)
		{
			theNode0_ = std::move(theNode);
		}

		void SetNode1(const std::shared_ptr<ShapePx_TopoSectNode>& theNode)
		{
			theNode1_ = theNode;
		}

		void SetNode1(std::shared_ptr<ShapePx_TopoSectNode>&& theNode)
		{
			theNode1_ = std::move(theNode);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::ShapePx_TopoSectProfile);

#endif // !_ShapePx_TopoSectProfile_Header
