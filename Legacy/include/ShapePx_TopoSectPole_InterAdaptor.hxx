#pragma once
#ifndef _ShapePx_TopoSectPole_InterAdaptor_Header
#define _ShapePx_TopoSectPole_InterAdaptor_Header

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

		class TopoSectPole_InterAdaptor
		{

			/*Private Data*/

			std::weak_ptr<ShapePx_TopoSectSegment> theBackward_;
			std::weak_ptr<ShapePx_TopoSectSegment> theForward_;


			//- Private functions and operators

			TNB_SERIALIZATION(TnbShapePx_EXPORT);

		public:

			//- default constructor

			TopoSectPole_InterAdaptor()
			{}


			//- constructors


			//- public functions and operators

			const auto& ForwardSegment() const
			{
				return theForward_;
			}

			const auto& BackwardSegment() const
			{
				return theBackward_;
			}

			void SetForwardSegment(const std::shared_ptr<ShapePx_TopoSectSegment>& theSegment)
			{
				theForward_ = theSegment;
			}

			void SetBackwardSegment(const std::shared_ptr<ShapePx_TopoSectSegment>& theSegment)
			{
				theBackward_ = theSegment;
			}
		};
	}
}

#endif // !_ShapePx_TopoSectPole_InterAdaptor_Header
