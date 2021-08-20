#pragma once
#ifndef _Marine_DisctSectionsIO_Header
#define _Marine_DisctSectionsIO_Header

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
			class Sections;

			class DisctSections
			{

			public:

				struct AlgInfo
				{

					Standard_Real Deflection;
					Standard_Real Angle;
					Standard_Real minSize;

					Standard_Integer maxNbSubdivision;
					Standard_Integer initNbSubdivision;
					Standard_Integer nbSmaples;

					AlgInfo();

					TNB_SERIALIZATION(TnbMarine_EXPORT);
				};

			private:

				/*Private Data*/

				std::shared_ptr<Sections> theSections_;

				std::shared_ptr<AlgInfo> theInfo_;


				// private functions and operators [8/19/2021 Amir]

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:

				DisctSections()
				{}

				//- public functions and operators

				const auto& GetSections() const
				{
					return theSections_;
				}

				const auto& GetInfo() const
				{
					return theInfo_;
				}

				auto& GetInfoRef()
				{
					return theInfo_;
				}

				void LoadSections(const std::shared_ptr<Sections>& theSections)
				{
					theSections_ = theSections;
				}

				void SetInfo(const std::shared_ptr<AlgInfo>& theInfo)
				{
					theInfo_ = theInfo;
				}

				void SetInfo(std::shared_ptr<AlgInfo>&& theInfo)
				{
					theInfo_ = std::move(theInfo);
				}
			};
		}
	}
}

#endif // !_Marine_DisctSectionsIO_Header
