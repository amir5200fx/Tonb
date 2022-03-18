#pragma once
#ifndef _Aft2d_StdOptNodeSurface_Info_Header
#define _Aft2d_StdOptNodeSurface_Info_Header

#include <Standard_TypeDef.hxx>

#include <Global_Serialization.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	class Aft2d_StdOptNodeSurface_Info
	{

		/*Private Data*/

		Standard_Real theTolerance_;

		Standard_Integer theMaxIter_;


		// private functions and operators [2/24/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theTolerance_;
			ar & theMaxIter_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_ITERS;

		// default constructor [2/24/2022 Amir]

		Aft2d_StdOptNodeSurface_Info()
			: theTolerance_(DEFAULT_TOLERANCE)
			, theMaxIter_(DEFAULT_MAX_ITERS)
		{}

		// constructors [2/24/2022 Amir]

		Aft2d_StdOptNodeSurface_Info(const Standard_Real theTol, const Standard_Integer theMaxIters)
			: theTolerance_(theTol)
			, theMaxIter_(theMaxIters)
		{}


		// public functions and operators [2/24/2022 Amir]

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto MaxIters() const
		{
			return theMaxIter_;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}

		void SetMaxIters(const Standard_Integer theMaxIters)
		{
			theMaxIter_ = theMaxIters;
		}
	};
}

#endif // !_Aft2d_StdOptNodeSurface_Info_Header
