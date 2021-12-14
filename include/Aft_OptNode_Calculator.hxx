#pragma once
#ifndef _Aft_OptNode_Calculator_Header
#define _Aft_OptNode_Calculator_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>
#include <Global_Serialization.hxx>
//#include <Aft_MetricPrcsr.hxx>

#include <Standard_Real.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	template<class FrontType, class SizeFun, class MetricFun = void>
	class Aft_OptNode_Calculator
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		typedef Aft_MetricPrcsr<FrontType, SizeFun, MetricFun>
			metricMap;
		typedef FrontType frontType;
		typedef typename SizeFun::ptType Point;

		/*Private Data*/

		std::shared_ptr<frontType> theFront_;
		std::shared_ptr<metricMap> theMetricMap_;

		Standard_Real theSize_;


		Point theCoord_;

		Standard_Boolean IsConverged_;


		// Private functions and operators [11/27/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			Info << "This function is not supposed to be called!" << endl;
			NotImplemented;
		}

	protected:

		//- default constructor

		Aft_OptNode_Calculator()
			: theSize_(0)
			, IsConverged_(Standard_True)
		{}


		//- protected functions and operators

		auto& ChangeCoord()
		{
			return theCoord_;
		}

		auto& Change_IsConverged()
		{
			return IsConverged_;
		}

	public:


		//- public functions and operators

		const std::shared_ptr<frontType>& Front() const
		{
			return theFront_;
		}

		const std::shared_ptr<metricMap>& MetricMap() const
		{
			return theMetricMap_;
		}

		auto Size() const
		{
			return theSize_;
		}

		const auto& Coord() const
		{
			return theCoord_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		virtual void Perform() = 0;

		void SetFront(const std::shared_ptr<frontType>& theFront);
		void SetMetricMap(const std::shared_ptr<metricMap>& theMetricMap);
		void SetSize(const Standard_Real theSize);
	};
}

#include <Aft_OptNode_CalculatorI.hxx>

#endif // !_Aft_OptNode_Calculator_Header