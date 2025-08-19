#pragma once
#ifndef _PtdShapeFit2d_AirfoilNose_t2_Header
#define _PtdShapeFit2d_AirfoilNose_t2_Header

#include <PtdShapeFit2d_AirfoilNose.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	namespace curveLib
	{

		namespace airfoilLib
		{

			class Type2
				: public PtdShapeFit2d_AirfoilNose
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

				struct upperMaxPar
				{
					enum { id = 3 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxLocPar
				{
					enum { id = 4 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct upperMaxAnglePar
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

				struct upperTightPar
				{
					enum { id = 7 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxPar
				{
					enum { id = 8 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxLocPar
				{
					enum { id = 9 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerMaxAnglePar
				{
					enum { id = 10 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerNoseTightPar
				{
					enum { id = 11 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				struct lowerTightPar
				{
					enum { id = 12 };
					static TnbPtdShapeFit_EXPORT const char* name;
					Standard_Real value;
				};

				static TnbPtdShapeFit_EXPORT std::map<Standard_Integer, const char*> ParsMap;

			private:

				/*Private Data*/

				Dir2d theDir_;

				// the Parameters [5/5/2023 Payvand]

				std::shared_ptr<PtdShapeFit_Par> theXo_;
				std::shared_ptr<PtdShapeFit_Par> theYo_;

				std::shared_ptr<PtdShapeFit_Par> theNoseAngle_;

				std::shared_ptr<PtdShapeFit_Par> theUpperMaxLoc_;
				std::shared_ptr<PtdShapeFit_Par> theUpperMax_;
				std::shared_ptr<PtdShapeFit_Par> theUpperMaxAngle_;
				std::shared_ptr<PtdShapeFit_Par> theUpperNoseTight_;
				std::shared_ptr<PtdShapeFit_Par> theUpperTight_;

				std::shared_ptr<PtdShapeFit_Par> theLowerMaxLoc_;
				std::shared_ptr<PtdShapeFit_Par> theLowerMax_;
				std::shared_ptr<PtdShapeFit_Par> theLowerMaxAngle_;
				std::shared_ptr<PtdShapeFit_Par> theLowerNoseTight_;
				std::shared_ptr<PtdShapeFit_Par> theLowerTight_;


				// Private functions and operators [5/5/2023 Payvand]

				TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

			public:


				static TnbPtdShapeFit_EXPORT const unsigned int nb_parameters;
				static TnbPtdShapeFit_EXPORT unsigned short verbose;

				// default constructor [5/5/2023 Payvand]

				Type2()
				{}

				// constructors [5/5/2023 Payvand]

				// Public functions and operators [5/5/2023 Payvand]

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

				const auto& UpperMax() const { return theUpperMax_; }
				const auto& UpperMaxLoc() const { return theUpperMaxLoc_; }
				const auto& UpperMaxAngle() const { return theUpperMaxAngle_; }
				const auto& UpperNoseTight() const { return theUpperNoseTight_; }
				const auto& UpperTight() const { return theUpperTight_; }

				const auto& LowerMax() const { return theLowerMax_; }
				const auto& LowerMaxLoc() const { return theLowerMaxLoc_; }
				const auto& LowerMaxAngle() const { return theLowerMaxAngle_; }
				const auto& LowerNoseTight() const { return theLowerNoseTight_; }
				const auto& LowerTight() const { return theLowerTight_; }

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

				void SetUpperMax(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMax_ = x; }
				void SetUpperMaxLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMaxLoc_ = x; }
				void SetUpperMaxAngle(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperMaxAngle_ = x; }
				void SetUpperNoseTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperNoseTight_ = x; }
				void SetUpperTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theUpperTight_ = x; }

				void SetLowerMax(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMax_ = x; }
				void SetLowerMaxLoc(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMaxLoc_ = x; }
				void SetLowerMaxAngle(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerMaxAngle_ = x; }
				void SetLowerNoseTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerNoseTight_ = x; }
				void SetLowerTight(const std::shared_ptr<PtdShapeFit_Par>& x) { theLowerTight_ = x; }

				static TnbPtdShapeFit_EXPORT Standard_Integer XoId();
				static TnbPtdShapeFit_EXPORT Standard_Integer YoId();

				static TnbPtdShapeFit_EXPORT Standard_Integer NoseAngleId();

				static TnbPtdShapeFit_EXPORT Standard_Integer UpperMaxId();
				static TnbPtdShapeFit_EXPORT Standard_Integer UpperMaxLocId();
				static TnbPtdShapeFit_EXPORT Standard_Integer UpperMaxAngleId();
				static TnbPtdShapeFit_EXPORT Standard_Integer UpperNoseTightId();
				static TnbPtdShapeFit_EXPORT Standard_Integer UpperTightId();

				static TnbPtdShapeFit_EXPORT Standard_Integer LowerMaxId();
				static TnbPtdShapeFit_EXPORT Standard_Integer LowerMaxLocId();
				static TnbPtdShapeFit_EXPORT Standard_Integer LowerMaxAngleId();
				static TnbPtdShapeFit_EXPORT Standard_Integer LowerNoseTightId();
				static TnbPtdShapeFit_EXPORT Standard_Integer LowerTightId();

				static const char* XoName() { return xoPar::name; }
				static const char* YoName() { return yoPar::name; }

				static const char* NoseAngleName() { return noseAnglePar::name; }

				static const char* UpperMaxName() { return upperMaxPar::name; }
				static const char* UpperMaxLocName() { return upperMaxLocPar::name; }
				static const char* UpperMaxAngleName() { return upperMaxAnglePar::name; }
				static const char* UpperNoseTightName() { return upperNoseTightPar::name; }
				static const char* UpperTightName() { return upperTightPar::name; }

				static const char* LowerMaxName() { return lowerMaxPar::name; }
				static const char* LowerMaxLocName() { return lowerMaxLocPar::name; }
				static const char* LowerMaxAngleName() { return lowerMaxAnglePar::name; }
				static const char* LowerNoseTightName() { return lowerNoseTightPar::name; }
				static const char* LowerTightName() { return lowerTightPar::name; }

				static TnbPtdShapeFit_EXPORT Standard_Real GetXo(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetYo(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetNoseAngle(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMax(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMaxLoc(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperMaxAngle(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperNoseTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetUpperTight(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMax(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMaxLoc(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerMaxAngle(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerNoseTight(const std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT Standard_Real GetLowerTight(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertXo(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertYo(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertNoseAngle(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertUpperMax(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperMaxLoc(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperMaxAngle(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperNoseTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertUpperTight(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void InsertLowerMax(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerMaxLoc(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerMaxAngle(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerNoseTight(const Standard_Real, std::vector<Standard_Real>&);
				static TnbPtdShapeFit_EXPORT void InsertLowerTight(const Standard_Real, std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT std::tuple
					<
					xoPar,
					yoPar,

					noseAnglePar,

					upperMaxPar,
					upperMaxLocPar,
					upperMaxAnglePar,
					upperNoseTightPar,
					upperTightPar,

					lowerMaxPar,
					lowerMaxLocPar,
					lowerMaxAnglePar,
					lowerNoseTightPar,
					lowerTightPar
					>
					RetrieveParameters(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT void CheckVector(const std::vector<Standard_Real>&);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateXo(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateYo(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateNoseAngle(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMax(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMaxLoc(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperMaxAngle(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperNoseTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateUpperTight(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMax(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMaxLoc(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerMaxAngle(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerNoseTight(const Standard_Real theLower, const Standard_Real theUpper);
				static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateLowerTight(const Standard_Real theLower, const Standard_Real theUpper);

				static TnbPtdShapeFit_EXPORT std::shared_ptr<Parameters>
					CreateParChromosome
					(
						const Standard_Real theXo,
						const Standard_Real theYo,

						const Standard_Real theNoseAngle,

						const Standard_Real theUpperMax,
						const Standard_Real theUpperMaxLoc,
						const Standard_Real theUpperMaxAngle,
						const Standard_Real theUpperNoseTight,
						const Standard_Real theUpperTight,

						const Standard_Real theLowerMax,
						const Standard_Real theLowerMaxLoc,
						const Standard_Real theLowerMaxAngle,
						const Standard_Real theLowerNoseTight,
						const Standard_Real theLowerTight
					);
			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::curveLib::airfoilLib::Type2);

#endif // !_PtdShapeFit2d_AirfoilNose_t2_Header
