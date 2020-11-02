#pragma once
#ifndef _Pln_WireAux_Header
#define _Pln_WireAux_Header

#include <Entity2d_Box.hxx>
#include <Pln_Orientation.hxx>
#include <Global_Serialization.hxx>
#include <Cad2d_Module.hxx>

namespace tnbLib
{

	class Pln_WireAux
	{

		/*Private Data*/

		Entity2d_Box theBoundingBox_;

		Pln_Orientation theOrientation_;


		/*private functions and operators*/

		DECLARE_SAVE_LOAD_HEADER(TnbCad2d_EXPORT);

	protected:

		Pln_WireAux()
		{}

		void SetBoundingBox(const Entity2d_Box&& theB);

		void SetOrientation(const Pln_Orientation theOrient);

	public:

		const auto& BoundingBox() const
		{
			return theBoundingBox_;
		}

		const auto Orientation() const
		{
			return theOrientation_;
		}
	};
}

#endif // !_Pln_WireAux_Header
