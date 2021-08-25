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
			class DisctSections;

			class AnalysisSections
			{

			public:

				class Section
				{

					/*Private Data*/

					std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> theSegments_;

					Standard_Real theX_;

					//- private functions and operators

					TNB_SERIALIZATION(TnbMarine_EXPORT);

				public:

					//- default constructor

					Section()
						: theX_(0)
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

					auto X() const
					{
						return theX_;
					}

					void SetX(const Standard_Real x)
					{
						theX_ = x;
					}

				};

			private:

				/*Private Data*/

				std::shared_ptr<DisctSections> theModel_;
				std::vector<std::shared_ptr<Section>> theSections_;
				
				Standard_Real theMinTol_;
				Standard_Real theMaxTol_;

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

				auto MinTolerance() const
				{
					return theMinTol_;
				}

				auto MaxTolerance() const
				{
					return theMaxTol_;
				}

				auto& SectionsRef()
				{
					return theSections_;
				}

				void LoadModel(const std::shared_ptr<DisctSections>& theModel)
				{
					theModel_ = theModel;
				}

				void SetMinTolerance(const Standard_Real x)
				{
					theMinTol_ = x;
				}

				void SetMaxTolerance(const Standard_Real x)
				{
					theMaxTol_ = x;
				}
			};
		}
	}
}

#endif // !_Marine_AnalysisSectionsIO_Header
