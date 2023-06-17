#pragma once
#ifndef _PtdShapeFit2d_AirfoilGlobal_t1_Header
#define _PtdShapeFit2d_AirfoilGlobal_t1_Header

#include <PtdShapeFit2d_AirfoilGlobal.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	namespace curveLib
	{

		namespace airfoilLib
		{

			class Global_t1
				: public PtdShapeFit2d_AirfoilGlobal
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

				struct noseAnglePar
				{
					enum { id = 2 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct chordLenPar
				{
					enum { id = 3 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxPar
				{
					enum { id = 4 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxLocPar
				{
					enum { id = 5 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperNoseTightPar
				{
					enum { id = 6 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxTightPar
				{
					enum { id = 7 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperTrailAnglePar
				{
					enum { id = 8 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxVelPar
				{
					enum { id = 9 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperTrailVelPar
				{
					enum { id = 10 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxPar
				{
					enum { id = 11 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxLocPar
				{
					enum { id = 12 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerNoseTightPar
				{
					enum { id = 13 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxTightPar
				{
					enum { id = 14 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerTrailAnglePar
				{
					enum { id = 15 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxVelPar
				{
					enum { id = 16 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerTrailVelPar
				{
					enum { id = 17 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				static TnbPtdShapeFit_EXPORT std::map<Standard_Integer, const char*> ParsMap;

			private:

				/*Private Data*/

				Dir2d theDir_;

				// the Parameters [5/7/2023 Payvand]

				std::shared_ptr<PtdShapeFit_Par> theXo_;
				std::shared_ptr<PtdShapeFit_Par> theYo_;

				std::shared_ptr<PtdShapeFit_Par> theNoseAngle_;

				std::shared_ptr<PtdShapeFit_Par> theChordLen_;

				std::shared_ptr<PtdShapeFit_Par> theUpperMax_;
				std::shared_ptr<PtdShapeFit_Par> theUpperMaxLoc_;
				std::shared_ptr<PtdShapeFit_Par> theUpperNoseTight_;
				std::shared_ptr<PtdShapeFit_Par> theUpperMaxTight_;
				std::shared_ptr<PtdShapeFit_Par> theUpperTrailAngle_;
				std::shared_ptr<PtdShapeFit_Par> theUpperMaxVel_;
				std::shared_ptr<PtdShapeFit_Par> theUpperTrailVel_;

				std::shared_ptr<PtdShapeFit_Par> theLowerMax_;
				std::shared_ptr<PtdShapeFit_Par> theLowerMaxLoc_;
				std::shared_ptr<PtdShapeFit_Par> theLowerNoseTight_;
				std::shared_ptr<PtdShapeFit_Par> theLowerMaxTight_;
				std::shared_ptr<PtdShapeFit_Par> theLowerTrailAngle_;
				std::shared_ptr<PtdShapeFit_Par> theLowerMaxVel_;
				std::shared_ptr<PtdShapeFit_Par> theLowerTrailVel_;

				// Private functions and operators [5/7/2023 Payvand]

				TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

			public:

				static TnbPtdShapeFit_EXPORT const unsigned int nb_parameters;
				static TnbPtdShapeFit_EXPORT unsigned short verbose;

				// default constructor [5/7/2023 Payvand]

				Global_t1()
				{}

				// constructors [5/7/2023 Payvand]

				// Public functions and operators [5/7/2023 Payvand]

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

				const auto& NoseAngle() const { return theNoseAngle_; }

				const auto& ChordLen() const { return theChordLen_; }

				const auto& UpperMax() const { return theUpperMax_; }
				const auto& UpperMaxLoc() const { return theUpperMaxLoc_; }
				const auto& UpperNoseTight() const { return theUpperNoseTight_; }
				const auto& UpperMaxTight() const { return theUpperMaxTight_; }
				const auto& UpperTrailAngle() const { return theUpperTrailAngle_; }
				const auto& UpperMaxVel() const { return theUpperMaxVel_; }
				const auto& UpperTrailVel() const { return theUpperTrailVel_; }

				const auto& LowerMax() const { return theLowerMax_; }
				const auto& LowerMaxLoc() const { return theLowerMaxLoc_; }
				const auto& LowerNoseTight() const { return theLowerNoseTight_; }
				const auto& LowerMaxTight() const { return theLowerMaxTight_; }
				const auto& LowerTrailAngle() const { return theLowerTrailAngle_; }
				const auto& LowerMaxVel() const { return theLowerMaxVel_; }
				const auto& LowerTrailVel() const { return theLowerTrailVel_; }


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

				void SetNoseAngle(const std::shared_ptr<PtdShapeFit_Par>& x) { theNoseAngle_ = x; }

				void SetChordLen(const std::shared_ptr<PtdShapeFit_Par>& x) { theChordLen_ = x; }

				void SetUpperMax(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMax_ = x; }
				void SetUpperMaxLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMaxLoc_ = x; }
				void SetUpperNoseTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperNoseTight_ = x; }
				void SetUpperMaxTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMaxTight_ = x; }
				void SetUpperTrailAngle(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperTrailAngle_ = x; }
				void SetUpperMaxVel(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMaxVel_ = x; }
				void SetUpperTrailVel(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperTrailVel_ = x; }

				void SetLowerMax(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMax_ = x; }
				void SetLowerMaxLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMaxLoc_ = x; }
				void SetLowerNoseTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerNoseTight_ = x; }
				void SetLowerMaxTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMaxTight_ = x; }
				void SetLowerTrailAngle(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerTrailAngle_ = x; }
				void SetLowerMaxVel(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMaxVel_ = x; }
				void SetLowerTrailVel(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerTrailVel_ = x; }

				static Standard_Integer XoId() { return xoPar::id; }
				static Standard_Integer YoId() { return yoPar::id; }

				static Standard_Integer NoseAngleId() { return noseAnglePar::id; }

				static Standard_Integer ChordLenId() { return chordLenPar::id; }

				static Standard_Integer UpperMaxId() { return upperMaxPar::id; }
				static Standard_Integer UpperMaxLocId() { return upperMaxLocPar::id; }
				static Standard_Integer UpperNoseTightId() { return upperNoseTightPar::id; }
				static Standard_Integer UpperMaxTightId() { return upperMaxTightPar::id; }
				static Standard_Integer UpperTrailAngleId() { return upperTrailAnglePar::id; }
				static Standard_Integer UpperMaxVelId() { return upperMaxVelPar::id; }
				static Standard_Integer UpperTrailVelId() { return upperTrailVelPar::id; }

				static Standard_Integer LowerMaxId() { return lowerMaxPar::id; }
				static Standard_Integer LowerMaxLocId() { return lowerMaxLocPar::id; }
				static Standard_Integer LowerNoseTightId() { return lowerNoseTightPar::id; }
				static Standard_Integer LowerMaxTightId() { return lowerMaxTightPar::id; }
				static Standard_Integer LowerTrailAngleId() { return lowerTrailAnglePar::id; }
				static Standard_Integer LowerMaxVelId() { return lowerMaxVelPar::id; }
				static Standard_Integer LowerTrailVelId() { return lowerTrailVelPar::id; }

				static const char* XoName() { return xoPar::name; }
				static const char* YoName() { return yoPar::name; }

				static const char* NoseAngleName() { return noseAnglePar::name; }

				static const char* ChordLenName() { return chordLenPar::name; }

				static const char* UpperMaxName() { return upperMaxPar::name; }
				static const char* UpperMaxLocName() { return upperMaxLocPar::name; }
				static const char* UpperNoseTightName() { return upperNoseTightPar::name; }
				static const char* UpperMaxTightName() { return upperMaxTightPar::name; }
				static const char* UpperTrailAngleName() { return upperTrailAnglePar::name; }
				static const char* UpperMaxVelName() { return upperMaxVelPar::name; }
				static const char* UpperTrailVelName() { return upperTrailVelPar::name; }

				static const char* LowerMaxName() { return lowerMaxPar::name; }
				static const char* LowerMaxLocName() { return lowerMaxLocPar::name; }
				static const char* LowerNoseTightName() { return lowerNoseTightPar::name; }
				static const char* LowerMaxTightName() { return lowerMaxTightPar::name; }
				static const char* LowerTrailAngleName() { return lowerTrailAnglePar::name; }
				static const char* LowerMaxVelName() { return lowerMaxVelPar::name; }
				static const char* LowerTrailVelName() { return lowerTrailVelPar::name; }

				static TnbPtdShapeFit_EXPORT Standard_Real GetXo(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetYo(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetNoseAngle(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetChordLen(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMax(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMaxLoc(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperNoseTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMaxTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperTrailAngle(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMaxVel(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperTrailVel(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMax(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMaxLoc(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerNoseTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMaxTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerTrailAngle(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMaxVel(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerTrailVel(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertXo(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertYo(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertNoseAngle(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertChordLen(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertUpperMax(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperMaxLoc(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperNoseTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperMaxTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperTrailAngle(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperMaxVel(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperTrailVel(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertLowerMax(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerMaxLoc(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerNoseTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerMaxTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerTrailAngle(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerMaxVel(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerTrailVel(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT std::tuple
					<
					xoPar,
					yoPar,

					noseAnglePar,

					chordLenPar,

					upperMaxPar,
					upperMaxLocPar,
					upperNoseTightPar,
					upperMaxTightPar,
					upperTrailAnglePar,
					upperMaxVelPar,
					upperTrailVelPar,

					lowerMaxPar,
					lowerMaxLocPar,
					lowerNoseTightPar,
					lowerMaxTightPar,
					lowerTrailAnglePar,
					lowerMaxVelPar,
					lowerTrailVelPar
					>
					RetrieveParameters(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void CheckVector(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateXo(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateYo(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateNoseAngle(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateChordLen(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMax(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMaxLoc(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperNoseTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMaxTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperTrailAngle(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMaxVel(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperTrailVel(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMax(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMaxLoc(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerNoseTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMaxTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerTrailAngle(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMaxVel(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerTrailVel(const Standard_Real theLower, const Standard_Real theUpper);


				static TnbPtdShapeFit_EXPORT std::shared_ptr<Parameters>
					CreateParChromosome
					(
						const Standard_Real theXo,
						const Standard_Real theYo,

						const Standard_Real theNoseAngle,

						const Standard_Real theChordLen,

						const Standard_Real theUpperMax,
						const Standard_Real theUpperMaxLoc,
						const Standard_Real theUpperNoseTight,
						const Standard_Real theUpperMaxTight,
						const Standard_Real theUpperTrailAngle,
						const Standard_Real theUpperMaxVel,
						const Standard_Real theUpperTrailVel,

						const Standard_Real theLowerMax,
						const Standard_Real theLowerMaxLoc,
						const Standard_Real theLowerNoseTight,
						const Standard_Real theLowerMaxTight,
						const Standard_Real theLowerTrailAngle,
						const Standard_Real theLowerMaxVel,
						const Standard_Real theLowerTrailVel
					);
			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::curveLib::airfoilLib::Global_t1);

#endif // !_PtdShapeFit2d_AirfoilGlobal_t1_Header
