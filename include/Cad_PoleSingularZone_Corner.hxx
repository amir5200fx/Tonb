#pragma once
#ifndef _Cad_PoleSingularZone_Corner_Header
#define _Cad_PoleSingularZone_Corner_Header

#include <Cad_PoleSingularZone.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		struct PoleSingularZone_CornerBase
		{
			static TnbCad_EXPORT const word typeName;
		};

		template<class SurfPln>
		class PoleSingularZone_Corner
			: public Cad_PoleSingularZone<SurfPln>
			, public PoleSingularZone_CornerBase
		{

		public:

			typedef typename cad_singular_zone_traits<SurfPln>::curveType curveType;
			typedef Cad_PoleSingularZone<SurfPln> base;

		private:

			/*Private Data*/

			std::shared_ptr<curveType> theHorizon_;

		public:

			// default constructor [12/31/2021 Amir]

			PoleSingularZone_Corner()
			{}

			// constructors [12/31/2021 Amir]

			explicit PoleSingularZone_Corner(const Standard_Integer theIndex)
				: base(theIndex)
			{}

			PoleSingularZone_Corner(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
				: base(theIndex, thePlane)
			{}

			PoleSingularZone_Corner(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
				: base(theIndex, std::move(thePlane))
			{}

			explicit PoleSingularZone_Corner(std::shared_ptr<SurfPln>&& thePlane)
				: base(std::move(thePlane))
			{}

			explicit PoleSingularZone_Corner(const std::shared_ptr<SurfPln>& thePlane)
				: base(thePlane)
			{}

			PoleSingularZone_Corner
			(
				const std::shared_ptr<curveType>& theHorizon
			)
				: theHorizon_(theHorizon)
			{}

			PoleSingularZone_Corner
			(
				std::shared_ptr<curveType>&& theHorizon
			)
				: theHorizon_(std::move(theHorizon))
			{}

			PoleSingularZone_Corner
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SurfPln>& thePlane,
				const std::shared_ptr<curveType>& theHorizon
			)
				: base(theIndex, thePlane)
				, theHorizon_(theHorizon)
			{}

			PoleSingularZone_Corner
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

			Standard_Integer NbHorizons() const override;
			std::shared_ptr<curveType> Horizon(const Standard_Integer theIndex) const override;

		};
	}
}

#include <Cad_PoleSingularZone_CornerI.hxx>

#endif // !_Cad_PoleSingularZone_Corner_Header
