#pragma once
#ifndef _Geo_GraphEdge_Header
#define _Geo_GraphEdge_Header

#include <Global_Indexed.hxx>
#include <Global_AccessMethod.hxx>
#include <Geo_GraphEdgeAdaptor.hxx>

#include <memory>

namespace tnbLib
{

	template<class EdgeTraits>
	class Geo_GraphEdge
		: public Global_Indexed
		, public Geo_GraphEdgeAdaptor<typename EdgeTraits::edgeAdaptType>
	{

	public:

		typedef typename EdgeTraits::nodeType nodeType;
		typedef Geo_GraphEdgeAdaptor<typename EdgeTraits::edgeAdaptType> adaptor;

	private:

		/*Private Data*/


	protected:

		// default constructor [1/5/2022 Amir]

		Geo_GraphEdge()
		{}


		// constructors [1/5/2022 Amir]

		explicit Geo_GraphEdge
		(
			const Standard_Integer theIndex
		)
			: Global_Indexed(theIndex)
		{}

	public:


		// public functions and operators [1/5/2022 Amir]

		virtual Standard_Boolean IsSegment() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsRing() const
		{
			return Standard_False;
		}


		//- Macros

	};
}


#endif // !_Geo_GraphEdge_Header
