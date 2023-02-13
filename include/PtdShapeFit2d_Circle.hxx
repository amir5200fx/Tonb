#pragma once
#ifndef _PtdShapeFit2d_Circle_Header
#define _PtdShapeFit2d_Circle_Header

#include <PtdShapeFit_Section.hxx>
#include <Dir2d.hxx>

namespace tnbLib
{

	class PtdShapeFit2d_Circle
		: public PtdShapeFit_Section
	{

	public:

		struct xoPar
		{
			enum {id = 0};
			static TnbPtdShapeFit_EXPORT const char* name;
			Standard_Real value;
		};

		struct yoPar
		{
			enum { id = 1 };
			static TnbPtdShapeFit_EXPORT const char* name;
			Standard_Real value;
		};

		struct radiusPar
		{
			enum { id = 2 };
			static TnbPtdShapeFit_EXPORT const char* name;
			Standard_Real value;
		};

	private:

		/*Private Data*/

		Dir2d theDir_;

		std::shared_ptr<PtdShapeFit_Par> theXo_;
		std::shared_ptr<PtdShapeFit_Par> theYo_;

		std::shared_ptr<PtdShapeFit_Par> theRadius_;


		// Private functions and operators [2/10/2023 Payvand]

		TNB_SERIALIZATION(TnbPtdShapeFit_EXPORT);

	public:

		static TnbPtdShapeFit_EXPORT const unsigned int nb_parameters;
		static TnbPtdShapeFit_EXPORT unsigned short verbose;

		// default constructor [2/9/2023 Payvand]

		PtdShapeFit2d_Circle()
			: theXo_(0)
			, theYo_(0)
			, theRadius_(0)
			, theDir_(1.0, 0.0)
		{}


		// constructors [2/9/2023 Payvand]

		// public functions and operators [2/9/2023 Payvand]

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

		TnbPtdShapeFit_EXPORT std::vector<std::shared_ptr<PtdShapeFit_Par>> 
			RetrieveParList() const override;

		std::vector<Standard_Real> RetrieveChromosome(const std::shared_ptr<Parameters>&) const override;

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

		const auto& Radius() const
		{
			return theRadius_;
		}

		void SetXo(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theXo_ = x;
		}

		void SetYo(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theYo_ = x;
		}

		void SetRadius(const std::shared_ptr<PtdShapeFit_Par>& x)
		{
			theRadius_ = x;
		}

		void SetDir(const Dir2d& theDir)
		{
			theDir_ = theDir;
		}

		void SetDir(Dir2d&& theDir)
		{
			theDir_ = std::move(theDir);
		}

		static TnbPtdShapeFit_EXPORT Standard_Integer XoId();
		static TnbPtdShapeFit_EXPORT Standard_Integer YoId();
		static TnbPtdShapeFit_EXPORT Standard_Integer RadiusId();

		static const char* XoName() { return xoPar::name; }
		static const char* YoName() { return yoPar::name; }
		static const char* RadiusName() { return radiusPar::name; }

		static TnbPtdShapeFit_EXPORT Standard_Real GetXo(const std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT Standard_Real GetYo(const std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT Standard_Real GetRadius(const std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT void InsertXo(const Standard_Real, std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT void InsertYo(const Standard_Real, std::vector<Standard_Real>&);
		static TnbPtdShapeFit_EXPORT void InsertRadius(const Standard_Real, std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT std::tuple<xoPar, yoPar, radiusPar>
			RetrieveParameters(const std::vector<Standard_Real>&);
		
		static TnbPtdShapeFit_EXPORT void CheckVector(const std::vector<Standard_Real>&);

		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateXo(const Standard_Real theLower, const Standard_Real theUpper);
		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateYo(const Standard_Real theLower, const Standard_Real theUpper);
		static TnbPtdShapeFit_EXPORT std::shared_ptr<PtdShapeFit_Par> CreateRadius(const Standard_Real theLower, const Standard_Real theUpper);
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::PtdShapeFit2d_Circle);

#endif // !_PtdShapeFit2d_Circle_Header
