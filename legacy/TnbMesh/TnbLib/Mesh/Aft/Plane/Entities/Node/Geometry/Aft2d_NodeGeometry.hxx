#pragma once
#ifndef _Aft2d_NodeGeometry_Header
#define _Aft2d_NodeGeometry_Header

#include <Pnt2d.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_NodeGeometry
		{

		public:

			class frontSpecs
			{

				/*Private Data*/
				
				Standard_Real theRadius_ = 0;
				Standard_Real theMaxL_ = 0;

				Standard_Boolean onCavity_ = Standard_False;


				// Private functions and operators [2/1/2023 Payvand]

				friend class boost::serialization::access;

				template<class Archive>
				void serialize(Archive& ar, const unsigned int file_version)
				{
					ar& theRadius_;
					ar& theMaxL_;

					ar& onCavity_;
				}

			public:

				// default constructor [2/1/2023 Payvand]

				frontSpecs()
				{}

				// constructors [2/1/2023 Payvand]


				// Public functions and operators [2/1/2023 Payvand]

				auto Radius() const
				{
					return theRadius_;
				}

				auto& RadiusRef()
				{
					return theRadius_;
				}

				auto MaxL() const
				{
					return theMaxL_;
				}

				auto& MaxLRef()
				{
					return theMaxL_;
				}

				auto OnCavity() const
				{
					return onCavity_;
				}

				auto& onCavityRef()
				{
					return onCavity_;
				}

				void SetRadius(const Standard_Real);
				void SetMaxL(const Standard_Real);

				void SetCavityCond(const Standard_Boolean);

			};

		private:

			/*Private Data*/

			Pnt2d theCoord_;

			frontSpecs theFrontSpecs_;


			// Private functions and operators [2/1/2023 Payvand]

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& theCoord_;
				ar& theFrontSpecs_;
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_NodeGeometry()
			{}

			// constructors [2/1/2023 Payvand]

			explicit Aft2d_NodeGeometry(const Pnt2d& theCoord)
				: theCoord_(theCoord)
			{}

			Aft2d_NodeGeometry(Pnt2d&& theCoord)
				: theCoord_(std::move(theCoord))
			{}

		public:

			// Public functions and operators [2/1/2023 Payvand]

			const auto& Coord() const
			{
				return theCoord_;
			}

			auto& CoordRef()
			{
				return theCoord_;
			}

			const auto& FrontSpecs() const
			{
				return theFrontSpecs_;
			}

			auto& FrontSpacsRef()
			{
				return theFrontSpecs_;
			}

			void SetCoord(const Pnt2d&);
			void SetCoord(Pnt2d&&);

			void SetFrontSpacs(const frontSpecs&);
			void SetFrontSpacs(frontSpecs&&);
		};
	}
}

#endif // !_Aft2d_NodeGeometry_Header
