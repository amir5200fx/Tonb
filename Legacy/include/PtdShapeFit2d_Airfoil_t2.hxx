#pragma once
#ifndef _PtdShapeFit2d_Airfoil_t2_Header
#define _PtdShapeFit2d_Airfoil_t2_Header

#include <PtdShapeFit2d_Airfoil.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	namespace airfoilLib
	{

		class Type2
			: public PtdShapeFit2d_Airfoil
		{

		public:

			struct xoPar
			{
				enum { id = 0 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct yoPar
			{
				enum { id = 1 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct chordLenPar
			{
				enum { id = 2 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct maxCambPar
			{
				enum { id = 3 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct maxCambLocPar
			{
				enum { id = 4 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct leadCambSteepPar
			{
				enum { id = 5 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct leadCambSteepTightPar
			{
				enum { id = 6 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct leadCambSteepWeightPar
			{
				enum { id = 7 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailCambSteepPar
			{
				enum { id = 8 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailCambSteepTightPar
			{
				enum { id = 9 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailCambSteepWeightPar
			{
				enum { id = 10 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct maxThickPar
			{
				enum { id = 11 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct maxThickLocPar
			{
				enum { id = 12 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct leadThickSteepTight1Par
			{
				enum { id = 13 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct leadThickSteepTight2Par
			{
				enum { id = 14 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailThickSteepPar
			{
				enum { id = 15 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailThickSteepTightPar
			{
				enum { id = 16 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			struct trailThickSteepVelocityPar
			{
				enum { id = 17 };
				static TnbPtdShapeFit_EXPORT const char* name;
				Standard_Real value;
			};

			static TnbPtdShapeFit_EXPORT std::map<Standard_Integer, const char*> ParsMap;

		private:

			/*Private Data*/

			Dir2d theDir_;

			Standard_Integer theNbPoints_;

			// the parameters [4/30/2023 Payvand]

			std::shared_ptr<PtdShapeFit_Par> theXo_;
			std::shared_ptr<PtdShapeFit_Par> theYo_;

			std::shared_ptr<PtdShapeFit_Par> theChordLen_;

			std::shared_ptr<PtdShapeFit_Par> theMaxCamb_;
			std::shared_ptr<PtdShapeFit_Par> theMaxCambLoc_;
			std::shared_ptr<PtdShapeFit_Par> theLeadCambSteep_;
			std::shared_ptr<PtdShapeFit_Par> theLeadCambTight_;
			std::shared_ptr<PtdShapeFit_Par> theLeadCambWeight_;
			std::shared_ptr<PtdShapeFit_Par> theTrailCambSteep_;
			std::shared_ptr<PtdShapeFit_Par> theTrailCambTight_;
			std::shared_ptr<PtdShapeFit_Par> theTrailCambWeight_;

			std::shared_ptr<PtdShapeFit_Par> theMaxThick_;
			std::shared_ptr<PtdShapeFit_Par> theMaxThickLoc_;

			std::shared_ptr<PtdShapeFit_Par> theLeadThickSteepTight1_;
			std::shared_ptr<PtdShapeFit_Par> theLeadThickSteepTight2_;

			std::shared_ptr<PtdShapeFit_Par> theTrailThickSteep_;
			std::shared_ptr<PtdShapeFit_Par> theTrailThickSteepTight_;
			std::shared_ptr<PtdShapeFit_Par> theTrailThickSteepVelocity_;


			// Private functions and operators [4/30/2023 Payvand]

			TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

		public:

			static TnbPtdShapeFit_EXPORT const unsigned int nb_parameters;
			static TnbPtdShapeFit_EXPORT unsigned short verbose;

			// default constructor [4/30/2023 Payvand]

			Type2()
				: theDir_(1.0, 0.0)
				, theNbPoints_(60)
			{}

			// constructors [4/30/2023 Payvand]

			// Public functions and operators [4/30/2023 Payvand]

			TnbPtdShapeFit_EXPORT const char* ParName(const Standard_Integer theIndex) const override;
			TnbPtdShapeFit_EXPORT Standard_Integer NbPars() const override;
			TnbPtdShapeFit_EXPORT Standard_Real CalcError
			(
				const std::vector<Standard_Real>&,
				const std::shared_ptr<PtdShapeFit2d_ScatterMap>&
			) const override;

			TnbPtdShapeFit_EXPORT std::shared_ptr<Parameters>
				RetrieveParChromosome(const std::vector<Standard_Real>&) const override;

			TnbPtdShapeFit_EXPORT std::shared_ptr<Cad2d_Plane>
				RetrieveShape(const std::vector<Standard_Real>&) const override;

			TnbPtdShapeFit_EXPORT std::shared_ptr<Cad2d_Plane>
				ExportPlane(const std::vector<Standard_Real>&) const override;

			TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<PtdShapeFit_Par>>
				RetrieveParList() const override;

			TnbPtdShapeFit_EXPORT std::vector<Standard_Real>
				RetrieveChromosome
				(
					const std::shared_ptr<Parameters>&
				) const override;

			TnbPtdShapeFit_EXPORT void SetParameters(const std::vector<Standard_Real>&) override;

			auto NbOffsetPoints() const { return theNbPoints_; }

			const auto& Dir() const
			{
				return theDir_;
			}

			const auto& Xo() const
			{
				return theXo_;
			}

			const auto& Yo() const
			{
				return theYo_;
			}

			const auto& ChordLen() const { return theChordLen_; }

			const auto& MaxCamb() const { return theMaxCamb_; }
			const auto& MaxCambLoc() const { return theMaxCambLoc_; }
			const auto& LeadCambSteep() const { return theLeadCambSteep_; }
			const auto& LeadCambSteepTight() const { return theLeadCambTight_; }
			const auto& LeadCambSteepWeight() const { return theLeadCambWeight_; }
			const auto& TrailCambSteep() const { return theTrailCambSteep_; }
			const auto& TrailCambSteepTight() const { return theTrailCambTight_; }
			const auto& TrailCambSteepWeight() const { return theTrailCambWeight_; }

			const auto& MaxThick() const { return theMaxThick_; }
			const auto& MaxThickLoc() const { return theMaxThickLoc_; }
			const auto& LeadThickSteepTight1() const { return theLeadThickSteepTight1_; }
			const auto& LeadThickSteepTight2() const { return theLeadThickSteepTight2_; }
			const auto& TrailThickSteep() const { return theTrailThickSteep_; }
			const auto& TrailThickSteepTight() const { return theTrailThickSteepTight_; }
			const auto& TrailThickSteepVelocity() const { return theTrailThickSteepVelocity_; }

			void SetDir(const Dir2d& theDir)
			{
				theDir_ = theDir;
			}

			void SetDir(Dir2d&& theDir)
			{
				theDir_ = std::move(theDir);
			}

			void SetXo(const std::shared_ptr<PtdShapeFit_Par>& x)
			{
				theXo_ = x;
			}

			void SetYo(const std::shared_ptr<PtdShapeFit_Par>& x)
			{
				theYo_ = x;
			}

			void SetNbOffsetPoints(const Standard_Integer n)
			{
				theNbPoints_ = n;
			}

			void SetChordLen(const std::shared_ptr<PtdShapeFit_Par>& x) { theChordLen_ = x; }

			void SetMaxCamb(const std::shared_ptr<PtdShapeFit_Par>& x) { theMaxCamb_ = x; }
			void SetMaxCambLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theMaxCambLoc_ = x; }

			void SetLeadCambSteep(const std::shared_ptr<PtdShapeFit_Par>& x) { theLeadCambSteep_ = x; }
			void SetLeadCambSteepTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLeadCambTight_ = x; }
			void SetLeadCambSteepWeight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLeadCambWeight_ = x; }

			void SetTrailCambSteep(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailCambSteep_ = x; }
			void SetTrailCambSteepTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailCambTight_ = x; }
			void SetTrailCambSteepWeight(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailCambWeight_ = x; }

			void SetMaxThick(const std::shared_ptr<PtdShapeFit_Par>& x) { theMaxThick_ = x; }
			void SetMaxThickLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theMaxThickLoc_ = x; }

			void SetLeadThickSteepTight1(const std::shared_ptr<PtdShapeFit_Par>& x) { theLeadThickSteepTight1_ = x; }
			void SetLeadThickSteepTight2(const std::shared_ptr<PtdShapeFit_Par>& x) { theLeadThickSteepTight2_ = x; }

			void SetTrailThickSteep(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailThickSteep_ = x; }
			void SetTrailThickSteepTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailThickSteepTight_ = x; }
			void SetTrailThickSteepVelocity(const std::shared_ptr<PtdShapeFit_Par>& x) { theTrailThickSteepVelocity_ = x; }

			static TnbPtdShapeFit_EXPORT Standard_Integer XoId();
			static TnbPtdShapeFit_EXPORT Standard_Integer YoId();

			static TnbPtdShapeFit_EXPORT Standard_Integer ChordLenId();

			static TnbPtdShapeFit_EXPORT Standard_Integer MaxCambId();
			static TnbPtdShapeFit_EXPORT Standard_Integer MaxCambLocId();
			static TnbPtdShapeFit_EXPORT Standard_Integer LeadCambSteepId();
			static TnbPtdShapeFit_EXPORT Standard_Integer LeadCambSteepTightId();
			static TnbPtdShapeFit_EXPORT Standard_Integer LeadCambSteepWeightId();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailCambSteepId();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailCambSteepTightId();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailCambSteepWeightId();

			static TnbPtdShapeFit_EXPORT Standard_Integer MaxThickId();
			static TnbPtdShapeFit_EXPORT Standard_Integer MaxThickLocId();
			static TnbPtdShapeFit_EXPORT Standard_Integer LeadThickSteepTight1Id();
			static TnbPtdShapeFit_EXPORT Standard_Integer LeadThickSteepTight2Id();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailThickSteepId();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailThickSteepTightId();
			static TnbPtdShapeFit_EXPORT Standard_Integer TrailThickSteepVelocityId();

			static const char* XoName() { return xoPar::name; }
			static const char* YoName() { return yoPar::name; }
			static const char* ChordLenName() { return chordLenPar::name; }
			static const char* MaxCambName() { return maxCambPar::name; }
			static const char* MaxCambLocName() { return maxCambLocPar::name; }
			static const char* LeadCambSteepName() { return leadCambSteepPar::name; }
			static const char* LeadCambSteepTightName() { return leadCambSteepTightPar::name; }
			static const char* LeadCambSteepWeightName() { return leadCambSteepWeightPar::name; }
			static const char* TrailCambSteepName() { return trailCambSteepPar::name; }
			static const char* TrailCambSteepTightName() { return trailCambSteepTightPar::name; }
			static const char* TrailCambSteepWeightName() { return trailCambSteepWeightPar::name; }

			static const char* MaxThickName() { return maxThickPar::name; }
			static const char* MaxThickLocName() { return maxThickLocPar::name; }
			static const char* LeadThickSteepTight1Name() { return leadThickSteepTight1Par::name; }
			static const char* LeadThickSteepTight2Name() { return leadThickSteepTight2Par::name; }
			static const char* TrailThickSteepName() { return trailThickSteepPar::name; }
			static const char* TrailThickSteepTightName() { return trailThickSteepTightPar::name; }
			static const char* TrailThickSteepVelocityName() { return trailThickSteepVelocityPar::name; }

			static TnbPtdShapeFit_EXPORT Standard_Real GetXo(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetYo(const std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT Standard_Real GetChordLen(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetMaxCamb(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetMaxCambLoc(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetLeadCambSteep(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetLeadCambSteepTight(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetLeadCambSteepWeight(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailCambSteep(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailCambSteepTight(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailCambSteepWeight(const std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT Standard_Real GetMaxThick(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetMaxThickLoc(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetLeadThickSteepTight1(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetLeadThickSteepTight2(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailThickSteep(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailThickSteepTight(const std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT Standard_Real GetTrailThickSteepVelocity(const std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT void InsertXo(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertYo(const Standard_Real, std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT void InsertChordLen(const Standard_Real, std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT void InsertMaxCamb(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertMaxCambLoc(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertLeadCambSteep(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertLeadCambSteepTight(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertLeadCambSteepWeight(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailCambSteep(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailCambSteepTight(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailCambSteepWeight(const Standard_Real, std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT void InsertMaxThick(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertMaxThickLoc(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertLeadThickSteepTight1(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertLeadThickSteepTight2(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailThickSteep(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailThickSteepTight(const Standard_Real, std::vector<Standard_Real>&);
			static TnbPtdShapeFit_EXPORT void InsertTrailThickSteepVelocity(const Standard_Real, std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT std::tuple
				<
				xoPar,
				yoPar,
				chordLenPar,

				maxCambPar,
				maxCambLocPar,
				leadCambSteepPar,
				leadCambSteepTightPar,
				leadCambSteepWeightPar,
				trailCambSteepPar,
				trailCambSteepTightPar,
				trailCambSteepWeightPar,

				maxThickPar,
				maxThickLocPar,
				leadThickSteepTight1Par,
				leadThickSteepTight2Par,
				trailThickSteepPar,
				trailThickSteepTightPar,
				trailThickSteepVelocityPar
				>
				RetrieveParameters(const std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT void CheckVector(const std::vector<Standard_Real>&);

			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateXo(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateYo(const Standard_Real theLower, const Standard_Real theUpper);

			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateChordLen(const Standard_Real theLower, const Standard_Real theUpper);

			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateMaxCamb(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateMaxCambLoc(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLeadCambSteep(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLeadCambSteepTight(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLeadCambSteepWeight(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailCambSteep(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailCambSteepTight(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailCambSteepWeight(const Standard_Real theLower, const Standard_Real theUpper);

			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateMaxThick(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateMaxThickLoc(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLeadThickSteepTight1(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLeadThickSteepTight2(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailThickSteep(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailThickSteepTight(const Standard_Real theLower, const Standard_Real theUpper);
			static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateTrailThickSteepVelocity(const Standard_Real theLower, const Standard_Real theUpper);

			static TnbPtdShapeFit_EXPORT std::shared_ptr<Parameters>
				CreateParChromosome
				(
					const Standard_Real theXo,
					const Standard_Real theYo,

					const Standard_Real theChordLen,

					const Standard_Real theMaxCamb,
					const Standard_Real theMaxCambLoc,
					const Standard_Real theLeadCambSteep,
					const Standard_Real theLeadCambSteepTight,
					const Standard_Real theLeadCambSteepWeight,
					const Standard_Real theTrailCambSteep,
					const Standard_Real theTrailCambSteepTight,
					const Standard_Real theTrailCambSteepWeight,

					const Standard_Real theMaxThick,
					const Standard_Real theMaxThickLoc,
					const Standard_Real theLeadThickSteepTight1,
					const Standard_Real theLeadThickSteepTight2,
					const Standard_Real theTrailThickSteep,
					const Standard_Real theTrailThickSteepTight,
					const Standard_Real theTrailThickSteepVelocity
				);
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::airfoilLib::Type2);

#endif // !_PtdShapeFit2d_Airfoil_t2_Header
