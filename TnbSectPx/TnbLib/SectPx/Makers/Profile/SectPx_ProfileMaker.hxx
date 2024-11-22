#pragma once
#ifndef _SectPx_ProfileMaker_Header
#define _SectPx_ProfileMaker_Header

#include <SectPx_BasicProfileMaker.hxx>
#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class SectPx_Edge;
	class SectPx_ProfileQ;
	class SectPx_TopoProfile;
	class SectPx_Node;
	class SectPx_FrameRegistry;

	namespace maker
	{

		class Profile
			: public BasicProfile
		{

			/*Private Data*/

			std::shared_ptr<SectPx_TopoProfile> theProfile_;


			TNB_SERIALIZATION(TnbSectPx_EXPORT);

		protected:
			// default constructor
			Profile() = default;

		public:

			// constructors
			Profile
			(
				const std::shared_ptr<SectPx_TopoProfile>& theProfile,
				const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
			)
				: BasicProfile(theRegistry)
				, theProfile_(theProfile)
			{}

			// Public functions and operators

			const auto& TopoProfile() const
			{
				return theProfile_;
			}

			TnbSectPx_EXPORT const std::shared_ptr<SectPx_Node>& Node0() const;

			TnbSectPx_EXPORT const std::shared_ptr<SectPx_Node>& Node1() const;

			//Standard_Integer Init();

			TnbSectPx_EXPORT Standard_Boolean
				IsOnBoundary
				(
					const std::shared_ptr<SectPx_Pnt>& thePnt
				) const;

			//- returns index of the new edge that is created after removing the point
			//- WARNING! throws an exception if the point is in the boundary
			TnbSectPx_EXPORT Standard_Integer
				RemovePnt
				(
					const std::shared_ptr<SectPx_Pnt>& thePnt
				);

			TnbSectPx_EXPORT std::shared_ptr<SectPx_ProfileQ>
				RetrieveProfileQ() const;

			TnbSectPx_EXPORT Handle(Geom2d_Curve) RetrieveGeomCurve(const Standard_Integer deg) const;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::Profile);

#endif // !_SectPx_ProfileMaker_Header
