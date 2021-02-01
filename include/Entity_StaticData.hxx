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

namespace tnbLib
{

	// Forward Declarations
	template<class Point> class Entity_Box;

	template<class Point, class ConnectType, bool NeighbData = false>
	class Entity_StaticData
	{

		typedef std::vector<Point> pointList;
		typedef std::vector<ConnectType> connectList;
		typedef Entity_Box<Point> box;
		typedef std::shared_ptr<box> box_ptr;

		/*Private Data*/

		pointList thePoints_;

		connectList theConnectivity_;

		box_ptr theBoundingBox_;


		/*private functions and operators*/

		friend class boost::serialization::access;
		
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

	public:

		typedef Point ptType;
		typedef ConnectType connectType;

		Entity_StaticData()
		{}

		Entity_StaticData
		(
			const pointList& thePoints,
			const connectList& theConnectivity
		)
			: thePoints_(thePoints)
			, theConnectivity_(theConnectivity)
		{}

		Entity_StaticData
		(
			pointList&& thePoints,
			connectList&& theConnectivity
		)
			: thePoints_(std::move(thePoints))
			, theConnectivity_(std::move(theConnectivity))
		{}

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
			return (Standard_Integer)thePoints_.size();
		}

		Standard_Integer NbConnectivity() const
		{
			return (Standard_Integer)theConnectivity_.size();
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

		void ExportToPlt(std::fstream& File) const;

		void ExportToPlt(OFstream& File) const;
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
		void serialize(Archive& ar, const unsigned int version);

	public:

		typedef Entity_StaticData<Point, ConnectType, false> base;

		Entity_StaticData()
		{}

		Entity_StaticData
		(
			const pointList& thePoints,
			const connectList& theConnectivity,
			const connectList& theNeighbors
		)
			: Entity_StaticData<Point, ConnectType, false>(thePoints, theConnectivity)
			, theNeighbors_(theNeighbors)
		{}

		Entity_StaticData
		(
			pointList&& thePoints,
			connectList&& theConnectivity,
			connectList&& theNeighbors
		)
			: Entity_StaticData<Point, ConnectType, false>(std::move(thePoints), std::move(theConnectivity))
			, theNeighbors_(std::move(theNeighbors))
		{}

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
	};
}

#include <Entity_StaticDataI.hxx>

#endif // !_Entity_StaticData_Header
