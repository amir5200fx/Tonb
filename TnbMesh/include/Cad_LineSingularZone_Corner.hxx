#pragma once
#ifndef _Cad_LineSingularZone_Corner_Header
#define _Cad_LineSingularZone_Corner_Header

#include <Cad_LineSingularZone.hxx>

namespace tnbLib
{

	namespace cadLib
	{


		struct LineSingularZone_CornerBase
		{
			static TnbCad_EXPORT const word typeName;
		};

		template<class SurfPln>
		class LineSingularZone_Corner
			: public Cad_LineSingularZone<SurfPln>
			, public LineSingularZone_CornerBase
		{

		public:

			typedef typename cad_singular_zone_traits<SurfPln>::curveType curveType;
			typedef Cad_LineSingularZone<SurfPln> base;

		private:

			/*Private Data*/

			std::shared_ptr<curveType> theHorizon0_;
			std::shared_ptr<curveType> theHorizon1_;

		public:

			// default constructor [12/31/2021 Amir]

			LineSingularZone_Corner()
			{}

			// constructors [12/31/2021 Amir]

			explicit LineSingularZone_Corner(const Standard_Integer theIndex)
				: base(theIndex)
			{}

			LineSingularZone_Corner(const Standard_Integer theIndex, const std::shared_ptr<SurfPln>& thePlane)
				: base(theIndex, thePlane)
			{}

			LineSingularZone_Corner(const Standard_Integer theIndex, std::shared_ptr<SurfPln>&& thePlane)
				: base(theIndex, std::move(thePlane))
			{}

			explicit LineSingularZone_Corner(std::shared_ptr<SurfPln>&& thePlane)
				: base(std::move(thePlane))
			{}

			explicit LineSingularZone_Corner(const std::shared_ptr<SurfPln>& thePlane)
				: base(thePlane)
			{}

			LineSingularZone_Corner
			(
				const std::shared_ptr<curveType>& theHorizon0,
				const std::shared_ptr<curveType>& theHorizon1
			)
				: theHorizon0_(theHorizon0)
				, theHorizon1_(theHorizon1)
			{}

			LineSingularZone_Corner
			(
				std::shared_ptr<curveType>&& theHorizon0,
				std::shared_ptr<curveType>&& theHorizon1
			)
				: theHorizon0_(std::move(theHorizon0))
				, theHorizon1_(std::move(theHorizon1))
			{}

			LineSingularZone_Corner
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<SurfPln>& thePlane,
				const std::shared_ptr<curveType>& theHorizon0,
				const std::shared_ptr<curveType>& theHorizon1
			)
				: base(theIndex, thePlane)
				, theHorizon0_(theHorizon0)
				, theHorizon1_(theHorizon1)
			{}

			LineSingularZone_Corner
			(
				const Standard_Integer theIndex,
				std::shared_ptr<SurfPln>&& thePlane,
				std::shared_ptr<curveType>&& theHorizon0,
				std::shared_ptr<curveType>&& theHorizon1
			)
				: base(theIndex, std::move(thePlane))
				, theHorizon0_(std::move(theHorizon0))
				, theHorizon1_(std::move(theHorizon1))
			{}


			// public functions and operators [12/31/2021 Amir]

			const auto& Horizon0() const
			{
				return theHorizon0_;
			}

			const auto& Horizon1() const
			{
				return theHorizon1_;
			}

			void SetHorizon0(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon0_ = theCurve;
			}

			void SetHorizon0(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon0_ = std::move(theCurve);
			}

			void SetHorizon1(const std::shared_ptr<curveType>& theCurve)
			{
				theHorizon1_ = theCurve;
			}

			void SetHorizon1(std::shared_ptr<curveType>&& theCurve)
			{
				theHorizon1_ = std::move(theCurve);
			}


			// override functions and operators [12/31/2021 Amir]

			Cad_SingularType ZoneType() const override;

			Standard_Integer NbHorizons() const override;
			std::shared_ptr<curveType> Horizon(const Standard_Integer theIndex) const override;
		};
	}
}

#include <Cad_LineSingularZone_CornerI.hxx>

#endif // !_Cad_LineSingularZone_Corner_Header
