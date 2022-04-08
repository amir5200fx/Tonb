#pragma once
#ifndef _Cad_LineSingularZone_WholeSide_Header
#define _Cad_LineSingularZone_WholeSide_Header

#include <Cad_LineSingularZone.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		struct LineSingularZone_WholeSideBase
		{
			static TnbMesh_EXPORT const word typeName;
		};

		template<class SurfPln>
		class LineSingularZone_WholeSide
			: public Cad_LineSingularZone<SurfPln>
			, public LineSingularZone_WholeSideBase
		{

		public:

			typedef typename cad_singular_zone_traits<SurfPln>::curveType curveType;
			typedef Cad_LineSingularZone<SurfPln> base;

		private:

			/*Private Data*/

			std::shared_ptr<curveType> theHorizon_;

		public:


			// default constructor [12/31/2021 Amir]

			LineSingularZone_WholeSide()
			{}

			// constructors [12/31/2021 Amir]

			explicit LineSingularZone_WholeSide(const Standard_Integer theIndex)
				: base(theIndex)
			{}

			LineSingularZone_WholeSide(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
				: base(theIndex, thePlane)
			{}

			LineSingularZone_WholeSide(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
				: base(theIndex, std::move(thePlane))
			{}

			explicit LineSingularZone_WholeSide(std::shared_ptr<SurfPln>&& thePlane)
				: base(std::move(thePlane))
			{}

			explicit LineSingularZone_WholeSide(const std::shared_ptr<SurfPln>& thePlane)
				: base(thePlane)
			{}

			LineSingularZone_WholeSide
			(
				const std::shared_ptr<curveType>& theHorizon
			)
				: theHorizon_(theHorizon)
			{}

			LineSingularZone_WholeSide
			(
				std::shared_ptr<curveType>&& theHorizon
			)
				: theHorizon_(std::move(theHorizon))
			{}

			LineSingularZone_WholeSide
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SurfPln>& thePlane,
				const std::shared_ptr<curveType>& theHorizon
			)
				: base(theIndex, thePlane)
				, theHorizon_(theHorizon)
			{}

			LineSingularZone_WholeSide
			(
				const Standard_Integer theIndex,
				std::shared_ptr<SurfPln>&& thePlane,
				std::shared_ptr<curveType>&& theHorizon
			)
				: base(theIndex, std::move(thePlane))
				, theHorizon_(std::move(theHorizon))
			{}


			// public functions and operators [12/31/2021 Amir]

			const auto& Horizon() const
			{
				return theHorizon_;
			}

			void SetHorizon(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon_ = theCurve;
			}

			void SetHorizon(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon_ = std::move(theCurve);
			}

			// override functions and operators [12/31/2021 Amir]

			Cad_SingularType ZoneType() const override;
			word ZoneTypeName() const override;

			Standard_Integer NbHorizons() const override;
			std::shared_ptr<curveType> Horizon(const Standard_Integer theIndex) const override;
		};
	}
}

#include <Cad_LineSingularZone_WholeSideI.hxx>

#endif // !_Cad_LineSingularZone_WholeSide_Header
