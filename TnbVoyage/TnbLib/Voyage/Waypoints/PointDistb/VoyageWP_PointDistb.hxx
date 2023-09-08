#pragma once
#ifndef _VoyageWP_PointDistb_Header
#define _VoyageWP_PointDistb_Header

#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <vector>
#include <memory>

#include <Standard_Type.hxx>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageWP_Offset;
	class Voyage_OffsetProfile;
	class VoyageGeo_Earth;
	class Mesh_Curve_Info;
	class NumAlg_AdaptiveInteg_Info;

	class VoyageWP_PointDistb
		: public Global_Done
	{

	public:

		class Side
		{

			/*Private Data*/

			std::shared_ptr<Entity2d_Polygon> theOffsets_;

		protected:

			//- default constructor

			Side()
			{}

			//- Constructors

		public:

			//- public functions and operators

			const auto& Offsets() const { return theOffsets_; }

			void SetOffsets(const std::shared_ptr<Entity2d_Polygon>& theOffsets) 
			{ theOffsets_ = theOffsets; }

		};

		class StarSide
			: public Side
		{

			/*Private Data*/

		public:

			//- default constructor

			StarSide()
			{}

			//- Public functions and operators

		};

		class PortSide
			: public Side
		{

			/*Private Data*/

		public:

			//- default constructor

			PortSide()
			{}

			//- Public functions and operators

		};

		class RefNode
			: public Global_Indexed
		{

			/*Private Data*/

			Pnt2d theCoord_;
			Dir2d theDir_;

		protected:

			//- default constructor

			RefNode()
			{}

			//- constructors

			RefNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(theCoord)
			{}

			RefNode(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Global_Indexed(theIndex)
				, theCoord_(std::move(theCoord))
			{}

		public:

			//- Public functions and operators

			const auto& Coord() const { return theCoord_; }
			const auto& Direction() const { return theDir_; }

			virtual Standard_Boolean IsInterior() const { return Standard_False; }
			virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			virtual Standard_Boolean IsArrival() const { return Standard_False; }

			void SetCoord(const Pnt2d& theCoord) { theCoord_ = theCoord; }
			void SetDirection(const Dir2d& theDir) { theDir_ = theDir; }

		};

		class InterNode
			: public RefNode
		{

			/*Private Data*/

			std::shared_ptr<StarSide> theStarboard_;
			std::shared_ptr<PortSide> thePort_;

		public:

			//- default constructor

			InterNode()
			{}

			//- constructors

			InterNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			Standard_Boolean IsInterior() const override { return Standard_True; }

			const auto& Starboard() const { return theStarboard_; }
			const auto& Port() const { return thePort_; }

			void SetStarboard(const std::shared_ptr<StarSide>& theSide) { theStarboard_ = theSide; }
			void SetPort(const std::shared_ptr<PortSide>& theSide) { thePort_ = theSide; }

		};

		class DepNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			DepNode()
			{}

			//- constructors

			DepNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			Standard_Boolean IsDeparture() const override { return Standard_True; }

		};

		class ArvNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			ArvNode()
			{}

			//- constructors

			ArvNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			Standard_Boolean IsArrival() const override { return Standard_True; }

		};

	private:

		/*Private Data*/

		Standard_Real theSize_;

		std::shared_ptr<VoyageWP_Offset> theOffsets_;
		std::shared_ptr<Voyage_OffsetProfile> theProfile_;
		std::shared_ptr<VoyageGeo_Earth> theEarth_;

		std::shared_ptr<Mesh_Curve_Info> theCurveInfo_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIntegInfo_;

		//- results

		std::vector<std::shared_ptr<RefNode>> theNodes_;

	public:

		//- default constructor

		VoyageWP_PointDistb()
			: theSize_(0)
		{}

		//- constructors

		//- Public functions and operators

		auto Size() const { return theSize_; }

		const auto& Offsets() const { return theOffsets_; }
		const auto& Profile() const { return theProfile_; }
		const auto& Earth() const { return theEarth_; }

		const auto& CurveInfo() const { return theCurveInfo_; }
		const auto& IntegInfo() const { return theIntegInfo_; }

		const auto& Nodes() const { return theNodes_; }

		void Perform();

		void SetSize(const Standard_Real theSize) { theSize_ = theSize; }

		void SetOffsets(const std::shared_ptr<VoyageWP_Offset>& theOffsets) { theOffsets_ = theOffsets; }
		void SetProfile(const std::shared_ptr<Voyage_OffsetProfile>& theProfile) { theProfile_ = theProfile; }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }

		void SetCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveInfo_ = theInfo; }
		void SetIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo) { theIntegInfo_ = theInfo; }

	};
}

#endif // !_VoyageWP_PointDistb_Header