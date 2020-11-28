#pragma once
#ifndef _SectPx_Profile_Header
#define _SectPx_Profile_Header

#include <Standard_Handle.hxx>
#include <Pnt2d.hxx>
#include <SectPx_RegObj.hxx>

#include <vector>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Node;
	class SectPx_Registry;
	class SectPx_KnotVector;

	class SectPx_TopoProfile
		: public SectPx_RegObj
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Node> theNode0_;
		std::shared_ptr<SectPx_Node> theNode1_;

		std::shared_ptr<SectPx_KnotVector> theKnotAlg_;


		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_TopoProfile()
		{}

		TnbSectPx_EXPORT SectPx_TopoProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_TopoProfile
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		TnbSectPx_EXPORT SectPx_TopoProfile
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SectPx_Node>& theNode0,
			const std::shared_ptr<SectPx_Node>& theNode1
		);

		virtual void Update() const
		{}


		static TnbSectPx_EXPORT void SetProfile
		(
			const std::shared_ptr<SectPx_Node>& theNode, 
			const std::shared_ptr<SectPx_TopoProfile>& theProfile
		);

	public:

		const auto& Node0() const
		{
			return theNode0_;
		}

		const auto& Node1() const
		{
			return theNode1_;
		}

		const auto& Knots() const
		{
			return theKnotAlg_;
		}

		TnbSectPx_EXPORT std::vector<Pnt2d>
			RetrieveCoords() const;

		void SetKnot(const std::shared_ptr<SectPx_KnotVector>& theKnot)
		{
			theKnotAlg_ = theKnot;
		}

		void SetKnot(std::shared_ptr<SectPx_KnotVector>&& theKnot)
		{
			theKnotAlg_ = std::move(theKnot);
		}

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsProfile() const override;

		TnbSectPx_EXPORT Handle(Geom2d_Curve)
			RetrieveGeomCurve
			(
				const Standard_Integer deg
			) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_TopoProfile);

#endif // !_SectPx_Profile_Header
