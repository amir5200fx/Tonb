#pragma once
#ifndef _ShapePx_TopoSectPole_BndAdaptor_Header
#define _ShapePx_TopoSectPole_BndAdaptor_Header

#include <Global_Serialization.hxx>
#include <ShapePx_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSectSegment;

	namespace shapePxLib
	{

		class TopoSectPole_BndAdaptor
		{

			/*Private Data*/

			std::weak_ptr<ShapePx_TopoSectSegment> theSegment_;


			//- Private functions and operators

			TNB_SERIALIZATION(TnbShapePx_EXPORT);

		protected:

			//- default constructor

			TopoSectPole_BndAdaptor()
			{}

			//- constructors


		public:

			//- public functions and operators

			const auto& Segment() const
			{
				return theSegment_;
			}

			void SetSegment(const std::shared_ptr<ShapePx_TopoSectSegment>& theSegment)
			{
				theSegment_ = theSegment;
			}
		};
	}
}

#endif // !_ShapePx_TopoSectPole_BndAdaptor_Header
