#pragma once
#ifndef _PtdShapeFit_Shape_Header
#define _PtdShapeFit_Shape_Header

#include <PtdShapeFit_Section.hxx>
#include <PtdShapeFit_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_Indexed.hxx>
#include <Global_Named.hxx>

#include <memory>

#include <gp_Ax1.hxx>

namespace tnbLib
{

	// Forward Declarations [2/12/2023 Payvand]
	class PtdShapeFit_Section;
	class Cad_Shape;

	class PtdShapeFit_Shape
		: public Global_Indexed
		, public Global_Named
	{

		/*Private Data*/


		// Private functions and operators [2/12/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Global_Indexed>(*this);
			ar& boost::serialization::base_object<Global_Named>(*this);
		}

	protected:

		// default constructor [2/12/2023 Payvand]

		PtdShapeFit_Shape()
		{}

		// constructors [2/12/2023 Payvand]

		PtdShapeFit_Shape(const Standard_Integer theIndex, const word& theName)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
		{}

		
	public:

		static TnbPtdShapeFit_EXPORT const std::string extension;

		virtual ~PtdShapeFit_Shape()
		{}

		// Public functions and operators [2/12/2023 Payvand]


		virtual std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>> 
			CalcParameters
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections, 
				const gp_Ax1& theAxis,
				const std::vector<Standard_Real>& theXs
			) const = 0;

		virtual std::shared_ptr<Cad_Shape> 
			CreateShape
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section::Parameters>>&,
				const std::shared_ptr<PtdShapeFit_Section>&,
				const gp_Ax1&, 
				const std::vector<Standard_Real>&
			) const = 0;

		virtual std::shared_ptr<Cad_Shape> 
			CreateExtrapolated
			(
				const std::vector<std::pair<std::shared_ptr<PtdShapeFit_Section::Parameters>, Standard_Real>>&,
				const std::shared_ptr<PtdShapeFit_Section>&,
				const gp_Ax1&,
				const std::vector<Standard_Real>&
			) const = 0;

		static TnbPtdShapeFit_EXPORT std::pair
			<
			std::vector<std::shared_ptr<PtdShapeFit_Section>>, 
			std::vector<Standard_Real>
			> 
			Sort
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections,
				const std::vector<Standard_Real>& theXs
			);

		static TnbPtdShapeFit_EXPORT std::vector<std::vector<Standard_Real>>
			RetrieveChromosomes
			(
				const std::vector<std::shared_ptr<PtdShapeFit_Section>>& theSections
			);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdShapeFit_Shape);

#endif // !_PtdShapeFit_Shape_Header
