#pragma once
#ifndef _Geo_SearchTree_Header
#define _Geo_SearchTree_Header

#include <Global_Serialization.hxx>
#include <Entity_Box.hxx>

#include <vector>
#include <list>
#include <functional>

namespace tnbLib
{

	class Geo_SearchTree_Base
	{

		/*Private Data*/

		Standard_Integer theNbItems_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& theNbItems_;
		}

	protected:

		// default constructor

		Geo_SearchTree_Base()
			: theNbItems_(0)
		{}

		// constructors

		// Protected functions and operators

		auto& ChangeNbItems()
		{
			return theNbItems_;
		}

		void Increment()
		{
			theNbItems_++;
		}

		void Decrement()
		{
			theNbItems_--;
		}

	public:

		// Public functions and operators

		auto NbItems() const
		{
			return theNbItems_;
		}

		auto GeometrySize() const
		{
			return NbItems();
		}
	};

	template<class T>
	class Geo_SearchTree
		: public Geo_SearchTree_Base
	{

		typedef typename remove_pointer<T>::type::ptType Point;

		/*Private Data*/

		Entity_Box<Point> theRegion_;


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& theRegion_;
		}

	protected:

		std::function<const Point& (const T&)> CoordinateOf;

		// default constructor

		Geo_SearchTree() = default;

		// constructors

		explicit Geo_SearchTree
		(
			Entity_Box<Point> theRegion
		)
			: theRegion_(std::move(theRegion))
		{}
	

	public:

		// Public functions and operators

		virtual void Clear() = 0;

		virtual void InsertToGeometry(const T& theItem) = 0;

		virtual void InsertToGeometry(const std::vector<T>& theItems) = 0;

		virtual void RemoveFromGeometry(const T& theItem) = 0;

		virtual void RetrieveFromGeometryTo
		(
			std::vector<T>& theItems
		) const = 0;

		virtual void RetrieveFromGeometryTo
		(
			std::list<T>& theItems
		) const = 0;

		virtual void GeometrySearch
		(
			const Entity_Box<Point>& theRegion,
			std::vector<T>& theList
		) const = 0;

		virtual void GeometrySearch
		(
			const Entity_Box<Point>& theRegion,
			std::list<T>& theList
		) const = 0;

		virtual void GeometrySearch
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			std::list<T>& theList
		) const = 0;

		virtual void GeometrySearch
		(
			const Standard_Real theRadius,
			const Point& theCentre,
			std::vector<T>& theList
		) const = 0;

		Standard_Boolean IsGeometryEmpty() const
		{
			return !GeometrySize();
		}

		const auto& GeometryBoundingBox() const
		{
			return theRegion_;
		}

		void SetGeometryRegion(const Entity_Box<Point>& theBound)
		{
			theRegion_ = theBound;
		}

		void SetGeometryRegion(const Entity_Box<Point>&& theBound)
		{
			theRegion_ = std::move(theBound);
		}

		void SetGeometryCoordFunc(const Point& (*theCoordinateOf)(const T&))
		{
			CoordinateOf = theCoordinateOf;
		}
	};
}

#include <Geo_PrTreeI.hxx>

#endif // !_Geo_SearchTree_Header
