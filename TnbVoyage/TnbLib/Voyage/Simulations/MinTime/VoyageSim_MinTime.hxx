#pragma once
#ifndef _VoyageSim_MinTime_Header
#define _VoyageSim_MinTime_Header

#include <VoyageSim_Variables.hxx>
#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class VoyageSim_MinTime
		: public Global_Done
	{

	public:

		using voyageLib::variable::Time;
		using voyageLib::variable::Cost;
		using voyageLib::variable::Distance;
		using voyageLib::variable::RPM;
		using voyageLib::variable::NbSamples;
		using voyageLib::variable::Power;

		typedef  std::pair<Pnt2d, Standard_Real> State;

		/*typedef std::function<
			Standard_Real(
				const std::pair<Pnt2d, Standard_Real>&,
				const std::pair<Pnt2d, Standard_Real>&,
				const Standard_Real,
				const Standard_Integer
			)>
			ResistFunc;*/
		typedef  std::function<
			Time(
				const State&,
				const Pnt2d&,
				const Distance&,
				const Power&,
				const NbSamples&
			)>
			CostFunc;
		typedef std::function<Standard_Real(const Pnt2d&, const Pnt2d&)>
			DistFunc;


	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;

		NbSamples theNbSamples_;

		Power thePower_;

		// functions
		CostFunc theCostFun_;
		DistFunc theDist_;

		// results or caches

		std::shared_ptr<VoyageSim_Graph> theGraph_;

		// Private functions and operators
		std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Node>> CalcGraphNodesMap() const;
		std::vector<std::shared_ptr<VoyageSim_Graph::Node>> Nexts(const std::shared_ptr<VoyageWP_Net::Node>&, const Standard_Real theTime, Standard_Integer& theId) const;
		std::shared_ptr<VoyageSim_Graph> CalcGraph(const std::shared_ptr<VoyageWP_Net::Node>&, const std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Node>>&) const;

	public:

		// default constructor

		VoyageSim_MinTime() = default;

		// constructors


		// Public functions and operators

		const auto& Net() const { return theNet_; }

		void Perform();

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }
		void SetPower(const Power theValue) { thePower_ = theValue; }

		void SetResistFunc(const CostFunc& theFun) { theCostFun_ = theFun; }
		void SetDistFunc(const DistFunc& theFun) { theDist_ = theFun; }

	};
}

#endif