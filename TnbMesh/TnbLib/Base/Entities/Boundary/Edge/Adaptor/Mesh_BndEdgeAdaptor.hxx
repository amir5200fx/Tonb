#pragma once
#ifndef _Mesh_BndEdgeAdaptor_Header
#define _Mesh_BndEdgeAdaptor_Header

#include <Mesh_BndEdgeGeomAdaptor.hxx>

namespace tnbLib
{

	template
		<
		class CurveType,
		class SurfType,
		class FacetType,
		class MetricPrcsr,
		Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment
		>
		class Mesh_BndEdgeAdaptor
		: public Mesh_BndEdgeGeomAdaptor<CurveType, SurfType, POS>
	{


	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, SurfType, POS> base;

	private:


		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	protected:

		//- default constructor

		Mesh_BndEdgeAdaptor()
		{}

	public:

		

		//- public functions and operators


	};

	template<class CurveType>
	class Mesh_BndEdgeAdaptor<CurveType, void, void, void>
		: public Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
	{

	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
			base;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	public:

		Mesh_BndEdgeAdaptor()
		{}


		//- public functions and operators


	};

	template<class CurveType, class MetricPrcsr>
	class Mesh_BndEdgeAdaptor<CurveType, void, void, MetricPrcsr>
		: public Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
	{

	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
			base;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	public:

		Mesh_BndEdgeAdaptor()
		{}


		//- public functions and operators

		virtual Standard_Boolean SingularityContraction(const MetricPrcsr&);
	};
}

#include <Mesh_BndEdgeAdaptorI.hxx>

#endif // !_Mesh_BndEdgeAdaptor_Header
