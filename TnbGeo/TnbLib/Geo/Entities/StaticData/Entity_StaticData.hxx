#pragma once
#ifndef _Entity_StaticData_Header
#define _Entity_StaticData_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Traits.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <OFstream.hxx>

#include <vector>
#include <memory>
#include <sstream>

namespace tnbLib
{

	// Forward Declarations
	template<class Point> class Entity_Box;

	template<class Point, class ConnectType, bool NeighbData = false>
	class Entity_StaticData
	{

	public:

		typedef std::vector<Point> pointList;
		typedef std::vector<ConnectType> connectList;
		typedef Entity_Box<Point> box;
		typedef std::shared_ptr<box> box_ptr;

	private:

		/*Private Data*/

		pointList thePoints_;

		connectList theConnectivity_;

		box_ptr theBoundingBox_;


		/*private functions and operators*/

		friend class boost::serialization::access;
		
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & thePoints_;
			ar & theConnectivity_;
			ar & theBoundingBox_;
		}

	public:

		typedef Point ptType;
		typedef ConnectType connectType;


		static TnbGeo_EXPORT const std::string extension;


		//- default constructor

		Entity_StaticData() = default;


		//- constructors

		Entity_StaticData(pointList thePoints, connectList theConnectivity)
			: thePoints_(std::move(thePoints))
			, theConnectivity_(std::move(theConnectivity))
		{}

		Entity_StaticData(Entity_StaticData&& other) noexcept
			: thePoints_(std::move(other.thePoints_))
			, theConnectivity_(std::move(other.theConnectivity_))
		{}


		//- public functions and operators

		Entity_StaticData& operator = (Entity_StaticData&& other) noexcept
		{
			if (this != &other)
			{
				thePoints_ = std::move(other.thePoints_);
				theConnectivity_ = std::move(other.theConnectivity_);
				theBoundingBox_ = std::move(other.theBoundingBox_);
			}
			return *this;
		}

		const pointList& Points() const
		{
			return thePoints_;
		}

		pointList& Points()
		{
			return thePoints_;
		}

		const connectList& Connectivity() const
		{
			return theConnectivity_;
		}

		connectList& Connectivity()
		{
			return theConnectivity_;
		}

		Standard_Integer NbPoints() const
		{
			return static_cast<Standard_Integer>(thePoints_.size());
		}

		Standard_Integer NbConnectivity() const
		{
			return static_cast<Standard_Integer>(theConnectivity_.size());
		}

		void CalcBoundingBox();

		const box_ptr& BoundingBox() const
		{
			return theBoundingBox_;
		}

		std::shared_ptr<Entity_StaticData> 
			Merged
			(
				const Standard_Real theRes, 
				const Standard_Real theRadius
			) const;

		std::shared_ptr<Entity_StaticData> 
			Added
			(
				const Entity_StaticData& theChain
			) const;

		void Transform
		(
			const typename transform_point_type<Point>::type& theTrasf
		)
		{
			for (auto& x : thePoints_)
			{
				x.Transform(theTrasf);
			}
		}

		void Merging(const Standard_Boolean HandleDegeneracy, const Standard_Real Resolution, const Standard_Real Radius);

		void Add(const Entity_StaticData& theChain);
		void Add(Entity_StaticData&& theChain);

		void Clear();

		void SetBoundingBox(const std::shared_ptr<box>& theBox)
		{
			theBoundingBox_ = theBox;
		}

		void SetBoundingBox(std::shared_ptr<box>&& theBox)
		{
			theBoundingBox_ = std::move(theBox);
		}

		void ExportToPlt(std::fstream& File) const;

		void ExportToPlt(OFstream& File) const;
		void StreamToPlt(std::stringstream& theStream) const;
		void ExportToVtk(OFstream&) const;
		void ExportToVtk(std::stringstream& theStream) const;
		void ExportToVtk(std::fstream&) const;
	};

	template<class Point, class ConnectType>
	class Entity_StaticData<Point, ConnectType, true>
		: public Entity_StaticData<Point, ConnectType, false>
	{

		typedef std::vector<Point> pointList;
		typedef std::vector<ConnectType> connectList;
		typedef Entity_Box<Point> box;
		typedef std::shared_ptr<box> box_ptr;

		/*Private Data*/

		connectList theNeighbors_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Entity_StaticData<Point, ConnectType, false>>(*this);
			ar & theNeighbors_;
		}

	public:

		typedef Entity_StaticData<Point, ConnectType, false> base;


		//- default constructor

		Entity_StaticData() = default;


		//- constructors

		Entity_StaticData(pointList thePoints, connectList theConnectivity, connectList theNeighbors)
			: Entity_StaticData<Point, ConnectType, false>(std::move(thePoints), std::move(theConnectivity))
			, theNeighbors_(std::move(theNeighbors))
		{}

		Entity_StaticData(Entity_StaticData&& other) noexcept
			: Entity_StaticData<Point, ConnectType, false>(std::move(other))
			, theNeighbors_(std::move(other.theNeighbors_))
		{}

		//- public functions and operators

		Entity_StaticData& operator=(Entity_StaticData&& other) noexcept
		{
			if (this != &other)
			{
				base::operator=(std::move(other));
			}
			theNeighbors_ = std::move(other.theNeighbors_);
			return *this;
		}

		const connectList& Neighbors() const
		{
			return theNeighbors_;
		}

		connectList& Neighbors()
		{
			return theNeighbors_;
		}

		void Swap
		(
			const Standard_Integer theElement,
			const Standard_Integer theEdge
		);

		void Clear();

	};
}

#include <Entity_StaticDataI.hxx>

#endif // !_Entity_StaticData_Header
