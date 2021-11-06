#pragma once
#ifndef _Marine_SectionsIO_Header
#define _Marine_SectionsIO_Header

#include <Global_Serialization.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;

	namespace marineLib
	{

		namespace io
		{

			// Forward Declarations
			class Shape;

			class Sections
			{

			public:

				class Section
				{

					/*Private Data*/

					std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

					Standard_Real theX_;

					// private functions and operators [7/28/2021 Amir]

					TNB_SERIALIZATION(TnbMarine_EXPORT);

				public:

					Section()
						: theX_(0)
					{}

					const auto& Edges() const
					{
						return theEdges_;
					}

					auto X() const
					{
						return theX_;
					}

					auto& EdgesRef()
					{
						return theEdges_;
					}

					void SetX(const Standard_Real x)
					{
						theX_ = x;
					}
				};

			private:

				/*Private Data*/

				std::shared_ptr<Shape> theShape_;
				std::vector<std::shared_ptr<Section>> theSections_;

				// private functions and operators [7/28/2021 Amir]

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:

				static TnbMarine_EXPORT const std::string extension;

				//- default constructor

				Sections()
				{}


				// public functions and operators [7/28/2021 Amir]

				const auto& GetShape() const
				{
					return theShape_;
				}

				const auto& GetSections() const
				{
					return theSections_;
				}

				auto& GetSectionsRef()
				{
					return theSections_;
				}

				void LoadShape(const std::shared_ptr<Shape>& theShape)
				{
					theShape_ = theShape;
				}

			};
		}
	}
}

#endif // !_Marine_SectionsIO_Header
