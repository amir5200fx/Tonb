#pragma once
#ifndef _HydDyna_Holtrop_Veriables_Header
#define _HydDyna_Holtrop_Veriables_Header

#include <OSstream.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace holtropLib
	{

		// Forward Declarations [7/2/2023 Payvand]
		class ShipPrincipals;

		Ostream& operator<<(Ostream& os, const ShipPrincipals&);

		class ShipPrincipals
		{

			/*Private Data*/

			Standard_Real theB_;
			Standard_Real theT_;
			Standard_Real theL_;
			Standard_Real theCB_;
			Standard_Real theCP_;
			Standard_Real theCWP_;
			Standard_Real theCM_;
			Standard_Real theABT_;
			Standard_Real theLCB_;
			Standard_Real theDISPV_;
			Standard_Real theAT_;
			Standard_Real theTF_;
			Standard_Real theHB_;

		public:

			// default constructor [7/2/2023 Payvand]

			ShipPrincipals()
				: theB_(0)
				, theT_(0)
				, theL_(0)
				, theCB_(0)
				, theCP_(0)
				, theCWP_(0)
				, theCM_(0)
				, theABT_(0)
				, theLCB_(0)
				, theDISPV_(0)
				, theAT_(0)
				, theTF_(0)
				, theHB_(0)
			{}

			// constructors [7/2/2023 Payvand]


			// Public functions and operators [7/2/2023 Payvand]

			auto B() const { return theB_; }
			auto T() const { return theT_; }
			auto L() const { return theL_; }
			auto CB() const { return theCB_; }
			auto CP() const { return theCP_; }
			auto CWP() const { return theCWP_; }
			auto CM() const { return theCM_; }
			auto ABT() const { return theABT_; }
			auto LCB() const { return theLCB_; }
			auto DISPV() const { return theDISPV_; }
			auto AT() const { return theAT_; }
			auto TF() const { return theTF_; }
			auto HB() const { return theHB_; }

			void SetB(const Standard_Real x) { theB_ = x; }
			void SetT(const Standard_Real x) { theT_ = x; }
			void SetL(const Standard_Real x) { theL_ = x; }
			void SetCB(const Standard_Real x) { theCB_ = x; }
			void SetCP(const Standard_Real x) { theCP_ = x; }
			void SetCWP(const Standard_Real x) { theCWP_ = x; }
			void SetCM(const Standard_Real x) { theCM_ = x; }
			void SetABT(const Standard_Real x) { theABT_ = x; }
			void SetLCB(const Standard_Real x) { theLCB_ = x; }
			void SetDISPV(const Standard_Real x) { theDISPV_ = x; }
			void SetAT(const Standard_Real x) { theAT_ = x; }
			void SetTF(const Standard_Real x) { theTF_ = x; }
			void SetHB(const Standard_Real x) { theHB_ = x; }

			

		};

		// Forward Declarations [7/2/2023 Payvand]

		class HoltropResistance;

		Ostream& operator<<(Ostream&, const HoltropResistance&);

		class HoltropResistance
		{
			/*Private Data*/

			// frictional resistance
			Standard_Real theRF_;
			// Wave-making resistance
			Standard_Real theRW_;
			// Additional pressure resistance of immersed transom stern
			Standard_Real theRTR_;
			// Model-ship correlation resistance
			Standard_Real theRA_;

			Standard_Real theRTOT_;

		public:

			// default constructor [7/2/2023 Payvand]

			HoltropResistance()
				: theRF_(0)
				, theRW_(0)
				, theRTR_(0)
				, theRA_(0)
				, theRTOT_(0)
			{}

			// constructors [7/2/2023 Payvand]

			auto RF() const { return theRF_; }
			auto RW() const { return theRW_; }
			auto RTR() const { return theRTR_; }
			auto RA() const { return theRA_; }

			auto RTOT() const { return theRTOT_; }

			void SetRF(const Standard_Real x) { theRF_ = x; }
			void SetRW(const Standard_Real x) { theRW_ = x; }
			void SetRTR(const Standard_Real x) { theRTR_ = x; }
			void SetRA(const Standard_Real x) { theRA_ = x; }

			void SetRTOT(const Standard_Real x) { theRTOT_ = x; }

		};

		struct HoltropCoeffs
		{
			Standard_Real c1;
			Standard_Real c12;
			Standard_Real c13;
			Standard_Real c14;
			Standard_Real c2;
			Standard_Real c3;
			Standard_Real c4;
			Standard_Real c5;
			Standard_Real c6;
			Standard_Real c15;
			Standard_Real c16;
			Standard_Real c7;
			Standard_Real iE;
			Standard_Real landa;
			Standard_Real m1;
			Standard_Real m2;
			Standard_Real S;
			Standard_Real CA;
			Standard_Real _1plusK1; // Form factor

			Standard_Real CalcWaveResistance(const Standard_Real theVel, const Standard_Real theGravity, const Standard_Real theDensity, const Standard_Real theL, const Standard_Real theDispv);

			void CalcCoefficients(const ShipPrincipals&, const Standard_Real theCSTEM, const Standard_Real theLR);
		};

		struct Froudes
		{
			double Fni;
			double FnT;

			void CalcVariables(const ShipPrincipals&, const Standard_Real theVel, const Standard_Real theGravity);
		};

		enum class AftBodyForm
		{
			VSHAPE = 0,
			NORMAL,
			USHAPE,
			Pram
		};
	}
}

#endif // !_HydDyna_Holtrop_Veriables_Header
