#pragma once
#ifndef _VoyageSim_MinFuel2_Header
#define _VoyageSim_MinFuel2_Header

#include <VoyageSim_Variables.hxx>
#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace var = tnbLib::voyageLib::variable;

namespace tnbLib
{
	
	class VoyageSim_MinFuel2
		: public Global_Done
	{

	public:

		

		/*typedef std::function<
			Standard_Real(
				const std::pair<Pnt2d, Standard_Real>&,
				const std::pair<Pnt2d, Standard_Real>&,
				const Standard_Real,
				const Standard_Integer
			)>
			ResistFunc;*/
		typedef  std::function<
			std::tuple<var::Time, var::Cost>(
				const var::State&, 
				const Pnt2d&, 
				const var::Distance&,
				const var::Power&,
				const var::NbSamples&
			)>
			CostFunc;
		typedef std::function<Standard_Real(const Pnt2d&, const Pnt2d&)>
			DistFunc;


	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;
		
		var::NbSamples theNbSamples_;

		var::Power thePower_;
		
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

		VoyageSim_MinFuel2() = default;

		// constructors


		// Public functions and operators

		const auto& Net() const { return theNet_; }

		void Perform();

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }
		void SetPower(const var::Power theValue) { thePower_ = theValue; }

		void SetResistFunc(const CostFunc& theFun) { theCostFun_ = theFun; }
		void SetDistFunc(const DistFunc& theFun) { theDist_ = theFun; }

	};
}

#endif // !_VoyageSim_MinFuel2_Header
