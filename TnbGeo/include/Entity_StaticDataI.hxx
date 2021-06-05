#pragma once
namespace tnbLib
{
	template<class Point, class ConnectType, bool NeighbData>
	void Entity_StaticData<Point, ConnectType, NeighbData>::Add
	(
		const Entity_StaticData & theChain
	)
	{
		pointList points;
		points.reserve(thePoints_.size() + theChain.NbPoints());

		for (auto& x : thePoints_)
		{
			points.push_back(std::move(x));
		}

		for (const auto& x : theChain.Points())
		{
			points.push_back(x);
		}

		auto connectivities = CombineConnectivities(Connectivity(), theChain.Connectivity());

		thePoints_.clear();
		theConnectivity_.clear();

		thePoints_ = std::move(points);
		theConnectivity_ = std::move(connectivities);

		if (theBoundingBox_)
			theBoundingBox_ = nullptr;
	}

	template<class Point, class ConnectType, bool NeighbData>
	void Entity_StaticData<Point, ConnectType, NeighbData>::Add
	(
		Entity_StaticData && theChain
	)
	{
		auto c = std::move(theChain);
		pointList points;
		points.reserve(thePoints_.size() + c.NbPoints());

		for (auto& x : thePoints_)
		{
			points.push_back(std::move(x));
		}

		for (auto& x : c.Points())
		{
			points.push_back(std::move(x));
		}

		auto connectivities = CombineConnectivities(std::move(theConnectivity_), std::move(c.theConnectivity_));

		//thePoints_.clear();
		//theConnectivity_.clear();

		thePoints_ = std::move(points);
		theConnectivity_ = std::move(connectivities);

		if (theBoundingBox_)
			theBoundingBox_ = nullptr;
	}

	template<class Point, class ConnectType, bool NeighbData>
	void Entity_StaticData<Point, ConnectType, NeighbData>::Clear()
	{
		thePoints_.clear();
		theConnectivity_.clear();
		theBoundingBox_.reset();
	}

	template<class Point, class ConnectType, bool NeighbData>
	std::shared_ptr<Entity_StaticData<Point, ConnectType, NeighbData>>
		Entity_StaticData<Point, ConnectType, NeighbData>::Added
		(
			const Entity_StaticData & theChain
		) const
	{
		auto copy = *this;
		copy.Add(theChain);

		auto p = std::make_shared<Entity_StaticData>(std::move(copy));
		return std::move(p);
	}

	/*template<class Point, class ConnectType, bool NeighbData>
	template<class Archive>
	void Entity_StaticData<Point, ConnectType, NeighbData>::serialize
	(
		Archive & ar, 
		const unsigned int version
	)
	{
		ar & Points();
		ar & Connectivity();
		ar & BoundingBox();
	}*/

	/*template<class Point, class ConnectType>
	template<class Archive>
	void Entity_StaticData<Point, ConnectType, true>::serialize
	(
		Archive & ar,
		const unsigned int version
	)
	{
		ar& boost::serialization::base_object<base>(*this);
		ar& Neighbors();
	}*/

	template<class Point, class ConnectType>
	inline void tnbLib::Entity_StaticData<Point, ConnectType, true>::Clear()
	{
		base::Clear();
		theNeighbors_.clear();
	}
}