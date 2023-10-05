#pragma once
#ifndef _VoyageSim_MinFuel_Header
#define _VoyageSim_MinFuel_Header

#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class VoyageWP_Net;

	class VoyageSim_MinFuel
		: public Global_Done
	{


	public:

		typedef std::function<Standard_Real(const std::pair<Pnt2d, Standard_Real>&, const std::pair<Pnt2d, Standard_Real>&, const Standard_Real, const Standard_Integer)>
			ResistFunc;
		typedef std::function<Standard_Real(const Pnt2d&, const Pnt2d&)>
			DistFunc;

	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;

		Standard_Real theMinVel_;
		Standard_Real theMaxVel_;
		Standard_Real theVel_;

		Standard_Integer theNbLevels_;
		Standard_Integer theNbSamples_;

		Standard_Real theTimeStep_;
		Standard_Real theTimeRes_;

		// functions
		ResistFunc theResistFun_;
		DistFunc theDist_;

		// Private funtions and operators

		std::vector<Standard_Real> CalcVelocities() const;

		static TnbVoyage_EXPORT std::vector<Standard_Real>
			DiscreteTime
			(
				const std::pair<Standard_Real, Standard_Real>&,
				const Standard_Real theDt
			);

		static TnbVoyage_EXPORT Standard_Boolean
			InsideTimeLine
			(
				const Standard_Real theTime,
				const std::vector<Standard_Real>&
			);

	public:

		static TnbVoyage_EXPORT unsigned short verbose;

		// default constructor

		VoyageSim_MinFuel();

		// constructors

		// Public functions and operators

		const auto& Net() const { return theNet_; }

		auto MinVel() const { return theMinVel_; }
		auto MaxVel() const { return theMaxVel_; }
		auto Vel() const { return theVel_; }
		auto NbLevels() const { return theNbLevels_; }
		auto NbSamples() const { return theNbSamples_; }

		auto TimeStep() const { return theTimeStep_; }
		auto TimeResolution() const { return theTimeRes_; }

		TnbVoyage_EXPORT void Perform();

		void SetMinVel(const Standard_Real theVel) { theMinVel_ = theVel; }
		void SetMaxVel(const Standard_Real theVel) { theMaxVel_ = theVel; }
		void SetVel(const Standard_Real theVel) { theVel_ = theVel; }

		void SetNbLevels(const Standard_Integer theSize) { theNbLevels_ = theSize; }
		void SetNbSamples(const Standard_Integer theSize) { theNbSamples_ = theSize; }

		void SetTimeStep(const Standard_Real theStep) { theTimeStep_ = theStep; }
		void SetTimeRes(const Standard_Real theRes) { theTimeRes_ = theRes; }

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }

		void SetResistFunc(const ResistFunc& theFun) { theResistFun_ = theFun; }
		void SetDistFunc(const DistFunc& theFun) { theDist_ = theFun; }

	};
}

#endif
