#pragma once
#ifndef _Cad_PoleSingularZone_Header
#define _Cad_PoleSingularZone_Header

#include <Cad_SingularZone.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<class SurfPln>
	class Cad_PoleSingularZone
		: public Cad_SingularZone<SurfPln>
	{

	public:

		typedef typename cad_singular_zone_traits<SurfPln>::surfType surfType;

	private:

		/*Private Data*/

		Pnt2d theCoord_;

	protected:

		// default constructor [12/31/2021 Amir]

		Cad_PoleSingularZone()
		{}

		// constructors [12/31/2021 Amir]

		explicit Cad_PoleSingularZone(const Standard_Integer theIndex)
			: Cad_SingularZone<SurfPln>(theIndex)
		{}

		Cad_PoleSingularZone(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
			: Cad_SingularZone<SurfPln>(theIndex, thePlane)
		{}

		Cad_PoleSingularZone(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
			: Cad_SingularZone<SurfPln>(theIndex, std::move(thePlane))
		{}

		explicit Cad_PoleSingularZone(const std::shared_ptr<SurfPln>& thePlane)
			: Cad_SingularZone<SurfPln>(thePlane)
		{}

		explicit Cad_PoleSingularZone(std::shared_ptr<SurfPln>&& thePlane)
			: Cad_SingularZone<SurfPln>(std::move(thePlane))
		{}


	public:


		const auto& Coord() const
		{
			return theCoord_;
		}

		void SetCoord(const Pnt2d& theCoord)
		{
			theCoord_ = theCoord;
		}

		void SetCoord(Pnt2d&& theCoord)
		{
			theCoord_ = std::move(theCoord);
		}

		// override functions and operators [12/31/2021 Amir]

		Standard_Boolean IsPole() const override
		{
			return Standard_True;
		}

		void ProjectBoundariesToHorizons(const surfType&) override;

	};
}

#include <Cad_PoleSingularZoneI.hxx>

#endif // !_Cad_PoleSingularZone_Header
