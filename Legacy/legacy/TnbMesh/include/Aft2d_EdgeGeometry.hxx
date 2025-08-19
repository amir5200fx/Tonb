#pragma once
#ifndef _Aft2d_EdgeGeometry_Header
#define _Aft2d_EdgeGeometry_Header

#include <Mesh_Module.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_EdgeGeometry
		{

			/*Private Data*/

			Pnt2d theCentre_;

			Standard_Real theLength_;


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& theCentre_;
				ar& theLength_;
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_EdgeGeometry()
			{}


			// constructors [2/1/2023 Payvand]


		public:

			// Public functions and operators [2/1/2023 Payvand]

			const auto& Centre() const
			{
				return theCentre_;
			}

			auto& CentreRef()
			{
				return theCentre_;
			}

			auto CharLength() const
			{
				return theLength_;
			}

			auto& CharLengthRef()
			{
				return theLength_;
			}

			void SetCentre(const Pnt2d& theCoord)
			{
				theCentre_ = theCoord;
			}

			void SetCentre(Pnt2d&& theCoord)
			{
				theCentre_ = std::move(theCoord);
			}

			void SetCharLength(const Standard_Real theLength)
			{
				theLength_ = theLength;
			}
		};
	}
}

#endif // !_Aft2d_EdgeGeometry_Header
