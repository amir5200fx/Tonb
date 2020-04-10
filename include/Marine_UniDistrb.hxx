#pragma once
#ifndef _Marine_UniDistrb_Header
#define _Marine_UniDistrb_Header

#include <Marine_Distrb.hxx>
#include <Global_Bound.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	class Marine_UniDistrb
		: public Marine_Distrb
		, public Global_Bound<Standard_Real>
	{

		/*Private Data*/

		Standard_Integer theSize_;

	public:

		Marine_UniDistrb()
		{}

		Marine_UniDistrb
		(
			const Standard_Real x0,
			const Standard_Real x1, 
			const Standard_Integer n
		);

		auto Size() const
		{
			return theSize_;
		}

		void Perform();

		void SetSize
		(
			const Standard_Integer theSize
		)
		{
			theSize_ = theSize;
		}


		static std::shared_ptr<Marine_Distrb> 
			xDistb
			(
				const Entity3d_Box& theDomain,
				const Standard_Integer theSize
			);

		static std::shared_ptr<Marine_Distrb> 
			zDistb
			(
				const Entity3d_Box& theDomain,
				const Standard_Integer theSize
			);

		static std::shared_ptr<Marine_Distrb> 
			xOneStepForwardDistb
			(
				const Entity3d_Box& theDomain,
				const Standard_Integer theSize
			);

		static std::shared_ptr<Marine_Distrb>
			zOneStepForwardDistb
			(
				const Entity3d_Box& theDomain,
				const Standard_Integer theSize
			);
	};
}

#endif // !_Marine_UniDistrb_Header
