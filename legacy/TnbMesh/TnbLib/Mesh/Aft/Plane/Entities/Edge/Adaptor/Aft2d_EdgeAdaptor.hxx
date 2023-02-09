#pragma once
#ifndef _Aft2d_EdgeAdaptor_Header
#define _Aft2d_EdgeAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]
		class Aft2d_Element;

		class Aft2d_EdgeAdaptor
		{

			/*Private Data*/

			std::weak_ptr<Aft2d_Element> theLeft_;
			std::weak_ptr<Aft2d_Element> theRight_;


			// Private functions and operators [2/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_EdgeAdaptor()
			{}

			// constructors [2/1/2023 Payvand]


		public:

			// Public functions and operators [2/1/2023 Payvand]

			const auto& LeftElement() const
			{
				return theLeft_;
			}

			const auto& RightElement() const
			{
				return theRight_;
			}

			void SetLeftElement(const std::shared_ptr<Aft2d_Element>& theElement)
			{
				theLeft_ = theElement;
			}

			void SetRightElement(const std::shared_ptr<Aft2d_Element>& theElement)
			{
				theRight_ = theElement;
			}

		};
	}
}

#endif // !_Aft2d_EdgeAdaptor_Header
