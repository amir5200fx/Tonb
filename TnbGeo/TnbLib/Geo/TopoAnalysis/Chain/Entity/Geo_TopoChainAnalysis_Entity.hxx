#pragma once
#ifndef _Geo_TopoChainAnalysis_Entity_Header
#define _Geo_TopoChainAnalysis_Entity_Header

#include <Global_Indexed.hxx>

#include <list>
#include <memory>

namespace tnbLib
{

	template<class EdgeType>
	class Geo_TopoChainAnalysis_Entity
		: public Global_Indexed
	{

		/*Private Data*/

		std::list<std::shared_ptr<EdgeType>> theEntities_;

		Standard_Boolean IsRing_;

	public:

		// default constructor [4/1/2022 Amir]

		Geo_TopoChainAnalysis_Entity()
			: IsRing_(Standard_False)
		{}


		// constructors [4/1/2022 Amir]

		Geo_TopoChainAnalysis_Entity(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
			, IsRing_(Standard_False)
		{}

	public:

		// public functions and operators [4/1/2022 Amir]

		Standard_Boolean IsDangle() const;

		auto IsRing() const
		{
			return IsRing_;
		}

		auto& IsRingRef()
		{
			return IsRing_;
		}

		const auto& Entities() const
		{
			return theEntities_;
		}

		auto& EntitiesRef()
		{
			return theEntities_;
		}

		const auto& First() const
		{
			return theEntities_.front();
		}

		auto& FirstRef()
		{
			return theEntities_.front();
		}

		const auto& End() const
		{
			return theEntities_.back();
		}

		auto& EndRef()
		{
			return theEntities_.back();
		}
	};
}

#include <Geo_TopoChainAnalysis_EntityI.hxx>

#endif // !_Geo_TopoChainAnalysis_Entity_Header
