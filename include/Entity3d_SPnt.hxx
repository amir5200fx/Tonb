#pragma once
#ifndef _Entity3d_SPnt_Header
#define _Entity3d_SPnt_Header

#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [6/13/2023 Payvand]
	class Entity3d_SPnt;
	class OFstream;

	TnbGeo_EXPORT std::ostream& operator<<(std::ostream& os, const Entity3d_SPnt&);
	TnbGeo_EXPORT std::istream& operator>>(std::istream& is, Entity3d_SPnt&);

	TnbGeo_EXPORT Ostream& operator<<(Ostream& os, const Entity3d_SPnt&);
	TnbGeo_EXPORT Istream& operator>>(Istream& is, Entity3d_SPnt&);

	
	class Entity3d_SPnt
	{

		/*Private Data*/

		Pnt3d theCoord_;
		Pnt2d thePara_;


		// Private functions and operators [6/11/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& theCoord_;
			ar& thePara_;
		}

	public:

		typedef Entity3d_SPnt ptType;


		// static members [6/13/2023 Payvand]
		static TnbGeo_EXPORT const Entity3d_SPnt null;

		enum
		{
			dim = 3
		};

		// default constructor [6/11/2023 Payvand]

		Entity3d_SPnt()
			: theCoord_(Pnt3d::null)
			, thePara_(Pnt2d::null)
		{}


		// constructors [6/11/2023 Payvand]

		Entity3d_SPnt(const Pnt3d& theCoord, const Pnt2d& thePara)
			: theCoord_(theCoord)
			, thePara_(thePara)
		{}

		Entity3d_SPnt(Pnt3d&& theCoord, Pnt2d&& thePara)
			: theCoord_(std::move(theCoord))
			, thePara_(std::move(thePara))
		{}


		// Public functions and operators [6/11/2023 Payvand]

		const auto& Coord() const
		{
			return theCoord_;
		}

		const auto& Para() const
		{
			return thePara_;
		}

		auto& CoordRef() { return theCoord_; }
		auto& ParaRef() { return thePara_; }

		void SetCoord(const Pnt3d& theCoord) { theCoord_ = theCoord; }
		void SetCoord(Pnt3d&& theCoord) { theCoord_ = std::move(theCoord); }
		void SetPara(const Pnt2d& thePara) { thePara_ = thePara; }
		void SetPara(Pnt2d&& thePara) { thePara_ = std::move(thePara); }

		void Transform(const gp_Trsf& t) { theCoord_.Transform(t); }

	};
}

#endif // !_Entity3d_SPnt_Header
