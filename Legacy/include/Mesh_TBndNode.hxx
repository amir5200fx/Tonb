#pragma once
#ifndef _Mesh_TBndNode_Header
#define _Mesh_TBndNode_Header

#include <Mesh_BndNode.hxx>
#include <Mesh_BndNode_Position.hxx>
#include <Mesh_BndNodeGeomAdaptor.hxx>
#include <Mesh_BndMergeAlg.hxx>

namespace tnbLib
{

	template<class TBndNodeTraits, Mesh_BndNode_Position POS = Mesh_BndNode_Position_Corner>
	class Mesh_TBndNode
	{};

	template<class TBndNodeTraits>
	class Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Corner>
		: public Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits>
		, public Mesh_BndNodeGeomAdaptor
		<
		typename TBndNodeTraits::curveType,
		typename TBndNodeTraits::surfType, 
		Mesh_BndNode_Position_Corner
		>
	{

	public:

		typedef Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits> base;
		typedef Mesh_BndNodeGeomAdaptor
			<
			typename TBndNodeTraits::curveType,
			typename TBndNodeTraits::surfType, 
			Mesh_BndNode_Position_Corner
			> geomAdaptor;

		typedef typename Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits>::Point Point;
		typedef typename TBndNodeTraits::metricPrcsr metricPrcsr;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<base>(*this);
			ar & boost::serialization::base_object<geomAdaptor>(*this);
		}

	public:

		
		//- default constructor

		Mesh_TBndNode()
		{}


		//- constructors

		Mesh_TBndNode
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Mesh_TBndNode
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: base(theIndex, theCoord)
		{}

		// public functions and operators [4/26/2022 Amir]

		virtual Standard_Boolean IsSingular() const;

		// override functions and operators [4/25/2022 Amir]

		Standard_Boolean IsCorner() const override
		{
			return Standard_True;
		}

		//- Static functions and operators

		static std::shared_ptr<Mesh_TBndNode>
			MergeNodes
			(
				const std::shared_ptr<Mesh_TBndNode>& theNode0,
				const std::shared_ptr<Mesh_TBndNode>& theNode1,
				const Mesh_BndMergeAlg theAlg
			);
	};


	template<class TBndNodeTraits>
	class Mesh_TBndNode<TBndNodeTraits, Mesh_BndNode_Position_Segment>
		: public Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits>
		, public Mesh_BndNodeGeomAdaptor
		<
		typename TBndNodeTraits::curveType,
		typename TBndNodeTraits::surfType, 
		Mesh_BndNode_Position_Segment
		>
	{

	public:

		typedef Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits> base;
		typedef Mesh_BndNodeGeomAdaptor
			<
			typename TBndNodeTraits::curveType,
			typename TBndNodeTraits::surfType, 
			Mesh_BndNode_Position_Segment
			> geomAdaptor;

		typedef typename Mesh_BndNode<typename TBndNodeTraits::bndNodeTraits>::Point Point;
		typedef typename TBndNodeTraits::metricPrcsr metricPrcsr;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<base>(*this);
			ar & boost::serialization::base_object<geomAdaptor>(*this);
		}

	public:


		//- default constructor

		Mesh_TBndNode()
		{}


		//- constructors

		Mesh_TBndNode
		(
			const Standard_Integer theIndex
		)
			: base(theIndex)
		{}

		Mesh_TBndNode
		(
			const Standard_Integer theIndex,
			const Point& theCoord
		)
			: base(theIndex, theCoord)
		{}

		// public functions and operators [4/26/2022 Amir]

		virtual Standard_Boolean IsSingular() const;

		// override functions and operators [4/25/2022 Amir]

		Standard_Boolean IsSegment() const override;

		//- Static functions and operators

		static std::shared_ptr<Mesh_TBndNode>
			MergeNodes
			(
				const std::shared_ptr<Mesh_TBndNode>& theNode0,
				const std::shared_ptr<Mesh_TBndNode>& theNode1,
				const Mesh_BndMergeAlg theAlg
			);
	};
}

#include <Mesh_TBndNodeI.hxx>

#endif // !_Mesh_TBndNode_Header
