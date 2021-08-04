#pragma once
#ifndef _Marine_AnalysisSectionsIO_Header
#define _Marine_AnalysisSectionsIO_Header

#include <Global_Serialization.hxx>
#include <Marine_Module.hxx>
#include <Cad2d_RemoveNonManifold.hxx>

#include <memory>

namespace tnbLib
{

	namespace marineLib
	{

		namespace io
		{

			// Forward Declarations
			class Sections;

			class AnalysisSections
			{

			public:

				class Section
				{

					/*Private Data*/

					std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> theSegments_;


					//- private functions and operators

					TNB_SERIALIZATION(TnbMarine_EXPORT);

				public:

					//- default constructor

					Section()
					{}

					//- public functions and operators

					const auto& Segments() const
					{
						return theSegments_;
					}

					auto& SegmentsRef()
					{
						return theSegments_;
					}

				};

			private:

				/*Private Data*/

				std::shared_ptr<Sections> theModel_;
				std::vector<std::shared_ptr<Section>> theSections_;
				

				//- private functions and operators

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:

				//- default constructor

				AnalysisSections()
				{}


				//- public functions and operators

				const auto& Model() const
				{
					return theModel_;
				}

				const auto& GetSections() const
				{
					return theSections_;
				}

				auto& SectionsRef()
				{
					return theSections_;
				}

				void LoadModel(const std::shared_ptr<Sections>& theModel)
				{
					theModel_ = theModel;
				}
			};
		}
	}
}

#endif // !_Marine_AnalysisSectionsIO_Header
