#pragma once
#ifndef _SectPx_TopoProfileMaker_Header
#define _SectPx_TopoProfileMaker_Header

#include <SectPx_Maker.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;
	class SectPx_Pnt;
	class SectPx_Node;
	class SectPx_Cloud;

	namespace maker
	{

		class TopoProfile
			: public SectPx_Maker
		{

			/*Private Data*/

		public:

			TopoProfile
			(
				const std::shared_ptr<SectPx_Registry>& theReg
			)
				: SectPx_Maker(theReg)
			{}


			std::shared_ptr<SectPx_TopoProfile>
				SelectProfile
				(
					const Standard_Integer theIndex
				) const;

			Standard_Integer
				CreateCustomProfile
				(
					const std::shared_ptr<SectPx_Pnt>& theP0,
					const std::shared_ptr<SectPx_Pnt>& theP1
				);

			Standard_Integer
				CreateCustomProfile
				(
					const std::shared_ptr<SectPx_Node>& theNode0,
					const std::shared_ptr<SectPx_Node>& theNode1
				);

			Standard_Integer 
				CreateInterplProfile
				(
					const std::shared_ptr<SectPx_Cloud>& theCloud
				);

			std::shared_ptr<SectPx_TopoProfile>
				RemoveProfile
				(
					const Standard_Integer theIndex
				);

			std::vector<std::shared_ptr<SectPx_TopoProfile>>
				RetrieveProfiles() const;

			void RetrieveProfilesTo
			(
				std::vector<std::shared_ptr<SectPx_TopoProfile>>& theProfiles
			) const;

			void Print(OSstream& out) const;
		};
	}
}

#endif // !_SectPx_TopoProfileMaker_Header
