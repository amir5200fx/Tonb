#pragma once
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{
	namespace Io
	{

		template<class Type, size_t nbVAR>
		void WriteFiled
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			OFstream & File
		)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteFiled()")
					<< "Filed size and Points size not equal"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(File);
				File << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					File << x[I] << "  ";
				File << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteFiled(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt2d>& thePoints,
			std::stringstream& theStream)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteFiled()")
					<< "Filed size and Points size not equal"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(theStream);
				theStream << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					theStream << x[I] << "  ";
				theStream << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteFiled
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			OFstream & File
		)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteFiled()")
					<< "Filed size and Points size not equal"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(File);
				File << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					File << x[I] << "  ";
				File << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteFiled(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt3d>& thePoints,
			std::stringstream& theStream)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteFiled()")
					<< "Filed size and Points size not equal"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(theStream);
				theStream << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					theStream << x[I] << "  ";
				theStream << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var,
			OFstream & File
		)
		{
			if (var.size() != Triangles.size())
			{
				FatalErrorIn("void WriteCellCenteredField()")
					<< "Filed size and Triangles size not equal"
					<< abort(FatalError);
			}

			for (const auto& x : var)
			{
				forThose(Index, 0, nbVAR - 1)
					File << x[Index] << "  ";
				File << endl;
			}

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var, std::stringstream& theStream)
		{
			if (var.size() != Triangles.size())
			{
				FatalErrorIn("void WriteCellCenteredField()")
					<< "Filed size and Triangles size not equal"
					<< abort(FatalError);
			}

			for (const auto& x : var)
			{
				forThose(Index, 0, nbVAR - 1)
					theStream << x[Index] << "  ";
				theStream << "\n";
			}

			for (const auto& x : Triangles)
			{
				theStream << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			File << Variables << endl;

			WriteFeTriangleZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				File
			);

			WriteFiled
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			theStream << Variables << "\n";

			WriteFeTriangleZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				theStream
			);

			WriteFiled
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : Triangles)
			{
				theStream
					<< x.Value(0)
					<< "  "
					<< x.Value(1)
					<< "  "
					<< x.Value(2)
					<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			File << Variables << endl;

			WriteFeTriangleZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				File
			);

			WriteFiled
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			theStream << Variables << "\n";

			WriteFeTriangleZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				theStream
			);

			WriteFiled
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : Triangles)
			{
				theStream
				<< x.Value(0)
				<< "  "
				<< x.Value(1)
				<< "  "
				<< x.Value(2)
				<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theTets,
			OFstream& File
		)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			File << Variables << endl;

			WriteFeTetrahedralZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)theTets.size(),
				File
			);

			WriteFiled
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : theTets)
			{
				File << x.Value(0) << " " << x.Value(1) << " " << x.Value(2) << " " << x.Value(3) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::quadruple>& theTets,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			theStream << Variables << endl;

			WriteFeTetrahedralZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)theTets.size(),
				theStream
			);

			WriteFiled
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : theTets)
			{
				theStream
				<< x.Value(0)
				<< " "
				<< x.Value(1)
				<< " "
				<< x.Value(2)
				<< " "
				<< x.Value(3)
				<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word & theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			File << Variables << endl;

			WriteCellCenteredFeTriangularZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				(Standard_Integer)nbVAR, File);

			WritePointsVariables(thePoints, File);

			WriteCellCenteredField(Triangles, var, File);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			theStream << Variables << "\n";

			WriteCellCenteredFeTriangularZone
			(
				(Standard_Integer)thePoints.size(),
				(Standard_Integer)Triangles.size(),
				(Standard_Integer)nbVAR, theStream);

			WritePointsVariables(thePoints, theStream);

			WriteCellCenteredField(Triangles, var, theStream);
		}
	}
}