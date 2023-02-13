#pragma once
#ifndef _PtdShapeFit_Section_Header
#define _PtdShapeFit_Section_Header

#include <PtdShapeFit_Module.hxx>
#include <Global_Serialization.hxx>

#include <vector>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [2/9/2023 Payvand]
	class PtdShapeFit2d_ScatterMap;
	class PtdShapeFit_Par;
	class Cad2d_Plane;
	class Pln_Curve;
	class Pnt2d;

	class PtdShapeFit_Section
	{

	public:

		struct Param
		{
			Standard_Real x;
			word name;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar& x;
				ar& name;
			}
		};

		struct Parameters
		{
			std::vector<Param> x;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar& x;
			}
		};

	private:

		/*Private Data*/


		std::shared_ptr<Parameters> theParameters_;

		// Private functions and operators [2/9/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& theParameters_;		
		}

	protected:

		// default constructor [2/9/2023 Payvand]

		PtdShapeFit_Section()
		{}

		// constructors [2/9/2023 Payvand]


		// Protected functions and operators [2/12/2023 Payvand]

		auto& ParsRef()
		{
			return theParameters_;
		}

	public:

		static TnbPtdShapeFit_EXPORT const std::string extension;

		// Public functions and operators [2/9/2023 Payvand]	

		const auto& Pars() const
		{
			return theParameters_;
		}

		virtual Standard_Integer NbPars() const = 0;
		virtual Standard_Real CalcError(const std::vector<Standard_Real>&, const std::shared_ptr<PtdShapeFit2d_ScatterMap>&) const = 0;

		virtual std::shared_ptr<Parameters> RetrieveParChromosome(const std::vector<Standard_Real>&) const = 0;
		virtual std::shared_ptr<Cad2d_Plane> RetrieveShape(const std::vector<Standard_Real>&) const = 0;
		virtual std::vector<std::shared_ptr<PtdShapeFit_Par>> RetrieveParList() const = 0;
		virtual std::vector<Standard_Real> RetrieveChromosome(const std::shared_ptr<Parameters>&) const = 0;

		virtual void SetParameters(const std::vector<Standard_Real>&) = 0;

		static TnbPtdShapeFit_EXPORT Standard_Real 
			CalcDistance(const Pnt2d&, const Pln_Curve&);

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit_Section);

#endif // !_PtdShapeFit_Section_Header
