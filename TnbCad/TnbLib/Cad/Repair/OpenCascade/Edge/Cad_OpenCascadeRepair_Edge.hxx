#pragma once
#ifndef _Cad_OpenCascadeRepair_Edge_Header
#define _Cad_OpenCascadeRepair_Edge_Header

#include <Global_Done.hxx>

#include <Standard_Handle.hxx>
#include <TopoDS_Edge.hxx>

// Forward Declarations
class TopoDS_Edge;
class TopoDS_Face;

namespace tnbLib
{

	namespace cadLib
	{

		class OpenCascadeRepair_Edge
			: public Global_Done
		{

		public:

			enum class repairAlg
			{
				none,
				sameRange,
				sameParameter,
				all
			};

		private:

			/*Private Data*/

			TopoDS_Edge theEdge_;


			//- private functions and operators

			void ApplySameRange();
			void ApplySameParameter();
			void ApplyAll();

		public:

			static unsigned short verbose;

			//- default constructor

			OpenCascadeRepair_Edge()
			{}

			//- constructors

			//- public functions and operators

			const auto& Edge() const
			{
				return theEdge_;
			}

			void Perform(const repairAlg alg);

			void LoadEdge(const TopoDS_Edge& theEdge)
			{
				theEdge_ = theEdge;
			}
		};
	}
}

#endif // !_Cad_OpenCascadeRepair_Edge_Header
