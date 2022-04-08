#pragma once
#ifndef _Cad_LineSingularZone_Header
#define _Cad_LineSingularZone_Header

#include <Cad_SingularZone.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<class SurfPln>
	class Cad_LineSingularZone
		: public Cad_SingularZone<SurfPln>
	{

	public:

		typedef typename cad_singular_zone_traits<SurfPln>::surfType surfType;

	private:

		/*Private Data*/

	protected:

		// default constructor [12/31/2021 Amir]

		Cad_LineSingularZone()
		{}

		// constructors [12/31/2021 Amir]

		explicit Cad_LineSingularZone(const Standard_Integer theIndex)
			: Cad_SingularZone<SurfPln>(theIndex)
		{}

		Cad_LineSingularZone(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
			: Cad_SingularZone<SurfPln>(theIndex, thePlane)
		{}

		Cad_LineSingularZone(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
			: Cad_SingularZone<SurfPln>(theIndex, std::move(thePlane))
		{}

		explicit Cad_LineSingularZone(const std::shared_ptr<SurfPln>& thePlane)
			: Cad_SingularZone<SurfPln>(thePlane)
		{}

		explicit Cad_LineSingularZone(std::shared_ptr<SurfPln>&& thePlane)
			: Cad_SingularZone<SurfPln>(std::move(thePlane))
		{}

	public:

		// public functions and operators [12/31/2021 Amir]

		Standard_Boolean IsLine() const override
		{
			return Standard_True;
		}

		void ProjectBoundariesToHorizons(const surfType&) override
		{
			NotImplemented;
		}
	};
}

#endif // !_Cad_LineSingularZone_Header
