#pragma once
#ifndef _ShapePx_TopoSectNodeAdaptor_Header
#define _ShapePx_TopoSectNodeAdaptor_Header

#include <Global_Serialization.hxx>
#include <ShapePx_Module.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSectProfile;

	class ShapePx_TopoSectNodeAdaptor
	{

		/*Private Data*/

		std::weak_ptr<ShapePx_TopoSectProfile> theProfile_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);

	protected:

		//- default constructor

		ShapePx_TopoSectNodeAdaptor()
		{}


		//- constructors


	public:

		//- public functions and operators

		const auto& Profile() const
		{
			return theProfile_;
		}

		void SetProfile(const std::shared_ptr<ShapePx_TopoSectProfile>& theProfile)
		{
			theProfile_ = theProfile;
		}
	};
}

#endif // !_ShapePx_TopoSectNodeAdaptor_Header
