#pragma once
#ifndef _HydStatic_SolutionData_Bonjean_Header
#define _HydStatic_SolutionData_Bonjean_Header

#include <Global_Serialization.hxx>
#include <Marine_BodiesFwd.hxx>
#include <HydStatic_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Domain;
	class Marine_Graph;

	namespace hydStcLib
	{

		class SolutionData_Bonjean
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Body_Displacer> theBody_;
			std::shared_ptr<Marine_Domain> theDomain_;


			std::shared_ptr<Marine_Graph> theGraph_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);

		public:

			//- default constructor

			SolutionData_Bonjean()
			{}


			//- constructors

			explicit SolutionData_Bonjean
			(
				const std::shared_ptr<marineLib::Body_Displacer>& theBody
			)
				: theBody_(theBody)
			{}


			//- public functions and operators

			const auto& Body() const
			{
				return theBody_;
			}

			const auto& Domain() const
			{
				return theDomain_;
			}

			const auto& Graph() const
			{
				return theGraph_;
			}

			void LoadBody(const std::shared_ptr<marineLib::Body_Displacer>& theBody)
			{
				theBody_ = theBody;
			}

			void LoadDomain(const std::shared_ptr<Marine_Domain>& theDomain)
			{
				theDomain_ = theDomain;
			}

			void SetGraph(const std::shared_ptr<Marine_Graph>& theGraph)
			{
				theGraph_ = theGraph;
			}
		};
	}
}

#endif // !_HydStatic_SolutionData_Bonjean_Header
