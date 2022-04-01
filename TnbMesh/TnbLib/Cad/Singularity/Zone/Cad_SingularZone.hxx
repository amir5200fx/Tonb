#pragma once
#ifndef _Cad_SingularZone_Header
#define _Cad_SingularZone_Header

#include <word.hxx>
#include <Global_Indexed.hxx>
#include <Cad_SingularType.hxx>
#include <Cad_SingularZoneTraits.hxx>
#include <Mesh_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class SurfPln>
	class Cad_SingularZone
		: public Global_Indexed
	{

	public:

		typedef typename cad_singular_zone_traits<SurfPln>::curveType curveType;

	private:

		/*Private Data*/

		std::shared_ptr<SurfPln> thePlane_;

		std::vector<std::shared_ptr<curveType>> theCurves_;

	protected:

		// default constructor [12/31/2021 Amir]

		Cad_SingularZone()
		{}

		// constructors [12/31/2021 Amir]

		explicit Cad_SingularZone(const Standard_Integer theIndex)
			: Global_Indexed(theIndex)
		{}

		Cad_SingularZone(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
			: Global_Indexed(theIndex)
			, thePlane_(thePlane)
		{}

		Cad_SingularZone(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
			: Global_Indexed(theIndex)
			, thePlane_(std::move(thePlane))
		{}

		explicit Cad_SingularZone(std::shared_ptr<SurfPln>&& thePlane)
			: thePlane_(std::move(thePlane))
		{}

		explicit Cad_SingularZone(const std::shared_ptr<SurfPln>& thePlane)
			: thePlane_(thePlane)
		{}

	public:


		// public functions and operators [12/31/2021 Amir]

		virtual Cad_SingularType ZoneType() const = 0;
		virtual word ZoneTypeName() const = 0;

		virtual Standard_Integer NbHorizons() const = 0;
		virtual std::shared_ptr<curveType> Horizon(const Standard_Integer theIndex) const = 0;

		virtual Standard_Boolean IsPole() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsLine() const
		{
			return Standard_False;
		}

		const auto& Plane() const
		{
			return thePlane_;
		}

		const auto& Curves() const
		{
			return theCurves_;
		}

		void SetPlane(const std::shared_ptr<SurfPln>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void SetPlane(std::shared_ptr<SurfPln>&& thePlane)
		{
			thePlane_ = std::move(thePlane);
		}

	};
}

#endif // !_Cad_SingularZone_Header
