#pragma once
#ifndef _VoyageSim_MinFuel_Header
#define _VoyageSim_MinFuel_Header

#include <VoyageSim_Graph.hxx>
#include <VoyageWP_Net.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class VoyageSim_Graph;
	class VoyageWP_Net;

	class VoyageSim_MinFuel
		: public Global_Done
	{


	public:

		typedef std::function<Standard_Real(const std::pair<Pnt2d, Standard_Real>&, const std::pair<Pnt2d, Standard_Real>&, const Standard_Real, const Standard_Integer)>
			ResistFunc;
		typedef std::function<Standard_Real(const Pnt2d&, const Pnt2d&)>
			DistFunc;

		struct Time
		{
			Standard_Real value;
		};

		struct Velocity
		{
			Standard_Real value;
		};
		
		struct Power
		{
			Standard_Real value;
		};

		struct Location
		{
			Pnt2d value;
		};

	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;

		Standard_Real theMinVel_;
		Standard_Real theMaxVel_;
		Standard_Real theVel_;

		Standard_Integer theNbLevels_;
		Standard_Integer theNbSamples_;

		Standard_Real theTimeStep_;
		Standard_Real theTimeRes_;  // the timeline resolution
		Standard_Real theMaxDay_;
		Standard_Real theBaseTime_;

		// functions
		ResistFunc theResistFun_;
		DistFunc theDist_;

		// Caches
		std::shared_ptr<VoyageSim_Graph> thePosGraph_;
		std::shared_ptr<VoyageSim_Graph> theGraph_;
		std::map
			<
			Standard_Integer,
			std::vector<std::shared_ptr<VoyageSim_Graph::Node>>
			>
			theNodesMap_;
		std::map<Standard_Integer, std::shared_ptr<VoyageWP_Net::Node>>
			theNetMap_;
		std::map<Standard_Integer, std::vector<Standard_Real>>
			theTimeLines_;
		std::map<Standard_Integer, std::pair<Standard_Real, std::weak_ptr<VoyageSim_Graph::Node>>>
			theTable_;
		Standard_Boolean IsInit_;

		std::map<Standard_Integer, std::shared_ptr<VoyageSim_Graph::Node>>
			theArrivals_;

		// Private functions and operators

		[[nodiscard]] std::vector<Standard_Real> CalcVelocities() const;

		static TnbVoyage_EXPORT std::vector<Standard_Real>
			DiscreteTime
			(
				const std::pair<Standard_Real, Standard_Real>&,
				const Standard_Real theDt,
				const Standard_Real theMaxTime
			);

		static TnbVoyage_EXPORT Standard_Boolean
			InsideTimeLine
			(
				const Standard_Real theTime,
				const std::vector<Standard_Real>&
			);

		static Standard_Real ConvertDaysToHours(const Standard_Real);

	public:

		static TnbVoyage_EXPORT unsigned short verbose;

		static TnbVoyage_EXPORT Standard_Real DEFAULT_MIN_VEL;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_MAX_VEL;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_VEL;

		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_LEVELS;
		static TnbVoyage_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;

		static TnbVoyage_EXPORT Standard_Real DEFAULT_TIME_STEP;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_TIME_RES;
		static TnbVoyage_EXPORT Standard_Real DEFAULT_MAX_DAY;


		// default constructor

		TnbVoyage_EXPORT VoyageSim_MinFuel();

		// constructors

		// Public functions and operators

		[[nodiscard]] const auto& Net() const { return theNet_; }
		[[nodiscard]] const auto& Timelines() const { return theTimeLines_; }
		[[nodiscard]] const auto& Graph() const { return theGraph_; }
		[[nodiscard]] const auto& PosGraph() const { return thePosGraph_; }

		[[nodiscard]] auto MinVel() const { return theMinVel_; }
		[[nodiscard]] auto MaxVel() const { return theMaxVel_; }
		[[nodiscard]] auto Vel() const { return theVel_; }
		[[nodiscard]] auto NbLevels() const { return theNbLevels_; }
		[[nodiscard]] auto NbSamples() const { return theNbSamples_; }

		[[nodiscard]] auto TimeStep() const { return theTimeStep_; }
		[[nodiscard]] auto TimeResolution() const { return theTimeRes_; }
		[[nodiscard]] auto MaxDay() const { return theMaxDay_; }
		[[nodiscard]] auto BaseTime() const { return theBaseTime_; }

		TnbVoyage_EXPORT Standard_Real MinTimeArrival() const;
		TnbVoyage_EXPORT Standard_Real MaxTimeArrival() const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> FastestTimeArrivalNode() const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> SlowestTimeArrivalNode() const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> LowestCostNode() const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> SelectArrivalNode(const Standard_Real theETA) const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> SelectArrivalNodeMinPower(const Pnt2d& arrival) const;
		TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> SelectArrivalNodeMinTime(const Pnt2d& arrival) const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageSim_Graph::Node>> SelectArrivalNodes(const Pnt2d& arrival) const;
		TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageSim_Graph::Node>> ArrivalNodeList() const;

		[[nodiscard]] const auto& ArrivalNodes() const { return theArrivals_; }

		TnbVoyage_EXPORT std::vector<std::tuple<Location, Time, Velocity, Power>> RetrievePath(const std::shared_ptr<VoyageSim_Graph::Node>&) const;

		TnbVoyage_EXPORT void Init();
		TnbVoyage_EXPORT void Perform(const Standard_Integer theStart /*the starting point of the optimization*/);

		void SetMinVel(const Standard_Real theVel) { theMinVel_ = theVel; }
		void SetMaxVel(const Standard_Real theVel) { theMaxVel_ = theVel; }
		void SetVel(const Standard_Real theVel) { theVel_ = theVel; }

		// Set the number of levels for a ship to take a velocity (must > 2)
		void SetNbLevels(const Standard_Integer theSize) { theNbLevels_ = theSize; }
		void SetNbSamples(const Standard_Integer theSize) { theNbSamples_ = theSize; }

		void SetTimeStep(const Standard_Real theStep) { theTimeStep_ = theStep; }
		// Set this time to discrete the timeline
		void SetTimeRes(const Standard_Real theRes) { theTimeRes_ = theRes; }
		void SetMaxDay(const Standard_Real theDay) { theMaxDay_ = theDay; }
		void SetBaseTime(const Standard_Real theTime) { theBaseTime_ = theTime; }

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }

		void SetResistFunc(const ResistFunc& theFun) { theResistFun_ = theFun; }
		void SetDistFunc(const DistFunc& theFun) { theDist_ = theFun; }

		static TnbVoyage_EXPORT Standard_Real MinTimeArrival(const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>&);
		static TnbVoyage_EXPORT Standard_Real MaxTimeArrival(const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>&);
		static TnbVoyage_EXPORT std::shared_ptr<VoyageSim_Graph::Node> SelectArrivalNode(const Standard_Real theETA, const std::vector<std::shared_ptr<VoyageSim_Graph::Node>>&);

	};
}

#endif
