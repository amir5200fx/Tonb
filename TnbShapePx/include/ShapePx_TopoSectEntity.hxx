#pragma once
#ifndef _ShapePx_TopoSectEntity_Header
#define _ShapePx_TopoSectEntity_Header

#include <ShapePx_Entity.hxx>

namespace tnbLib
{

	class ShapePx_TopoSectEntity
		: public ShapePx_Entity
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<ShapePx_Entity>(*this);
		}

	protected:


		//- default constructor

		ShapePx_TopoSectEntity()
		{}


		//- constructors

		ShapePx_TopoSectEntity(const Standard_Integer theIndex)
			: ShapePx_Entity(theIndex)
		{}

		ShapePx_TopoSectEntity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: ShapePx_Entity(theIndex, theName)
		{}

	public:

		//- public functions and operators

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ShapePx_TopoSectEntity);

#endif // !_ShapePx_TopoSectEntity_Header
