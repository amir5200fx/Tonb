#pragma once
#ifndef _Marine_AnalysisSectionsReportIO_Header
#define _Marine_AnalysisSectionsReportIO_Header

#include <Global_Serialization.hxx>
#include <Marine_Module.hxx>

#include <memory>

namespace tnbLib
{

	namespace marineLib
	{

		namespace io
		{

			// Forward Declarations
			class AnalysisSections;

			class AnalysisSectionsReport
			{

				/*Private Data*/

				std::shared_ptr<AnalysisSections> theAnalysis_;

				Standard_Boolean validSections_;


				//- private functions and operators

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:

				static TnbMarine_EXPORT const std::string extention;

				//- default constructor

				AnalysisSectionsReport()
					: validSections_(Standard_False)
				{}


				//- constructors


				//- public functions and operators

				const auto& Analysis() const
				{
					return theAnalysis_;
				}

				auto Valid() const
				{
					return validSections_;
				}

				void LoadAnalysis(const std::shared_ptr<AnalysisSections>& theAnalysis)
				{
					theAnalysis_ = theAnalysis;
				}

				void SetValid(const Standard_Boolean valid)
				{
					validSections_ = valid;
				}
			};
		}
	}
}

#endif // !_Marine_AnalysisSectionsReportIO_Header
