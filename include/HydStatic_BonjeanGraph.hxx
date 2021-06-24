#pragma once
#ifndef _HydStatic_BonjeanGraph_Header
#define _HydStatic_BonjeanGraph_Header

#include <HydStatic_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_CmpSection;
	class HydStatic_BnjCurve;

	class HydStatic_BonjeanGraph
		: public HydStatic_Entity
	{

	public:

		class GraphSect
		{

			/*Private Data*/

			std::shared_ptr<Marine_CmpSection> theSection_;
			std::vector<std::shared_ptr<HydStatic_BnjCurve>> theCurves_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:

			//- default constructor

			GraphSect()
			{}

			//- constructors

			TnbHydStatic_EXPORT GraphSect
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				std::vector<std::shared_ptr<HydStatic_BnjCurve>>&& theCurves
			);

			TnbHydStatic_EXPORT GraphSect
			(
				const std::shared_ptr<Marine_CmpSection>& theSection,
				const std::vector<std::shared_ptr<HydStatic_BnjCurve>>& theCurves
			);


			//- public functions and operators


			inline Standard_Integer NbSections() const;

			const auto& Section() const
			{
				return theSection_;
			}

			const auto& Curves() const
			{
				return theCurves_;
			}

			inline void SetSection(const std::shared_ptr<Marine_CmpSection>&);
			inline void SetCurves(std::vector<std::shared_ptr<HydStatic_BnjCurve>>&&);
			inline void SetCurves(const std::vector<std::shared_ptr<HydStatic_BnjCurve>>&);
			
		};


	private:

		/*Private Data*/


		std::vector<std::shared_ptr<GraphSect>> theSections_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<HydStatic_Entity>(*this);
			ar & theSections_;
		}

	public:

		//- default constructor

		HydStatic_BonjeanGraph()
		{}


		//- constructors

		TnbHydStatic_EXPORT HydStatic_BonjeanGraph(std::vector<std::shared_ptr<GraphSect>>&&);

		//- public functions and operators

		inline Standard_Integer NbSections() const;


		const auto& Sections() const
		{
			return theSections_;
		}

		inline void SetSections(std::vector<std::shared_ptr<GraphSect>>&&);
	};
}

#include <HydStatic_BonjeanGraphI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::HydStatic_BonjeanGraph);

#endif // !_HydStatic_BonjeanGraph_Header
