#pragma once
#ifndef _Marine_HullShapeIO_Header
#define _Marine_HullShapeIO_Header

#include <Marine_ShapeIO.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		namespace io
		{

			class HullShape
				: public Shape
			{

				/*Private Data*/

				gp_Ax2d theAx_;

				std::shared_ptr<Entity3d_Box> theBoundingBox_;

				Marine_BodyModelType theType_;

				//- private functions and operators

				TNB_SERIALIZATION(TnbMarine_EXPORT);

			public:


				//- default constructor

				HullShape()
				{}


				//- public functions and operators

				const auto& Ax() const
				{
					return theAx_;
				}

				const auto& PreciseBndBox() const
				{
					return theBoundingBox_;
				}

				auto ShapeType() const
				{
					return theType_;
				}

				TnbMarine_EXPORT std::shared_ptr<Entity3d_Box> BoundingBox() const override;

				void SetAx(const gp_Ax2d& ax)
				{
					theAx_ = ax;
				}

				void SetType(const Marine_BodyModelType t)
				{
					theType_ = t;
				}

				void SetPreciseBndBox(const std::shared_ptr<Entity3d_Box>& b)
				{
					theBoundingBox_ = b;
				}
			};
		}
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::io::HullShape);

#endif // !_Marine_HullShapeIO_Header
