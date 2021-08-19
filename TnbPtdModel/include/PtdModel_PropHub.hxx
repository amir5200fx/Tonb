#pragma once
#ifndef _PtdModel_PropHub_Header
#define _PtdModel_PropHub_Header

#include <PtdModel_Entity.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class PtdModel_PropHubSection;
	class PtdModel_PropBlade;
	class PtdModel_Profiles;
	class PtdModel_PropHubPars;
	class PtdModel_Face;
	class PtdModel_Par;

	class PtdModel_PropHub
		: public PtdModel_Entity
		, public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<PtdModel_PropBlade> theBlade_;
		std::shared_ptr<PtdModel_PropHubPars> theParameters_;

		std::shared_ptr<PtdModel_PropHubSection> theSection_;


		std::vector<std::shared_ptr<PtdModel_Face>> theFaces_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbPtdModel_EXPORT);

	protected:

		// default constructor

		PtdModel_PropHub()
		{}


		//- constructors

		TnbPtdModel_EXPORT PtdModel_PropHub
		(
			const std::shared_ptr<PtdModel_PropBlade>& theBlade, 
			const std::shared_ptr<PtdModel_PropHubPars>&,
			const std::shared_ptr<PtdModel_PropHubSection>& theSection
		);

		TnbPtdModel_EXPORT PtdModel_PropHub
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<PtdModel_PropBlade>& theBlade,
			const std::shared_ptr<PtdModel_PropHubPars>&, 
			const std::shared_ptr<PtdModel_PropHubSection>& theSection
		);


		//- protected functions and operators

		virtual void Revolve() = 0;


		void SetFaces(std::vector<std::shared_ptr<PtdModel_Face>>&& theFaces)
		{
			theFaces_ = std::move(theFaces);
		}

	public:


		//- public functions and operators

		const auto& Blade() const
		{
			return theBlade_;
		}

		const auto& Parameters() const
		{
			return theParameters_;
		}

		const auto& Section() const
		{
			return theSection_;
		}

		const auto& Faces() const
		{
			return theFaces_;
		}

		TnbPtdModel_EXPORT void Perform();

		TnbPtdModel_EXPORT void LoadBlade(const std::shared_ptr<PtdModel_PropBlade>&);
		TnbPtdModel_EXPORT void LoadParameters(const std::shared_ptr<PtdModel_PropHubPars>&);

		TnbPtdModel_EXPORT void LoadSection(const std::shared_ptr<PtdModel_PropHubSection>&);
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::PtdModel_PropHub);

#endif // !_PtdModel_PropHub_Header
