#pragma once
#ifndef _Mesh_SetSourcesNode_Header
#define _Mesh_SetSourcesNode_Header

#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	template<class Point, class Value>
	class Mesh_SetSourcesNode
	{

		/*Private Data*/

		Point theCoord_;

		Value theValue_;

	public:

		typedef Point ptType;


		// default constructor [8/10/2022 Amir]

		Mesh_SetSourcesNode()
			: theCoord_(Point::null)
			, theValue_(0)
		{}


		// constructors [8/10/2022 Amir]

		Mesh_SetSourcesNode
		(
			const Point& theCoord,
			const Value& h
		)
			: theCoord_(theCoord)
			, theValue_(h)
		{}

		Mesh_SetSourcesNode
		(
			Point&& theCoord, 
			Value&& h
		)
			: theCoord_(std::move(theCoord))
			, theValue_(std::move(h))
		{}


		// public functions and operators [8/10/2022 Amir]

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

		auto H() const
		{
			return theValue_;
		}

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Point&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		void SetH(const Value& theValue)
		{
			theValue_ = theValue;
		}

		static const auto& GetCoord(const std::shared_ptr<Mesh_SetSourcesNode>& theNode)
		{
			return theNode->Coord();
		}
	};

	template<class Point>
	class Mesh_SetSourcesNode<Point, void>
	{

		/*Private Data*/

		Point theCoord_;

	public:


		typedef Point ptType;

		// default constructor [8/13/2022 Amir]

		Mesh_SetSourcesNode()
			: theCoord_(Point::null)
		{}


		// constructors [8/13/2022 Amir]

		Mesh_SetSourcesNode(const Point& theCoord)
			: theCoord_(theCoord)
		{}

		Mesh_SetSourcesNode(Point&& theCoord)
			: theCoord_(std::move(theCoord))
		{}


		// public functions and operators [8/13/2022 Amir]

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Point&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		static const auto& GetCoord(const std::shared_ptr<Mesh_SetSourcesNode>& theNode)
		{
			return theNode->Coord();
		}
	};

	template<class Point>
	class Mesh_SetSourcesNode<Point, Standard_Real>
	{

		/*Private Data*/

		Point theCoord_;

		Standard_Real theValue_;

	public:

		typedef Point ptType;

		// default constructor [8/13/2022 Amir]

		Mesh_SetSourcesNode()
			: theCoord_(Point::null)
			, theValue_(0)
		{}

		// constructors [8/13/2022 Amir]

		Mesh_SetSourcesNode
		(
			const Point& theCoord, 
			const Standard_Real theValue
		)
			: theCoord_(theCoord)
			, theValue_(theValue)
		{}

		Mesh_SetSourcesNode
		(
			Point&& theCoord,
			const Standard_Real theValue
		)
			: theCoord_(std::move(theCoord))
			, theValue_(theValue)
		{}


		// public functions and operators [8/13/2022 Amir]

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto& CoordRef()
		{
			return theCoord_;
		}

		auto H() const
		{
			return theValue_;
		}

		void SetCoord(const Point& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Point&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		void SetH(const Standard_Real theValue)
		{
			theValue_ = theValue;
		}

		static const auto& GetCoord(const std::shared_ptr<Mesh_SetSourcesNode>& theNode)
		{
			return theNode->Coord();
		}

	};
}

#endif // !_Mesh_SetSourcesNode_Header
