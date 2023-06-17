#pragma once
#ifndef _PtdShapeFit2d_TypedAirfoil_Header
#define _PtdShapeFit2d_TypedAirfoil_Header

#include <PtdShapeFit2d_Airfoil.hxx>
#include <Dir2d.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [5/1/2023 Payvand]
	class PtdShapeFit2d_TypedAirfoil_Offsets;

	class PtdShapeFit2d_TypedAirfoil
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

		struct anglePar
		{
			enum { id = 3 };
			static TnbPtdShapeFit_EXPORT const char* name;
			Standard_Real value;
		};

		static TnbPtdShapeFit_EXPORT std::map<Standard_Integer, const char*> ParsMap;

	private:

		/*Private Data*/

		Dir2d theDir_;

		std::shared_ptr<PtdShapeFit_Par> theXo_;
		std::shared_ptr<PtdShapeFit_Par> theYo_;
		std::shared_ptr<PtdShapeFit_Par> theAngle_;

		std::shared_ptr<PtdShapeFit_Par> theChordLen_;

		std::shared_ptr<PtdShapeFit2d_TypedAirfoil_Offsets> theOffsets_;

		// Private functions and operators [4/30/2023 Payvand]

		TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

	public:

		static TnbPtdShapeFit_EXPORT const unsigned int nb_parameters;
		static TnbPtdShapeFit_EXPORT unsigned short verbose;

		// default constructor [4/30/2023 Payvand]

		PtdShapeFit2d_TypedAirfoil()
			: theDir_(1.0, 0.0)
		{}


		// constructors [4/30/2023 Payvand]


		// Public functions and operators [4/30/2023 Payvand]

		const auto& OffsetPoints() const { return theOffsets_; }

		TnbPtdShapeFit_EXPORT const char*
			ParName(const Standard_Integer theIndex) const override;
		TnbPtdShapeFit_EXPORT Standard_Integer
			NbPars() const override;
		TnbPtdShapeFit_EXPORT Standard_Real
			CalcError
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
			RetrieveChromosome(const std::shared_ptr<Parameters>&) const override;

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

		const auto& ChordLen() const
		{
			return theChordLen_;
		}

		const auto& Angle() const
		{
			return theAngle_;
		}

		void SetXo(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theXo_ = x;
		}

		void SetYo(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theYo_ = x;
		}

		void SetChordLen(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theChordLen_ = x;
		}

		void SetAngle(const std::shared_ptr<PtdShapeFit_Par>& theAngle)
		{
			theAngle_ = theAngle;
		}

		void SetDir(const Dir2d& theDir)
		{
			theDir_ = theDir;
		}

		void SetDir(Dir2d&& theDir)
		{
			theDir_ = std::move(theDir);
		}

		void SetOffsets(const std::shared_ptr<PtdShapeFit2d_TypedAirfoil_Offsets>& theOffsets) 
		{ theOffsets_ = theOffsets; }

		static TnbPtdShapeFit_EXPORT Standard_Integer XoId();
		static TnbPtdShapeFit_EXPORT Standard_Integer YoId();
		static TnbPtdShapeFit_EXPORT Standard_Integer ChordLenId();
		static TnbPtdShapeFit_EXPORT Standard_Integer AngleId();

		static const char* XoName() { return xoPar::name; }
		static const char* YoName() { return yoPar::name; }
		static const char* ChordLenName() { return chordLenPar::name; }
		static const char* AngleName() { return anglePar::name; }

		static TnbPtdShapeFit_EXPORT Standard_Real GetXo(const std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT Standard_Real GetYo(const std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT Standard_Real GetChordLen(const std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT Standard_Real GetAngle(const std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT void InsertXo(const Standard_Real, std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT void InsertYo(const Standard_Real, std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT void InsertChordLen(const Standard_Real, std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT void InsertAngle(const Standard_Real, std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT std::tuple<xoPar, yoPar, chordLenPar, anglePar>
			RetrieveParameters(const std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT void CheckVector(const std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateXo(const Standard_Real theLower, const Standard_Real theUpper);
		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateYo(const Standard_Real theLower, const Standard_Real theUpper);
		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateChordLen(const Standard_Real theLower, const Standard_Real theUpper);
		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateAngle(const Standard_Real theLower, const Standard_Real theUpper);

		static TnbPtdShapeFit_EXPORT std::shared_ptr<Parameters>
			CreateParChromosome
			(
				const Standard_Real theXo,
				const Standard_Real theYo,
				const Standard_Real theAngle,
				const Standard_Real theChordLen
			);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdShapeFit2d_TypedAirfoil);

#endif // !_PtdShapeFit2d_TypedAirfoil_Header
