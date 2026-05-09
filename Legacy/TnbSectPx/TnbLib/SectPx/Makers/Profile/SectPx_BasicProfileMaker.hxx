#pragma once
#ifndef _SectPx_BasicProfileMaker_Header
#define _SectPx_BasicProfileMaker_Header

#include <SectPx_Maker.hxx>
#include <Global_Done.hxx>
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

		class BasicProfile
			: public SectPx_Maker<SectPx_FrameRegistry>
		{

			/*Private Data*/


			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<SectPx_Maker<SectPx_FrameRegistry>>(*this);
			}

		protected:

			BasicProfile()
			{}

			TnbSectPx_EXPORT Standard_Integer
				MakeEdge
				(
					const std::shared_ptr<SectPx_Pnt>& theP0,
					const std::shared_ptr<SectPx_Pnt>& theP1
				);

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Edge>
				RemoveEdge
				(
					const Standard_Integer theIndex
				);

			TnbSectPx_EXPORT void RemoveEdge
			(
				const std::shared_ptr<SectPx_Edge>& theEdge
			);

			static TnbSectPx_EXPORT void AddEdgeToPnt
			(
				const std::shared_ptr<SectPx_Edge>& theSeg,
				const std::shared_ptr<SectPx_Pnt>& thePnt
			);

		public:

			BasicProfile(const std::shared_ptr<SectPx_FrameRegistry>& theRegistry)
				: SectPx_Maker<SectPx_FrameRegistry>(theRegistry)
			{}

			TnbSectPx_EXPORT std::shared_ptr<SectPx_Edge>
				SelectEdge
				(
					const Standard_Integer theIndex
				) const;


			//- Returns index of the left and right edge that are created due to the
			//- inserting new point, respectively
			TnbSectPx_EXPORT std::tuple<Standard_Integer, Standard_Integer>
				ImportPnt
				(
					const std::shared_ptr<SectPx_Pnt>& thePnt,
					const std::shared_ptr<SectPx_Edge>& theEdge
				);

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::maker::BasicProfile);

#endif // !_SectPx_BasicProfileMaker_Header
