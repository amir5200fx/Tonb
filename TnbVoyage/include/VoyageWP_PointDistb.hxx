#pragma once
#ifndef _VoyageWP_PointDistb_Header
#define _VoyageWP_PointDistb_Header

#include <Voyage_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageWP_Net;
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

			Side() = default;

			//- Constructors

		public:

			//- public functions and operators

			[[nodiscard]] const auto& Offsets() const { return theOffsets_; }

			void SetOffsets(const std::shared_ptr<Entity2d_Polygon>& theOffsets) 
			{ theOffsets_ = theOffsets; }

		};

		class StarSide
			: public Side
		{

			/*Private Data*/

		public:

			//- default constructor

			StarSide() = default;

			//- Public functions and operators

		};

		class PortSide
			: public Side
		{

			/*Private Data*/

		public:

			//- default constructor

			PortSide() = default;

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
				= default;

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

			[[nodiscard]] const auto& Coord() const { return theCoord_; }
			[[nodiscard]] const auto& Direction() const { return theDir_; }

			[[nodiscard]] virtual Standard_Boolean IsInterior() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsDeparture() const { return Standard_False; }
			[[nodiscard]] virtual Standard_Boolean IsArrival() const { return Standard_False; }

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
				= default;

			//- constructors

			InterNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsInterior() const override { return Standard_True; }

			[[nodiscard]] const auto& Starboard() const { return theStarboard_; }
			[[nodiscard]] const auto& Port() const { return thePort_; }

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
				= default;

			//- constructors

			DepNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsDeparture() const override { return Standard_True; }

		};

		class ArvNode
			: public RefNode
		{

			/*Private Data*/

		public:

			//- default constructor

			ArvNode()
				= default;

			//- constructors

			ArvNode(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: RefNode(theIndex, theCoord)
			{}

			//- Public functions and operators

			[[nodiscard]] Standard_Boolean IsArrival() const override { return Standard_True; }

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

		[[nodiscard]] auto Size() const { return theSize_; }

		[[nodiscard]] const auto& Offsets() const { return theOffsets_; }
		[[nodiscard]] const auto& Profile() const { return theProfile_; }
		[[nodiscard]] const auto& Earth() const { return theEarth_; }

		[[nodiscard]] const auto& CurveInfo() const { return theCurveInfo_; }
		[[nodiscard]] const auto& IntegInfo() const { return theIntegInfo_; }

		[[nodiscard]] const auto& Nodes() const { return theNodes_; }

		TnbVoyage_EXPORT std::shared_ptr<VoyageWP_Net> RetrieveNet() const;
		
		TnbVoyage_EXPORT void Perform();

		void SetSize(const Standard_Real theSize) { theSize_ = theSize; }

		void SetOffsets(const std::shared_ptr<VoyageWP_Offset>& theOffsets) { theOffsets_ = theOffsets; }
		void SetProfile(const std::shared_ptr<Voyage_OffsetProfile>& theProfile) { theProfile_ = theProfile; }
		void SetEarth(const std::shared_ptr<VoyageGeo_Earth>& theEarth) { theEarth_ = theEarth; }

		void SetCurveInfo(const std::shared_ptr<Mesh_Curve_Info>& theInfo) { theCurveInfo_ = theInfo; }
		void SetIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo) { theIntegInfo_ = theInfo; }

		TnbVoyage_EXPORT void ExportToPlt(OFstream&) const;
	};
}

#endif // !_VoyageWP_PointDistb_Header
