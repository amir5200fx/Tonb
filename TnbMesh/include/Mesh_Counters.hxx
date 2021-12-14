#pragma once
#ifndef _Mesh_Counters_Header
#define _Mesh_Counters_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>
#include <Mesh_EntityCounterM.hxx>

namespace tnbLib
{

	Mesh_EntityCounter(NodeCounter);
	Mesh_EntityCounter(EdgeCounter);
	Mesh_EntityCounter(FacetCounter);
	Mesh_EntityCounter(ElementCounter);

	class Mesh2d_FrontCounter
		: public Mesh_NodeCounterCounter
		, public Mesh_EdgeCounterCounter
		, public Mesh_ElementCounterCounter
	{

		/*Private Data*/


		// Private functions and operators [11/22/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Mesh_NodeCounterCounter>(*this);
			ar & boost::serialization::base_object<Mesh_EdgeCounterCounter>(*this);
			ar & boost::serialization::base_object<Mesh_ElementCounterCounter>(*this);
		}

	public:

		// default constructor [11/22/2021 Amir]

		Mesh2d_FrontCounter()
		{}

		// Public functions and operators [11/22/2021 Amir]


	};

	class Mesh3d_FrontCounter
		: public Mesh_NodeCounterCounter
		, public Mesh_EdgeCounterCounter
		, public Mesh_FacetCounterCounter
		, public Mesh_ElementCounterCounter
	{

		/*Private Data*/


		// Private functions and operators [11/22/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Mesh_NodeCounterCounter>(*this);
			ar & boost::serialization::base_object<Mesh_EdgeCounterCounter>(*this);
			ar & boost::serialization::base_object<Mesh_FacetCounterCounter>(*this);
			ar & boost::serialization::base_object<Mesh_ElementCounterCounter>(*this);
		}

	public:

		// default constructor [11/22/2021 Amir]

		Mesh3d_FrontCounter()
		{}

		// Public functions and operators [11/22/2021 Amir]

	};
}

#endif // !_Mesh2d_Counters_Header