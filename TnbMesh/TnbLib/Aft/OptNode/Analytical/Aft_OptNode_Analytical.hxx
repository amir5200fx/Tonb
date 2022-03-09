#pragma once
#ifndef _Mesh_OptNode_Analytical_Header
#define _Mesh_OptNode_Analytical_Header

#include <Global_Done.hxx>
#include <Standard_TypeDef.hxx>

#include <Aft_OptNode_AnalyticalTraits.hxx>

namespace tnbLib
{

	template<class FrontType, class MetricType = void>
	class Aft_OptNode_Analytical
		: public Global_Done
	{

	public:

		typedef typename point_type_from_front<FrontType>::ptType Point;

	private:

		/*Private Data*/

		Standard_Real theSize_;

		const MetricType& theMetric_;
		const FrontType& theFront_;

		Point theCoord_;


		Point& ChangeCoord()
		{
			return theCoord_;
		}

	public:

		// default constructor [12/23/2021 Amir]


		// constructors [12/23/2021 Amir]

		Aft_OptNode_Analytical
		(
			const Standard_Real theSize,
			const MetricType& theMetric,
			const FrontType& theFront
		)
			: theSize_(theSize)
			, theMetric_(theMetric)
			, theFront_(theFront)
		{}


		// public functions and operators [12/23/2021 Amir]

		auto ElementSize() const
		{
			return theSize_;
		}

		const auto& Metric() const
		{
			return theMetric_;
		}

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		void Perform();

	};

	template<class FrontType>
	class Aft_OptNode_Analytical<FrontType, void>
		: public Global_Done
	{

	public:

		typedef typename point_type_from_front<FrontType>::ptType Point;

	private:

		/*Private Data*/

		Standard_Real theSize_;

		const FrontType& theFront_;

		Point theCoord_;


		Point& ChangeCoord()
		{
			return theCoord_;
		}

	public:

		// default constructor [12/23/2021 Amir]


		// constructors [12/23/2021 Amir]

		Aft_OptNode_Analytical
		(
			const Standard_Real theSize,
			const FrontType& theFront
		)
			: theSize_(theSize)
			, theFront_(theFront)
		{}


		// public functions and operators [12/23/2021 Amir]

		auto ElementSize() const
		{
			return theSize_;
		}

		const auto& Front() const
		{
			return theFront_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		void Perform();
	};
}

#endif // !_Mesh_OptNode_Analytical_Header