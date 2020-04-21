#pragma once
#ifndef _HydStatic_Model_Volume_Header
#define _HydStatic_Model_Volume_Header

#include <HydStatic_Model_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_WireFrameModel;
	class HydStatic_CrossCurves;

	namespace hydStcLib
	{

		class Model_Volume
			: public Model_Entity
		{

			/*Private Data*/

			std::shared_ptr<Marine_WireFrameModel> theModel_;
			std::shared_ptr<HydStatic_CrossCurves> theCrossCurves_;


			auto& ChangeCrossCurves()
			{
				return theCrossCurves_;
			}

		protected:

			Model_Volume();

			Model_Volume(const Standard_Integer theIndex);

			Model_Volume(const Standard_Integer theIndex, const word& theName);


		public:

			const auto& CrossCurves() const
			{
				return theCrossCurves_;
			}

			const auto& Model() const
			{
				return theModel_;
			}

			void LoadModel
			(
				const std::shared_ptr<Marine_WireFrameModel>& theModel
			)
			{
				theModel_ = theModel;
			}

		};
	}
}

#endif // !_HydStatic_Model_Volume_Header
