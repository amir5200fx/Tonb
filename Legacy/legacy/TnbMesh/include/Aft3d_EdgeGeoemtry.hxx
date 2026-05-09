#pragma once
#ifndef _Aft3d_EdgeGeoemtry_Header
#define _Aft3d_EdgeGeoemtry_Header

#include <Mesh_Module.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_EdgeGeoemtry
		{

			/*Private Data*/

			Pnt3d theCentre_;

			Standard_Real theLength_;

			// Private functions and operators [2/23/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar& theCentre_;
				ar& theLength_;
			}

		protected:

			// default constructor [2/23/2023 Payvand]

			Aft3d_EdgeGeoemtry()
			{}


			// constructors [2/23/2023 Payvand]

		public:


			// Public functions and operators [2/23/2023 Payvand]

			const auto& Centre() const { return theCentre_; }
			auto& CentreRef() { return theCentre_; }

			auto CharLength() const { return theLength_; }
			auto& CharLengthRef() { return theLength_; }

			void SetCentre(const Pnt3d& theCoord) { theCentre_ = theCoord; }
			void SetCoord(Pnt3d&& theCoord) { theCentre_ = std::move(theCoord); }

			void SetCharLength(const Standard_Real theLength) { theLength_ = theLength; }

		};
	}
}

#endif // !_Aft3d_EdgeGeoemtry_Header
